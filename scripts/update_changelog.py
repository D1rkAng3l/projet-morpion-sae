from pathlib import Path
from datetime import date, timedelta, datetime
import subprocess
import os
import re


# ============================================================
# CONFIGURATION
# ============================================================

# Le fichier CHANGELOG.md situé à la racine du projet
CHANGELOG = Path("CHANGELOG.md")

# Date officielle de lancement du projet :
# 01/10/2026 = Semaine 1
PROJECT_START = date(2026, 10, 1)

# Format imposé par le modèle du CHANGELOG
DATE_FORMAT = "%d/%m/%y"

# Préfixes autorisés dans les commits
CATEGORIES = {
    "add": "Ajouté",
    "feat": "Ajouté",

    "mod": "Modifié",
    "update": "Modifié",

    "fix": "Corrigé",
}

# Ordre des catégories dans le CHANGELOG
CATEGORY_ORDER = [
    "Ajouté",
    "Modifié",
    "Corrigé",
]


# ============================================================
# COMMANDES GIT
# ============================================================

def git(*args):
    """
    Exécute une commande Git et renvoie sa sortie.
    """

    result = subprocess.run(
        ["git", *args],
        capture_output=True,
        text=True,
        encoding="utf-8",
        check=True,
    )

    return result.stdout.strip()


# ============================================================
# GESTION DES AUTEURS
# ============================================================

def first_name(name):
    """
    Transforme :

        Mathis Dupont -> Mathis
        @Mathis       -> Mathis
        Ilan          -> Ilan
    """

    name = name.strip().lstrip("@")

    if not name:
        return "Inconnu"

    return name.split()[0]


# ============================================================
# RÉCUPÉRATION DES COMMITS DU PUSH
# ============================================================

def get_commits():

    before = os.environ.get("BEFORE", "")
    after = os.environ.get("AFTER", "HEAD")

    # --------------------------------------------------------
    # Premier push du dépôt
    # --------------------------------------------------------

    if not before or before == "0" * 40:

        hashes = git(
            "rev-list",
            "--reverse",
            after
        ).splitlines()

    # --------------------------------------------------------
    # Push classique
    # --------------------------------------------------------

    else:

        hashes = git(
            "rev-list",
            "--reverse",
            f"{before}..{after}"
        ).splitlines()

    commits = []

    for commit_hash in hashes:

        # ----------------------------------------------------
        # Sujet du commit
        # ----------------------------------------------------

        subject = git(
            "show",
            "-s",
            "--format=%s",
            commit_hash
        )

        # Ignore les commits automatiques du bot
        if subject.startswith(
            "chore: mise à jour automatique du changelog"
        ):
            continue

        # ----------------------------------------------------
        # Vérification du préfixe
        #
        # add:
        # feat:
        # mod:
        # update:
        # fix:
        # ----------------------------------------------------

        match = re.match(
            r"^(add|feat|mod|update|fix):\s*(.+)$",
            subject,
            re.IGNORECASE,
        )

        # Commit sans préfixe valide :
        # il n'est pas ajouté au CHANGELOG
        if not match:
            continue

        prefix = match.group(1).lower()

        description = match.group(2).strip()

        # ----------------------------------------------------
        # Auteur principal
        # ----------------------------------------------------

        author = git(
            "show",
            "-s",
            "--format=%an",
            commit_hash
        )

        # ----------------------------------------------------
        # Date du commit
        # ----------------------------------------------------

        commit_date_string = git(
            "show",
            "-s",
            "--format=%as",
            commit_hash
        )

        commit_date = datetime.strptime(
            commit_date_string,
            "%Y-%m-%d"
        ).date()

        # ----------------------------------------------------
        # Corps complet du commit
        # ----------------------------------------------------

        body = git(
            "show",
            "-s",
            "--format=%B",
            commit_hash
        )

        authors = [
            first_name(author)
        ]

        # ----------------------------------------------------
        # Gestion des co-auteurs
        #
        # Exemple :
        #
        # Co-authored-by: Ilan <mail@example.com>
        # ----------------------------------------------------

        coauthors = re.findall(
            r"(?im)^Co-authored-by:\s*([^<\n]+)\s*<[^>]+>",
            body
        )

        for coauthor in coauthors:

            name = first_name(coauthor)

            if name.lower() not in [
                author_name.lower()
                for author_name in authors
            ]:
                authors.append(name)

        commits.append(
            {
                "hash": commit_hash,
                "date": commit_date,
                "category": CATEGORIES[prefix],
                "description": description,
                "authors": authors,
            }
        )

    return commits


