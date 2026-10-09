from pathlib import Path
from datetime import date, datetime
import subprocess
import os
import re

CHANGELOG = Path("CHANGELOG.md")
PROJECT_START = date(2026, 10, 1)
DATE_FORMAT = "%d/%m/%y"

CATEGORIES = {
    "add": "Ajouté",
    "feat": "Ajouté",
    "mod": "Modifié",
    "update": "Modifié",
    "fix": "Corrigé",
}

CATEGORY_ORDER = ["Ajouté", "Modifié", "Corrigé"]


def git(*args):
    result = subprocess.run(
        ["git", *args],
        capture_output=True,
        text=True,
        encoding="utf-8",
        check=True,
    )
    return result.stdout.strip()


def first_name(name):
    name = name.strip().lstrip("@")
    return name.split()[0] if name else "Inconnu"


def get_push_date():
    push_date = os.environ.get("PUSH_DATE")
    if not push_date:
        return date.today()
    return datetime.strptime(push_date, "%Y-%m-%d").date()


def project_week(push_date):
    delta = (push_date - PROJECT_START).days
    if delta < 0:
        return None
    return (delta // 7) + 1


def get_commits():
    before = os.environ.get("BEFORE", "")
    after = os.environ.get("AFTER", "HEAD")

    if not before or before == "0" * 40:
        hashes = [after]
    else:
        hashes = git("rev-list", "--reverse", f"{before}..{after}").splitlines()

    commits = []

    for commit_hash in hashes:
        subject = git("show", "-s", "--format=%s", commit_hash)

        if subject.lower().startswith("chore: mise à jour automatique du changelog"):
            continue

        # Accepte add:, add :, mod:, mod :, fix:, fix :
        match = re.match(
            r"^(add|feat|mod|update|fix)\s*:\s*(.+)$",
            subject,
            re.IGNORECASE,
        )

        if not match:
            continue

        prefix = match.group(1).lower()
        description = match.group(2).strip()

        author = git("show", "-s", "--format=%an", commit_hash)
        authors = [first_name(author)]

        body = git("show", "-s", "--format=%B", commit_hash)
        coauthors = re.findall(
            r"(?im)^Co-authored-by:\s*([^<\n]+)\s*<[^>]+>",
            body,
        )

        for coauthor in coauthors:
            name = first_name(coauthor)
            if name.lower() not in [a.lower() for a in authors]:
                authors.append(name)

        commits.append(
            {
                "category": CATEGORIES[prefix],
                "description": description,
                "authors": authors,
            }
        )

    return commits


def make_entry(commit):
    description = commit["description"].strip()
    if description:
        description = description[0].upper() + description[1:]

    # Le point final est ajouté après la liste des auteurs
    description = description.rstrip(". ")
    authors = ", ".join(f"@{author}" for author in commit["authors"])
    return f"- {description} ({authors})."


def template_start(content):
    return content.find("<!--")


def get_week_sections(content):
    """Ne lit que les semaines placées avant le gabarit commenté."""
    end_of_logs = template_start(content)
    if end_of_logs == -1:
        end_of_logs = len(content)

    log_area = content[:end_of_logs]

    pattern = re.compile(
        r"(?m)^## Semaine (\d+) -- (\d{2}/\d{2}/\d{2})[ \t]*$"
    )

    sections = []
    for match in pattern.finditer(log_area):
        sections.append(
            {
                "number": int(match.group(1)),
                "date": match.group(2),
                "start": match.start(),
                "header_end": match.end(),
            }
        )
    return sections


def find_week(content, week_number):
    """Une seule section par semaine. La date existante n'est jamais modifiée."""
    for section in get_week_sections(content):
        if section["number"] == week_number:
            return section
    return None


def get_section_end(content, section):
    sections = get_week_sections(content)
    later = [s["start"] for s in sections if s["start"] > section["start"]]

    if later:
        return min(later)

    end = template_start(content)
    return len(content) if end == -1 else end


def add_entry(content, week_number, category, entry):
    """Ajoute uniquement du nouveau texte sans réécrire les anciens logs."""
    section = find_week(content, week_number)
    if not section:
        return content

    start = section["start"]
    end = get_section_end(content, section)
    block = content[start:end]

    if entry in block:
        return content

    category_pattern = re.compile(
        r"(?m)^### (Ajouté|Modifié|Corrigé)[ \t]*$"
    )
    headings = list(category_pattern.finditer(block))

    target = None
    for heading in headings:
        if heading.group(1) == category:
            target = heading
            break

    if target:
        following = [h.start() for h in headings if h.start() > target.start()]
        insertion = min(following) if following else len(block)

        prefix = "" if block[:insertion].endswith("\n") else "\n"
        new_block = (
            block[:insertion]
            + prefix
            + entry
            + "\n"
            + block[insertion:]
        )
    else:
        target_order = CATEGORY_ORDER.index(category)
        insertion = None

        for heading in headings:
            existing_category = heading.group(1)
            if CATEGORY_ORDER.index(existing_category) > target_order:
                insertion = heading.start()
                break

        if insertion is None:
            insertion = len(block)

        fragment = f"### {category}\n\n{entry}\n\n"

        if block[:insertion].endswith("\n\n"):
            prefix = ""
        elif block[:insertion].endswith("\n"):
            prefix = "\n"
        else:
            prefix = "\n\n"

        new_block = (
            block[:insertion]
            + prefix
            + fragment
            + block[insertion:]
        )

    return content[:start] + new_block + content[end:]


def create_week(week_number, push_date, entries):
    """La date du titre est celle du premier log créé pour cette semaine."""
    date_string = push_date.strftime(DATE_FORMAT)
    result = f"## Semaine {week_number} -- {date_string}\n"

    for category in CATEGORY_ORDER:
        category_entries = [
            entry
            for entry_category, entry in entries
            if entry_category == category
        ]

        if not category_entries:
            continue

        result += f"\n### {category}\n\n"
        for entry in category_entries:
            result += entry + "\n"

    return result.rstrip() + "\n\n"


def insert_new_week(content, new_section):
    """Insère toujours la nouvelle semaine avant les anciennes et avant le gabarit."""
    sections = get_week_sections(content)
    candidates = []

    if sections:
        candidates.append(min(section["start"] for section in sections))

    template = template_start(content)
    if template != -1:
        candidates.append(template)

    if candidates:
        position = min(candidates)
        return content[:position] + new_section + content[position:]

    return content.rstrip() + "\n\n" + new_section


def main():
    if not CHANGELOG.exists():
        raise FileNotFoundError("CHANGELOG.md introuvable à la racine du projet.")

    push_date = get_push_date()
    week_number = project_week(push_date)

    if week_number is None:
        print("Push antérieur au lancement du projet.")
        return

    commits = get_commits()

    if not commits:
        print("Aucun commit add:, mod: ou fix: à ajouter.")
        return

    content = CHANGELOG.read_text(encoding="utf-8")

    entries = [
        (commit["category"], make_entry(commit))
        for commit in commits
    ]

    # Une seule section par semaine.
    # Si elle existe déjà, sa date reste inchangée.
    if find_week(content, week_number):
        for category, entry in entries:
            content = add_entry(
                content,
                week_number,
                category,
                entry,
            )
    else:
        new_section = create_week(
            week_number,
            push_date,
            entries,
        )
        content = insert_new_week(content, new_section)

    CHANGELOG.write_text(content, encoding="utf-8")

    print(
        f"CHANGELOG mis à jour : Semaine {week_number}, "
        f"push du {push_date.strftime(DATE_FORMAT)}"
    )


if __name__ == "__main__":
    main()
