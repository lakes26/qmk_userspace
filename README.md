# lakes26's QMK keymap for the ZSA Voyager

My [QMK](https://docs.qmk.fm) keymap for the [ZSA Voyager](https://www.zsa.io/voyager),
kept as a [QMK External Userspace](https://docs.qmk.fm/newbs_external_userspace).
It is based on [@getreuer's keymap](https://github.com/getreuer/qmk-keymap) and
uses his [community modules](https://github.com/getreuer/qmk-modules).

## Layers

The base layer is [Magic Sturdy](https://github.com/Ikcelaks/keyboard_layouts)
with home row mods (`⌥ ⌃ ⌘ ⇧` = Alt, Ctrl, GUI/Cmd, Shift). `✦` is the Magic
key (Alt Repeat), `Rep` the Repeat key, `·` unused, `(x)` passes through to the
layer below.

```
BASE
  ·     ·     ·     ↓     ↑     ·          Home  ←     →     End   App⁵  ⏯
  Tab   V     M     L     C     P          B     ✦     U     O     Q     /
  Bsp   S⌥    T⌃    R⌘    D⇧    Y          F     N⇧    E⌘    A⌃    I⌥    ·
  :¹    X     K     J     G²    W          Z     H     ,     .     ;     Ent
                          Spc   Esc³       Rep   Sym⁴
```

1. Tap `:`, hold for **EXT** (mouse).
2. Tap G, hold for **NUM**.
3. Tap Esc, hold for **NAV**.
4. One-shot **SYM**: the next key comes from SYM (hold to stay on it).
5. App switcher (Cmd+Tab on macOS, Super+Tab on GNOME) with
   [Cyclotab](https://github.com/getreuer/qmk-modules/tree/main/cyclotab): tap
   repeatedly to cycle; the next key press completes the switch.

Combos: **J + ,** toggles Caps Word; **F + N** is the one-shot **FUN** layer.
Key overrides: Shift + `,` = `!`, Shift + `.` = `?`, Shift + `/` = `\`,
Shift + ⏯ = next track.

```
SYM (one-shot)
  `     %     (     )     ;     ,          ·     ·     ·     ·     ·     ·
  !     {     '     "     }     ?          ·     ⇧     ⌘     ⌃     ⌥     ·
  #     ^     =     _     $     *          +     Bsp   Tab   Spc   .     usr
  ~     <     |     -     >     /          /     &     [     ]     @     (Ent)
                          :     \          ⇧     Base

NUM (hold G)
  ·     ·     ·     ·     ·     ·          ·     ·     ·     ·     ·     ·
  ·     ·     ·     ·     ·     ·          Tab   8     9     4     +     /
  ·     ⌥     ⌃     ⌘     ⇧     ·          :     1     2     3     -     *
  ·     ·     ·     ⇧     (G)   ·          ,     7     6     5     .     (Ent)
                          Base  Esc        0     Lock

NAV (hold Esc)
  (top row passes through from BASE)
  ·     ·     ⇧⌃Tab ⌃Tab  ·     ·          PgUp  Home  ↑     End   ·     (/)
  ·     ⌥     ⌃     ⌘     ⇧     SelLn      PgDn  ←     ↓     →     Del   ·
  ·     Undo  Cut   Copy  Paste ·          ·     SelW← SelW→ ·     ·     (Ent)
                          (Spc) (held)     (Rep) Lock

EXT (hold :) — Orbital Mouse
  (top row passes through from BASE)
  Fast  Undo  WhlL  Bsp   Spc   WhlR       WhlUp Click Fwd   RClk  Fast  (/)
  Slow  ⌥     ⌃     ⌘     ⇧     SelLn      WhlDn TurnL Back  TurnR Slow  ·
  (held) ·    Paste SelAl Copy  Cut        ·     ·     ·     ·     ·     (Ent)
                          Back  Click      Click Lock

FUN (F + N, one-shot)
  ·     ·     ·     ·     ·     ·          ·     ·     ·     ·     ·     Boot
  Lum   Fx→   Pal→  PalRn Pre1  Pre2       ·     F8    F9    F4    F11   ·
  SCase ⌥     ⌃     ⌘     ⇧     ·          ·     F1    F2    F3    F12   ·
  ·     Prev  Next  Vol-  Vol+  Mute       ·     F7    F6    F5    ·     Reboot
                          ·     ·          F10   Lock
```

- **Undo / Cut / Copy / Paste / SelAl (select all) / Back** send Cmd shortcuts
  on macOS and Ctrl (or Alt+Left for Back) elsewhere, using QMK OS detection.
- **SelW / SelLn**: [Select Word](https://github.com/getreuer/qmk-modules/tree/main/select_word)
  selects the word / line; press repeatedly to extend. Magic after it reverses.
- **Orbital Mouse**: Fwd/Back move along the current heading, TurnL/TurnR
  steer, Fast/Slow change speed.
- **Lum** cycles brightness off / 40% / 100%
  ([Lumino](https://github.com/getreuer/qmk-modules/tree/main/lumino)).
  **Fx→ / Pal→** step through [PaletteFx](https://github.com/getreuer/qmk-modules/tree/main/palettefx)
  effects / palettes (hold Shift to go back), **PalRn** picks a random
  palette, **Pre1 / Pre2** are presets.
- **SCase** toggles [Sentence Case](https://github.com/getreuer/qmk-modules/tree/main/sentence_case),
  which capitalizes the first letter of each sentence.
- **Boot** enters the bootloader for flashing; **Lock** is Layer Lock (60 s
  idle timeout).

### Status LEDs

| LED | Meaning |
|---|---|
| 1 (left, top) | A layer other than BASE is active (incl. a pending one-shot) |
| 2 (left, bottom) | Sentence Case will capitalize the next letter |
| 3 (right, top) | Caps Word is on |
| 4 (right, bottom) | A layer is locked |

### Tap-hold settings

Same approach as getreuer ([config_lakes26.h](config_lakes26.h),
[lakes26.c](lakes26.c)):

- 240 ms tapping term (195 ms for the Shift keys D and N).
- Chordal Hold: a home row mod only acts as a modifier when the next key is on
  the other hand.
- Permissive Hold.
- Flow Tap: no mods during fast typing.
- Speculative Hold: mods apply instantly, so Cmd/Shift + click don't lag.

## Files

| Path | Purpose |
|---|---|
| `qmk.json` | Build targets (`zsa/voyager:lakes26`) |
| `keyboards/zsa/voyager/keymaps/lakes26/keymap.c` | The layers and the Chordal Hold handedness map |
| `keyboards/zsa/voyager/keymaps/lakes26/keymap.json` | Community modules to enable |
| `keyboards/zsa/voyager/keymaps/lakes26/layout.h` | `LAYOUT_LR` macro (left half, then right half) |
| `keyboards/zsa/voyager/keymaps/lakes26/config.h`, `rules.mk` | Voyager-specific settings; include the shared ones below |
| `lakes26.c` | Keycodes, combos, key overrides, tap-hold callbacks, Magic key, macros, RGB, LEDs |
| `config_lakes26.h`, `rules.mk` | Shared feature configuration |
| `palettefx_user.inc` | Custom PaletteFx palettes |
| `modules/getreuer` | Submodule: [getreuer/qmk-modules](https://github.com/getreuer/qmk-modules) |

## Building and flashing

Clone with `git clone --recurse-submodules`, or run
`git submodule update --init` in an existing clone.

- **GitHub Actions:** every push builds the firmware and publishes
  `zsa_voyager_lakes26.bin` under Releases. The QMK version is pinned in
  [.github/workflows/build_binaries.yaml](.github/workflows/build_binaries.yaml).
- **Locally:** set up QMK (`curl -fsSL https://install.qmk.fm | sh`), check out
  the same QMK version (`git -C ~/qmk_firmware checkout 0.34.7 && qmk git-submodule`),
  then in this directory run `qmk config user.overlay_dir="$(realpath .)"` and
  `qmk compile -kb zsa/voyager -km lakes26`.

Flash the `.bin` with [Keymapp](https://www.zsa.io/flash). To enter the
bootloader, use the reset pinhole or press **F + N**, then **Boot** (top right).

## License

The userspace template is from [qmk/qmk_userspace](https://github.com/qmk/qmk_userspace)
(GPL-2.0, see [LICENSE](LICENSE)). Code adapted from
[getreuer/qmk-keymap](https://github.com/getreuer/qmk-keymap) is Copyright
Google LLC and licensed under the
[Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).