# ============================================================
# CALCUL DU NUMÉRO DE SEMAINE
# ============================================================

def project_week(commit_date):
    """
    01/10/2026 -> Semaine 1
    08/10/2026 -> Semaine 2
    15/10/2026 -> Semaine 3
    etc.
    """

    delta = (
        commit_date
        - PROJECT_START
    ).days

    # Commit antérieur au lancement du projet
    if delta < 0:
        return None, None

    week_number = (
        delta // 7
    ) + 1

    week_start = (
        PROJECT_START
        + timedelta(
            days=(week_number - 1) * 7
        )
    )

    return (
        week_number,
        week_start
    )


# ============================================================
# CRÉATION D'UNE LIGNE DU CHANGELOG
# ============================================================

def make_entry(commit):

    description = commit["description"]

    # Majuscule automatique
    if description:

        description = (
            description[0].upper()
            + description[1:]
        )

    authors = ", ".join(
        f"@{author}"
        for author in commit["authors"]
    )

    return (
        f"- {description} ({authors})"
    )


# ============================================================
# GESTION DES COMMENTAIRES HTML
# ============================================================

def comment_ranges(content):
    """
    Récupère les zones comprises entre :

        <!--
        -->

    afin que le modèle du CHANGELOG
    ne soit jamais modifié.
    """

    ranges = []

    cursor = 0

    while True:

        start = content.find(
            "<!--",
            cursor
        )

        if start == -1:
            break

        end = content.find(
            "-->",
            start + 4
        )

        if end == -1:

            ranges.append(
                (
                    start,
                    len(content)
                )
            )

            break

        ranges.append(
            (
                start,
                end + 3
            )
        )

        cursor = end + 3

    return ranges


def inside_comment(
    position,
    ranges
):

    return any(
        start <= position < end
        for start, end in ranges
    )


# ============================================================
# RECHERCHE DES VRAIES SEMAINES
# ============================================================

def week_sections(content):

    ranges = comment_ranges(
        content
    )

    pattern = re.compile(
        r"(?m)^## Semaine "
        r"(\d+) -- "
        r"(\d{2}/\d{2}/\d{2})"
        r"[ \t]*$"
    )

    sections = []

    for match in pattern.finditer(
        content
    ):

        # Ignore le modèle commenté
        if inside_comment(
            match.start(),
            ranges
        ):
            continue

        try:

            section_date = (
                datetime.strptime(
                    match.group(2),
                    DATE_FORMAT
                ).date()
            )

        except ValueError:
            continue

        sections.append(
            {
                "start": match.start(),
                "end_header": match.end(),
                "number": int(
                    match.group(1)
                ),
                "date": section_date,
                "header": match.group(0),
            }
        )

    return sections


# ============================================================
# LIMITES D'UNE SECTION SEMAINE
# ============================================================

def section_bounds(
    content,
    section
):

    sections = week_sections(
        content
    )

    next_sections = [
        item["start"]
        for item in sections
        if item["start"]
        > section["start"]
    ]

    if next_sections:

        end = min(
            next_sections
        )

    else:

        end = len(
            content
        )

    # --------------------------------------------------------
    # Si le modèle HTML est juste après la semaine,
    # on s'arrête avant le modèle.
    # --------------------------------------------------------

    comment_start = content.find(
        "<!--",
        section["end_header"]
    )

    if (
        comment_start != -1
        and comment_start < end
    ):

        end = comment_start

    return (
        section["start"],
        end
    )


# ============================================================
# RECHERCHE D'UNE SEMAINE EXISTANTE
# ============================================================

