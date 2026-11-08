#!/usr/bin/env python3
"""Post-processes keymap-drawer SVGs for a getreuer-style look.

* Single-character tap legends (letters, digits, symbols) get the CSS class
  "big", so they can be drawn larger than word legends like "Home".
* Keys with a hold behavior (home row mods, layer-taps) get a yellow band
  along the bottom of the key, behind the hold legend, like the diagrams in
  getreuer/qmk-keymap.

Colors and sizes are set in config.yaml (text.big, path.holdband).

Usage: tools/keymap_drawer/postprocess.py doc/*.svg
(normally run by tools/draw_keymap.sh)
"""

import re
import sys

BAND_HEIGHT = 22

# A key is drawn as <g ... class="key ..."><rect .../><text/use .../></g>.
KEY_RE = re.compile(r'(<g transform="[^"]*" class="key[^"]*">)(.*?)(</g>)',
                    re.S)
RECT_RE = re.compile(
    r'<rect rx="([\d.]+)" ry="([\d.]+)" x="([-\d.]+)" y="([-\d.]+)" '
    r'width="([\d.]+)" height="([\d.]+)" class="key([^"]*)"/>')
# A tap legend that is a single character or a single XML entity.
TAP_RE = re.compile(r'(<text [^>]*class="key(?: held)? tap)(">)'
                    r'([^<&]|&[a-z]+;|&#\d+;)(</text>)')
HOLD_RE = re.compile(r'<(?:text|use) [^>]*class="key[^"]* hold[" ]')


def band(rect: re.Match) -> str:
    """A band along the bottom of the key, following its rounded corners."""
    rx, ry, x, y, w, h = map(float, rect.groups()[:6])
    bottom, right = y + h, x + w
    top = bottom - BAND_HEIGHT
    return (f'<path class="holdband" d="M{x:g},{top:g} H{right:g} '
            f'V{bottom - ry:g} A{rx:g},{ry:g} 0 0 1 {right - rx:g},{bottom:g} '
            f'H{x + rx:g} A{rx:g},{ry:g} 0 0 1 {x:g},{bottom - ry:g} Z"/>')


def fix_key(m: re.Match) -> str:
    start, body, end = m.groups()
    body = TAP_RE.sub(r'\1 big\2\3\4', body)
    if HOLD_RE.search(body):
        rect = RECT_RE.search(body)
        if rect and "trans" not in rect.group(7):
            body = body.replace(rect.group(0), rect.group(0) + band(rect), 1)
    return start + body + end


for path in sys.argv[1:]:
    with open(path, encoding="utf-8") as f:
        svg = f.read()
    with open(path, "w", encoding="utf-8") as f:
        f.write(KEY_RE.sub(fix_key, svg))
