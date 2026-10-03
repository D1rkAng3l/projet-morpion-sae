from pathlib import Path
from datetime import date, timedelta, datetime
import subprocess
import os
import re

CHANGELOG = Path("CHANGELOG.md")

# Date de début de la semaine 1
PROJECT_START = date.fromisoformat(
    os.getenv("PROJECT_START_DATE", "2026-10-01")
)

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


def get_commits():
    before = os.getenv("BEFORE", "")
    after = os.getenv("AFTER", "HEAD")

    # Premier push du dépôt
    if not before or before == "0" * 40:
        revision = after
    else:
        revision = f"{before}..{after}"

    result = subprocess.run(
        [
            "git",
            "log",
            "--reverse",
            "--format=%an%x1f%ad%x1f%s",
            "--date=short",
            revision,
        ],
        capture_output=True,
        text=True,
        check=True,
    )

    commits = []

    for line in result.stdout.splitlines():
        parts = line.split("\x1f")

        if len(parts) != 3:
            continue

        author, commit_date, message = parts

        match = re.match(
            r"^(add|feat|mod|update|fix):\s*(.+)$",
            message,
            re.IGNORECASE,
        )

        if not match:
            continue

        prefix = match.group(1).lower()
        description = match.group(2).strip()

        commits.append({
            "author": author,
            "date": datetime.strptime(
                commit_date,
                "%Y-%m-%d"
            ).date(),
            "category": CATEGORIES[prefix],
            "description": description,
        })

    return commits


def get_week(commit_date):
    days = (commit_date - PROJECT_START).days

    if days < 0:
        return None

    return (days // 7) + 1


def author_name(author):
    # Prend le premier mot du nom Git
    # "Mathis Dupont" -> Mathis
    return author.strip().split()[0]


def make_entry(commit):
    description = commit["description"]

    if description:
        description = (
            description[0].upper()
            + description[1:]
        )

    author = author_name(commit["author"])

    return f"- {description} (@{author})"


def find_section(content, header):
    start = content.find(header)

    if start == -1:
        return None

    search_start = start + len(header)

    match = re.search(
        r"(?m)^## Semaine ",
        content[search_start:]
    )

    if match:
        end = search_start + match.start()
    else:
        end = len(content)

    return start, end


def add_to_existing_section(
    content,
    header,
    category,
    entry
):
    bounds = find_section(content, header)

    if not bounds:
        return content

    start, end = bounds

    section = content[start:end]

    # Évite les doublons
    if entry in section:
        return content

    category_header = f"### {category}"

    if category_header in section:

        category_pos = section.find(category_header)

        next_category = re.search(
            r"(?m)^### ",
            section[
                category_pos
                + len(category_header):
            ]
        )

        if next_category:
            insert_pos = (
                category_pos
                + len(category_header)
                + next_category.start()
            )
        else:
            insert_pos = len(section)

        section = (
            section[:insert_pos].rstrip()
            + "\n"
            + entry
            + "\n\n"
            + section[insert_pos:].lstrip()
        )

    else:
        section = (
            section.rstrip()
            + f"\n\n### {category}\n\n"
            + entry
            + "\n\n"
        )

    return (
        content[:start]
        + section
        + content[end:]
    )


def create_section(week, week_date, entries):
    section = (
        f"## Semaine {week} -- "
        f"{week_date.strftime('%d/%m/%y')}\n"
    )

    for category in CATEGORY_ORDER:

        category_entries = [
            entry
            for cat, entry in entries
            if cat == category
        ]

        if not category_entries:
            continue

        section += f"\n### {category}\n\n"

        for entry in category_entries:
            section += entry + "\n"

    return section.rstrip() + "\n\n"


def main():
    commits = get_commits()

    if not commits:
        print(
            "Aucun commit add:, mod: ou fix: trouvé."
        )
        return

    content = CHANGELOG.read_text(
        encoding="utf-8"
    )

    weeks = {}

    for commit in commits:

        week = get_week(commit["date"])

        if week is None:
            continue

        # La date affichée correspond au début
        # de la semaine du projet
        week_date = (
            PROJECT_START
            + timedelta(days=(week - 1) * 7)
        )

        key = (week, week_date)

        weeks.setdefault(key, [])

        weeks[key].append(
            (
                commit["category"],
                make_entry(commit)
            )
        )

    # Les semaines récentes d'abord
    for (week, week_date), entries in sorted(
        weeks.items(),
        reverse=True,
    ):

        header = (
            f"## Semaine {week} -- "
            f"{week_date.strftime('%d/%m/%y')}"
        )

        if header not in content:

            new_section = create_section(
                week,
                week_date,
                entries,
            )

            first_week = re.search(
                r"(?m)^## Semaine ",
                content
            )

            if first_week:
                pos = first_week.start()

                content = (
                    content[:pos]
                    + new_section
                    + content[pos:]
                )

            else:
                content += "\n" + new_section

        else:

            for category, entry in entries:

                content = add_to_existing_section(
                    content,
                    header,
                    category,
                    entry,
                )

    CHANGELOG.write_text(
        content,
        encoding="utf-8",
    )

    print("CHANGELOG.md mis à jour.")


if __name__ == "__main__":
    main()