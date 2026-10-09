"""Contrôles de non-régression du journal automatique sans modifier le dépôt."""
import importlib.util
from datetime import date
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("changelog", ROOT / "scripts/update_changelog.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class ChangelogTests(unittest.TestCase):
    def test_semaines(self):
        self.assertEqual(module.project_week(date(2026, 10, 1)), 1)
        self.assertEqual(module.project_week(date(2026, 10, 9)), 2)
        self.assertIsNone(module.project_week(date(2026, 9, 30)))

    def test_ajout_preserve_date_et_gabarit(self):
        content = "# Changelog\n\n## Semaine 2 -- 08/10/26\n\n### Ajouté\n\n- Ancien (@Tilio).\n\n<!--\n## Semaine 3 -- 16/10/26\n-->\n"
        entry = "- Nouveau (@Ilan)."
        result = module.add_entry(content, 2, "Corrigé", entry)
        self.assertIn("## Semaine 2 -- 08/10/26", result)
        self.assertIn("- Ancien (@Tilio).", result)
        self.assertEqual(result.count(entry), 1)
        self.assertEqual(module.add_entry(result, 2, "Corrigé", entry), result)
        self.assertIsNone(module.find_week(result, 3))

    def test_nouvelle_semaine_et_coauteurs(self):
        content = "# Changelog\n\n## Semaine 1 -- 01/10/26\n\n<!-- gabarit -->\n"
        entry = module.make_entry({"description": "nouveau module", "authors": ["Elisa", "Tilio"]})
        self.assertEqual(entry, "- Nouveau module (@Elisa, @Tilio).")
        result = module.insert_new_week(content, module.create_week(2, date(2026, 10, 9), [("Ajouté", entry)]))
        self.assertLess(result.index("## Semaine 2"), result.index("## Semaine 1"))

    def test_journal_reel_ordonne(self):
        content = (ROOT / "CHANGELOG.md").read_text(encoding="utf-8")
        sections = module.get_week_sections(content)
        numbers = [section["number"] for section in sections]
        self.assertEqual(numbers, sorted(set(numbers), reverse=True))
        self.assertIn("@Tilio", content)
        self.assertGreater(content.index("<!--"), sections[-1]["start"])


if __name__ == "__main__":
    unittest.main()
