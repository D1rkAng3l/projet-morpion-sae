from pathlib import Path
from datetime import date, datetime
import subprocess
import os
import re


# ============================================================
# CONFIGURATION
# ============================================================

CHANGELOG = Path("CHANGELOG.md")

# Début officiel du projet
PROJECT_START = date(2026, 10, 1)

DATE_FORMAT = "%d/%m/%y"

CATEGORIES = {
    "add": "Ajouté",
    "feat": "Ajouté",

    "mod": "Modifié",
    "update": "Modifié",

    "fix": "Corrigé",
}

CATEGORY_ORDER = [
    "Ajouté",
    "Modifié",
    "Corrigé",
]


# ============================================================
# GIT
# ============================================================

def git(*args):
    result = subprocess.run(
        ["git", *args],
        capture_output=True,
        text=True,
        encoding="utf-8",
        check=True,
    )

    return result.stdout.strip()


# ============================================================
# AUTEURS
# ============================================================

def first_name(name):

    name = name.strip().lstrip("@")

    if not name:
        return "Inconnu"

    return name.split()[0]


# ============================================================
# DATE DU PUSH
# ============================================================

def get_push_date():

    push_date = os.environ.get("PUSH_DATE")

    if not push_date:
        return date.today()

    return datetime.strptime(
        push_date,
        "%Y-%m-%d"
    ).date()


# ============================================================
# NUMÉRO DE SEMAINE
# ============================================================

def project_week(push_date):

    delta = (
        push_date
        - PROJECT_START
    ).days

    if delta < 0:
        return None

    return (
        delta // 7
    ) + 1


# ============================================================
# COMMITS DU PUSH
# ============================================================

def get_commits():

    before = os.environ.get(
        "BEFORE",
        ""
    )

    after = os.environ.get(
        "AFTER",
        "HEAD"
    )

    # Premier push
    if (
        not before
        or before == "0" * 40
    ):

        hashes = [
            after
        ]

    else:

        hashes = git(
            "rev-list",
            "--reverse",
            f"{before}..{after}"
        ).splitlines()

    commits = []

    for commit_hash in hashes:

        subject = git(
            "show",
            "-s",
            "--format=%s",
            commit_hash
        )

        # Ignore le commit automatique
        if subject.startswith(
            "chore: mise à jour automatique du changelog"
        ):
            continue

        match = re.match(
            r"^(add|feat|mod|update|fix):\s*(.+)$",
            subject,
            re.IGNORECASE,
        )

        # Commit normal sans préfixe :
        # pas d'entrée dans le changelog
        if not match:
            continue

        prefix = (
            match.group(1)
            .lower()
        )

        description = (
            match.group(2)
            .strip()
        )

        # Auteur principal
        author = git(
            "show",
            "-s",
            "--format=%an",
            commit_hash
        )

        authors = [
            first_name(author)
        ]

        # Corps complet pour récupérer
        # les éventuels Co-authored-by
        body = git(
            "show",
            "-s",
            "--format=%B",
            commit_hash
        )

        coauthors = re.findall(
            r"(?im)^Co-authored-by:\s*([^<\n]+)\s*<[^>]+>",
            body
        )

        for coauthor in coauthors:

            name = first_name(
                coauthor
            )

            if name.lower() not in [
                existing.lower()
                for existing in authors
            ]:

                authors.append(
                    name
                )

        commits.append(
            {
                "category": CATEGORIES[prefix],
                "description": description,
                "authors": authors,
            }
        )

    return commits


# ============================================================
# CRÉATION D'UNE LIGNE
# ============================================================

def make_entry(commit):

    description = (
        commit["description"]
    )

    if description:

        description = (
            description[0].upper()
            + description[1:]
        )

    authors = ", ".join(
        f"@{author}"
        for author
        in commit["authors"]
    )

    return (
        f"- {description} ({authors})"
    )


# ============================================================
# COMMENTAIRES HTML
# ============================================================

def comment_ranges(content):

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
        for start, end
        in ranges
    )


# ============================================================
# RECHERCHE DES SEMAINES EXISTANTES
# ============================================================

def get_week_sections(content):

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

        sections.append(
            {
                "number": int(
                    match.group(1)
                ),
                "date": match.group(2),
                "start": match.start(),
                "header_end": match.end(),
            }
        )

    return sections


# ============================================================
# RECHERCHE D'UNE SEMAINE
# ============================================================

def find_week(
    content,
    week_number
):

    for section in get_week_sections(
        content
    ):

        if (
            section["number"]
            == week_number
        ):

            return section

    return None


# ============================================================
# FIN D'UNE SECTION
# ============================================================

def get_section_end(
    content,
    section
):

    sections = get_week_sections(
        content
    )

    positions = [
        item["start"]
        for item in sections
        if item["start"]
        > section["start"]
    ]

    if positions:

        end = min(
            positions
        )

    else:

        end = len(
            content
        )

    # Ne jamais entrer dans le modèle commenté
    comment = content.find(
        "<!--",
        section["header_end"]
    )

    if (
        comment != -1
        and comment < end
    ):

        end = comment

    return end


# ============================================================
# AJOUT DANS UNE SEMAINE EXISTANTE
# ============================================================

