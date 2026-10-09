"""Vérifie uniquement les fonctionnalités de la semaine 2."""
import argparse
import json
import os
from pathlib import Path
import platform
import shlex
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def run(command, **kwargs):
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True,
                            encoding="utf-8", timeout=120, **kwargs)
    if result.returncode:
        raise RuntimeError(result.stdout + result.stderr)
    return result

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cc", default="gcc")
    args = parser.parse_args()
    cc = shlex.split(args.cc, posix=os.name != "nt")
    output = ROOT / "output"
    output.mkdir(exist_ok=True)
    game = ROOT / ("jeu.exe" if os.name == "nt" else "jeu")
    flags = ["-std=c23", "-Wall", "-Wextra", "-Werror", "-pedantic"]
    modules = [str(p.relative_to(ROOT)) for p in sorted((ROOT / "lib").glob("*.c"))]
    run(cc + flags + ["jeu.c", *modules, "-o", str(game), "-lm"])
    scenarios = [
        ("joueurs", "Alice\nBob\n", ["Joueurs : Alice (X) et Bob (O).", "Plateau initial :", "Demonstration :", "A Alice de jouer (X).", "| X |", "| O |"]),
        ("nom-long", "A" * 200 + "\nAlice\nBob\n", ["Nom vide ou trop long", "Joueurs : Alice (X) et Bob (O)."]),
        ("nom-vide", "\nAlice\nBob\n", ["Nom vide ou trop long", "Joueurs : Alice (X) et Bob (O)."]),
        ("nom-limite", "A" * 63 + "\nBob\n", ["Joueurs : " + "A" * 63 + " (X) et Bob (O)."]),
        ("eof", "", ["Fin de saisie."]),
        ("eof-second-joueur", "Alice\n", ["Fin de saisie."]),
    ]
    results = []
    for name, inputs, expected in scenarios:
        result = run([str(game)], input=inputs)
        assert all(item in result.stdout for item in expected), (name, result.stdout)
        assert "Rejouer" not in result.stdout and "Niveau" not in result.stdout
        if name == "joueurs":
            empty = result.stdout.split("Plateau initial :", 1)[1].split("Demonstration :", 1)[0]
            assert "| X |" not in empty and "| O |" not in empty
            assert empty.count("|   |   |   |") == 3
        (output / (name + ".log")).write_text("ENTREES\n" + inputs + "\nATTENDU\n" + "\n".join(expected) + "\nOBTENU\n" + result.stdout + "\nVALIDATION : PASS\n", encoding="utf-8")
        results.append(name + " : PASS")
    metadata = {"systeme": platform.platform(), "compilateur": run(cc + ["--version"]).stdout.splitlines()[0], "options": flags, "perimetre": "semaine 2"}
    (output / "environnement.json").write_text(json.dumps(metadata, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    summary = "Compilation stricte : PASS\n" + "\n".join(results) + "\n"
    (output / "verification.log").write_text(summary, encoding="utf-8")
    print(summary)

if __name__ == "__main__":
    main()