def find_or_normalize_week(
    content,
    week_number,
    week_start
):

    sections = week_sections(
        content
    )

    # --------------------------------------------------------
    # Cas idéal :
    # date déjà correcte
    # --------------------------------------------------------

    for section in sections:

        if (
            section["number"]
            == week_number
            and section["date"]
            == week_start
        ):

            return (
                content,
                section
            )

    # --------------------------------------------------------
    # Correction automatique d'une petite erreur de date
    #
    # Exemple actuel :
    #
    # ## Semaine 1 -- 02/10/26
    #
    # alors que la semaine commence le 01/10/26.
    # --------------------------------------------------------

    week_end = (
        week_start
        + timedelta(days=6)
    )

    for section in sections:

        if (
            section["number"]
            == week_number
            and week_start
            <= section["date"]
            <= week_end
        ):

            expected_header = (
                f"## Semaine "
                f"{week_number} -- "
                f"{week_start.strftime(DATE_FORMAT)}"
            )

            content = (
                content[:section["start"]]
                + expected_header
                + content[
                    section["end_header"]:
                ]
            )

            # Relecture après modification
            sections = week_sections(
                content
            )

            for new_section in sections:

                if (
                    new_section["number"]
                    == week_number
                    and new_section["date"]
                    == week_start
                ):

                    return (
                        content,
                        new_section
                    )

    return (
        content,
        None
    )


# ============================================================
# AJOUT D'UNE ENTRÉE DANS UNE SEMAINE
# ============================================================

def add_entry_to_section(
    content,
    section,
    category,
    entry
):

    start, end = section_bounds(
        content,
        section
    )

    block = content[
        start:end
    ]

    # --------------------------------------------------------
    # Empêche les doublons
    # --------------------------------------------------------

    if entry in block:
        return content

    category_pattern = re.compile(
        r"(?m)^### "
        r"(Ajouté|Modifié|Corrigé)"
        r"[ \t]*$"
    )

    headings = list(
        category_pattern.finditer(
            block
        )
    )

    existing_heading = None

    for heading in headings:

        if (
            heading.group(1)
            == category
        ):

            existing_heading = (
                heading
            )

            break

    # ========================================================
    # CATÉGORIE DÉJÀ EXISTANTE
    # ========================================================

    if existing_heading:

        next_headings = [
            heading.start()
            for heading in headings
            if heading.start()
            > existing_heading.start()
        ]

        if next_headings:

            insertion = min(
                next_headings
            )

        else:

            insertion = len(
                block
            )

        before = (
            block[:insertion]
            .rstrip()
        )

        after = (
            block[insertion:]
            .lstrip("\n")
        )

        block = (
            before
            + "\n"
            + entry
            + "\n\n"
            + after
        )

    # ========================================================
    # CATÉGORIE ABSENTE
    # ========================================================

    else:

        target_order = (
            CATEGORY_ORDER.index(
                category
            )
        )

        next_heading = None

        for heading in headings:

            existing_category = (
                heading.group(1)
            )

            existing_order = (
                CATEGORY_ORDER.index(
                    existing_category
                )
            )

            if (
                existing_order
                > target_order
            ):

                next_heading = (
                    heading
                )

                break

        fragment = (
            f"### {category}\n\n"
            f"{entry}\n\n"
        )

        # ----------------------------------------------------
        # Insère avant la catégorie suivante
        # ----------------------------------------------------

        if next_heading:

            position = (
                next_heading.start()
            )

            block = (
                block[:position]
                .rstrip()
                + "\n\n"
                + fragment
                + block[position:]
                .lstrip("\n")
            )

        # ----------------------------------------------------
        # Sinon ajoute à la fin
        # ----------------------------------------------------

        else:

            block = (
                block.rstrip()
                + "\n\n"
                + fragment
            )

    return (
        content[:start]
        + block
        + content[end:]
    )


# ============================================================
# CRÉATION D'UNE NOUVELLE SEMAINE
# ============================================================

