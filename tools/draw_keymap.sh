#!/usr/bin/env bash
# Regenerates the keymap diagrams in doc/ from keymap.c with keymap-drawer
# (https://github.com/caksoylar/keymap-drawer).
#
# Setup (once):  pipx install keymap-drawer   # or: pip install keymap-drawer
# Run:           tools/draw_keymap.sh
set -euo pipefail

cd "$(dirname "$0")/.."
TOOLS=tools/keymap_drawer
OUT=doc
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$OUT"

# 1. keymap.c -> QMK keymap JSON (qmk c2json can't parse this keymap).
python3 "$TOOLS/keymap_to_json.py" . > "$TMP/keymap.json"
read -r -a LAYERS < <(python3 -c \
  'import json,sys; print(" ".join(json.load(open(sys.argv[1]))["layer_names"]))' \
  "$TMP/keymap.json")

# 2. JSON -> keymap-drawer YAML, with friendly legends from config.yaml.
keymap -c "$TOOLS/config.yaml" parse -q "$TMP/keymap.json" \
  -l "${LAYERS[@]}" -c 12 -o "$TMP/keymap.yaml"

# 3. YAML (+ combos) -> SVG: one with all layers, and one per layer.
keymap -c "$TOOLS/config.yaml" draw "$TMP/keymap.yaml" "$TOOLS/combos.yaml" \
  -o "$OUT/keymap.svg"
for layer in "${LAYERS[@]}"; do
  name=$(echo "$layer" | tr '[:upper:]' '[:lower:]')
  keymap -c "$TOOLS/config.yaml" draw "$TMP/keymap.yaml" "$TOOLS/combos.yaml" \
    -s "$layer" -o "$OUT/layer-$name.svg"
done

# 4. Bigger single-character legends and yellow hold bands (getreuer-style).
python3 "$TOOLS/postprocess.py" "$OUT"/keymap.svg "$OUT"/layer-*.svg
echo "Wrote $OUT/keymap.svg and $OUT/layer-*.svg"
