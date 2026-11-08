#!/usr/bin/env python3
"""Converts the Voyager keymap.c into QMK keymap JSON for keymap-drawer.

`qmk c2json` can't parse this keymap (it includes lakes26.c and uses the
LAYOUT_LR macro), so this script does a small, targeted conversion instead:

  * extracts each `[LAYER] = LAYOUT_LR(...)` block from keymap.c,
  * expands the simple `#define ALIAS VALUE` aliases from lakes26.c
    (e.g. HOME_S -> LALT_T(KC_S)),
  * replaces layer names with layer numbers (keymap-drawer wants numbers),
  * reorders keys from LAYOUT_LR order (left half, then right half) to the
    Voyager's LAYOUT order (row by row).

Usage: tools/keymap_drawer/keymap_to_json.py [repo_root] > keymap.json
(normally run by tools/draw_keymap.sh)
"""

import json
import pathlib
import re
import sys

ROOT = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
KEYMAP_C = ROOT / "keyboards/zsa/voyager/keymaps/lakes26/keymap.c"
DEFS_C = ROOT / "lakes26.c"


def strip_comments(s: str) -> str:
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    return re.sub(r"//[^\n]*", "", s)


def split_args(s: str) -> list[str]:
    """Splits a macro argument list on top-level commas."""
    args, depth, cur = [], 0, []
    for c in s:
        if c == "," and depth == 0:
            args.append("".join(cur))
            cur = []
            continue
        depth += (c == "(") - (c == ")")
        cur.append(c)
    args.append("".join(cur))
    return [re.sub(r"\s+", "", a) for a in args if a.strip()]


defs_src = strip_comments(DEFS_C.read_text())

# Layer names in enum order.
layer_enum = re.search(r"enum\s+layers\s*\{(.*?)\}", defs_src, re.S).group(1)
layers = [n.strip() for n in layer_enum.split(",") if n.strip()]
layer_index = {name: i for i, name in enumerate(layers)}

# Object-like aliases, e.g. `#define HOME_S LALT_T(KC_S)`.
aliases = dict(re.findall(r"^\s*#define\s+([A-Z][A-Z0-9_]*)\s+(\S.*?)\s*$",
                          defs_src, re.M))
# Keys whose firmware behavior differs from their keycode: EXT_COL is
# LT(EXT, KC_SCLN), but process_record_user() makes its tap type ':'.
aliases["EXT_COL"] = "LT(EXT,KC_COLN)"


def expand(token: str) -> str:
    for _ in range(10):  # Resolve aliases of aliases.
        if token not in aliases:
            break
        token = re.sub(r"\s+", "", aliases[token])
    # Layer names -> numbers, e.g. LT(NAV,KC_ESC) -> LT(3,KC_ESC).
    return re.sub(r"\b(" + "|".join(layers) + r")\b",
                  lambda m: str(layer_index[m.group(1)]), token)


# LAYOUT_LR argument index -> LAYOUT position. LAYOUT_LR lists the left half
# (4 rows of 6, then 2 thumbs) followed by the right half; LAYOUT interleaves
# the rows of both halves, then lists the 4 thumb keys.
ORDER = []
for row in range(4):
    ORDER += [row * 6 + c for c in range(6)]       # Left half row.
    ORDER += [26 + row * 6 + c for c in range(6)]  # Right half row.
ORDER += [24, 25, 50, 51]                          # Thumbs.

keymap_src = strip_comments(KEYMAP_C.read_text())
keymap_src = keymap_src[keymap_src.index("keymaps[]"):]
out_layers = []
for m in re.finditer(r"\[(\w+)\]\s*=\s*LAYOUT_LR\s*\(", keymap_src):
    start, depth, i = m.end(), 1, m.end()
    while depth:
        depth += (keymap_src[i] == "(") - (keymap_src[i] == ")")
        i += 1
    keys = [expand(k) for k in split_args(keymap_src[start:i - 1])]
    assert len(keys) == 52, f"{m.group(1)}: expected 52 keys, got {len(keys)}"
    out_layers.append([keys[j] for j in ORDER])
    if len(out_layers) == len(layers):
        break

json.dump({"keyboard": "zsa/voyager", "keymap": "lakes26", "layout": "LAYOUT",
           "layer_names": layers, "layers": out_layers}, sys.stdout, indent=1)
print()