def create_week_section(
    week_number,
    week_start,
    entries
):

    date_string = (
        week_start.strftime(
            DATE_FORMAT
        )
    )

    result = (
        f"## Semaine "
        f"{week_number} -- "
        f"{date_string}\n"
    )

    # --------------------------------------------------------
    # Respecte l'ordre du modèle :
    #
    # Ajouté
    # Modifié
    # Corrigé
    # --------------------------------------------------------

    for category in CATEGORY_ORDER:

        category_entries = [
            entry
            for (
                entry_category,
                entry
            ) in entries
            if entry_category
            == category
        ]

        # Ne crée pas de catégorie vide
        if not category_entries:
            continue

        result += (
            f"\n### "
            f"{category}\n\n"
        )

        for entry in category_entries:

            result += (
                entry
                + "\n"
            )

    return (
        result.rstrip()
        + "\n\n"
    )


# ============================================================
# INSERTION D'UNE NOUVELLE SEMAINE
# ============================================================

def insert_new_week(
    content,
    section
):

    sections = week_sections(
        content
    )

    # --------------------------------------------------------
    # La nouvelle semaine est placée avant
    # toutes les semaines existantes.
    # --------------------------------------------------------

    if sections:

        position = (
            sections[0]["start"]
        )

        return (
            content[:position]
            + section
            + content[position:]
        )

    # --------------------------------------------------------
    # Aucun historique présent :
    # insertion avant le modèle commenté.
    # --------------------------------------------------------

    template = content.find(
        "<!--"
    )

    if template != -1:

        return (
            content[:template]
            + section
            + content[template:]
        )

    # --------------------------------------------------------
    # Aucun modèle non plus
    # --------------------------------------------------------

    return (
        content.rstrip()
        + "\n\n"
        + section
    )


# ============================================================
# PROGRAMME PRINCIPAL
# ============================================================

def main():

    # --------------------------------------------------------
    # Vérification du fichier
    # --------------------------------------------------------

    if not CHANGELOG.exists():

        raise FileNotFoundError(
            "CHANGELOG.md est introuvable "
            "à la racine du projet."
        )

    # --------------------------------------------------------
    # Récupération des commits
    # --------------------------------------------------------

    commits = get_commits()

    if not commits:

        print(
            "Aucun commit add:, mod: "
            "ou fix: à ajouter."
        )

        return

    # --------------------------------------------------------
    # Lecture du vrai CHANGELOG.md
    # --------------------------------------------------------

    content = (
        CHANGELOG.read_text(
            encoding="utf-8"
        )
    )

    weeks = {}

    # --------------------------------------------------------
    # Classement des commits par semaine
    # --------------------------------------------------------

    for commit in commits:

        (
            week_number,
            week_start
        ) = project_week(
            commit["date"]
        )

        # Commit avant le lancement
        if week_number is None:
            continue

        key = (
            week_number,
            week_start
        )

        weeks.setdefault(
            key,
            []
        )

        weeks[key].append(
            (
                commit["category"],
                make_entry(commit)
            )
        )

    # --------------------------------------------------------
    # Semaine la plus récente en premier
    # --------------------------------------------------------

    ordered_weeks = sorted(
        weeks.items(),
        key=lambda item: item[0][1],
        reverse=True,
    )

    # --------------------------------------------------------
    # Mise à jour du fichier
    # --------------------------------------------------------

    for (
        week_number,
        week_start
    ), entries in ordered_weeks:

        # Cherche la semaine existante
        content, section = (
            find_or_normalize_week(
                content,
                week_number,
                week_start
            )
        )

        # ====================================================
        # SEMAINE EXISTANTE
        # ====================================================

        if section:

            for (
                category,
                entry
            ) in entries:

                # Relecture de la section après
                # chaque modification
                content, section = (
                    find_or_normalize_week(
                        content,
                        week_number,
                        week_start
                    )
                )

                content = (
                    add_entry_to_section(
                        content,
                        section,
                        category,
                        entry
                    )
                )

        # ====================================================
        # NOUVELLE SEMAINE
        # ====================================================

        else:

            new_section = (
                create_week_section(
                    week_number,
                    week_start,
                    entries
                )
            )

            content = (
                insert_new_week(
                    content,
                    new_section
                )
            )

    # --------------------------------------------------------
    # Écriture finale
    # --------------------------------------------------------

    CHANGELOG.write_text(
        content,
        encoding="utf-8"
    )

    print(
        "CHANGELOG.md mis à jour "
        "avec succès."
    )


if __name__ == "__main__":
    main()