def add_entry(
    content,
    week_number,
    category,
    entry
):

    section = find_week(
        content,
        week_number
    )

    if not section:
        return content

    start = section["start"]

    end = get_section_end(
        content,
        section
    )

    block = content[
        start:end
    ]

    # --------------------------------------------------------
    # NE TOUCHE PAS AUX ENTRÉES EXISTANTES
    #
    # Si la même entrée existe déjà,
    # rien n'est fait.
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

    target = None

    for heading in headings:

        if (
            heading.group(1)
            == category
        ):

            target = heading
            break

    # ========================================================
    # CATÉGORIE EXISTANTE
    # ========================================================

    if target:

        following = [
            heading.start()
            for heading
            in headings
            if heading.start()
            > target.start()
        ]

        if following:

            insertion = min(
                following
            )

        else:

            insertion = len(
                block
            )

        ### Insertion uniquement
        ### Aucun caractère existant n'est supprimé ou modifié

        block = (
            block[:insertion]
            + entry
            + "\n"
            + block[insertion:]
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

        insertion = None

        # Cherche la prochaine catégorie
        # pour conserver :
        #
        # Ajouté
        # Modifié
        # Corrigé

        for heading in headings:

            heading_category = (
                heading.group(1)
            )

            heading_order = (
                CATEGORY_ORDER.index(
                    heading_category
                )
            )

            if (
                heading_order
                > target_order
            ):

                insertion = (
                    heading.start()
                )

                break

        fragment = (
            f"### {category}\n"
            f"{entry}\n\n"
        )

        if insertion is not None:

            block = (
                block[:insertion]
                .rstrip()
                + "\n\n"
                + fragment
                + block[insertion:]
                .lstrip("\n")
            )

        else:

            block = (
                block.rstrip()
                + "\n\n"
                + fragment
            )

    # --------------------------------------------------------
    # Seule la section ciblée est remplacée.
    #
    # Tout le reste du fichier reste strictement intact.
    # --------------------------------------------------------

    return (
        content[:start]
        + block
        + content[end:]
    )


# ============================================================
# CRÉATION D'UNE NOUVELLE SEMAINE
# ============================================================

def create_week(
    week_number,
    push_date,
    entries
):

    # IMPORTANT :
    # ici on prend la date réelle du PUSH,
    # PAS la date de début théorique de semaine.

    date_string = (
        push_date.strftime(
            DATE_FORMAT
        )
    )

    result = (
        f"## Semaine "
        f"{week_number} -- "
        f"{date_string}\n"
    )

    for category in CATEGORY_ORDER:

        category_entries = [
            entry
            for (
                entry_category,
                entry
            )
            in entries
            if entry_category
            == category
        ]

        if not category_entries:
            continue

        result += (
            f"\n### "
            f"{category}\n"
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
# INSERTION EN HAUT DU CHANGELOG
# ============================================================

def insert_new_week(
    content,
    new_section
):

    sections = get_week_sections(
        content
    )

    # Nouvelle semaine avant
    # la plus récente existante
    if sections:

        position = min(
            section["start"]
            for section
            in sections
        )

        return (
            content[:position]
            + new_section
            + content[position:]
        )

    # S'il n'y a encore aucune semaine :
    # insertion avant le modèle commenté
    template = content.find(
        "<!--"
    )

    if template != -1:

        return (
            content[:template]
            + new_section
            + content[template:]
        )

    return (
        content.rstrip()
        + "\n\n"
        + new_section
    )


# ============================================================
# MAIN
# ============================================================

def main():

    if not CHANGELOG.exists():

        raise FileNotFoundError(
            "CHANGELOG.md introuvable "
            "à la racine du projet."
        )

    push_date = get_push_date()

    week_number = project_week(
        push_date
    )

    if week_number is None:

        print(
            "Push antérieur au lancement "
            "du projet."
        )

        return

    commits = get_commits()

    if not commits:

        print(
            "Aucun commit add:, mod: "
            "ou fix: à ajouter."
        )

        return

    content = CHANGELOG.read_text(
        encoding="utf-8"
    )

    entries = [
        (
            commit["category"],
            make_entry(commit)
        )
        for commit in commits
    ]

    # ========================================================
    # LA SEMAINE EXISTE DÉJÀ
    #
    # IMPORTANT :
    # - on ne change PAS sa date
    # - on ne change PAS ses anciennes lignes
    # - on ajoute uniquement les nouvelles entrées
    # ========================================================

    if find_week(
        content,
        week_number
    ):

        for category, entry in entries:

            content = add_entry(
                content,
                week_number,
                category,
                entry
            )

    # ========================================================
    # PREMIER PUSH DE CETTE SEMAINE
    #
    # On crée la semaine avec LA DATE DU PUSH.
    # ========================================================

    else:

        new_section = create_week(
            week_number,
            push_date,
            entries
        )

        content = insert_new_week(
            content,
            new_section
        )

    CHANGELOG.write_text(
        content,
        encoding="utf-8"
    )

    print(
        f"CHANGELOG mis à jour : "
        f"Semaine {week_number}, "
        f"{push_date.strftime(DATE_FORMAT)}"
    )


if __name__ == "__main__":
    main()