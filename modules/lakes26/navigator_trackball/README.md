# Navigator Trackball (ported to upstream QMK)

QMK community module with the driver for the
[ZSA Navigator](https://www.zsa.io/navigator) trackball, so that it can be
used with upstream [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware)
instead of ZSA's fork.

This is a modified copy of the `navigator_trackball` module from
[zsa/qmk_modules](https://github.com/zsa/qmk_modules) at commit
[`13890cd`](https://github.com/zsa/qmk_modules/commit/13890cd7856175de20798689d15ba6a46bf0c5c7)
(2026-08-10). Copyright ZSA Technology Labs, Inc, licensed GPL-2.0-or-later
(see [LICENSE](LICENSE)).

## Changes from ZSA's version

1. `navigator_trackball.c`, `pointing_device_driver_init()`:
   - Returns `bool`, as upstream QMK requires since 2025. It always returns
     `true`: upstream QMK stops polling a pointing device for good when its
     init returns `false`.
   - Registers the polling callback even if the trackball is not detected, so
     it is probed again once per second. ZSA's version only does this after
     the trackball was detected once.
2. `navigator_trackball.c`, `sci18is606_configure()`: returns right away when
   the trackball does not answer, instead of waiting 10 ms first.
3. `qmk_module.json`: defines the trackball keycodes (`DRAG_SCROLL`,
   `TOGGLE_SCROLL`, `NAVIGATOR_INC_CPI`, ...). In ZSA's firmware they come from
   the `zsa/defaults` module, which can't be used with upstream QMK's Voyager
   code (both define `TOGGLE_LAYER_COLOR` and `LED_LEVEL`).

Everything else is unchanged. To pick up later fixes from ZSA, copy the files
from `zsa/qmk_modules` again and reapply these changes.

## Use

In `keymap.json`:

```json
{
    "modules": ["lakes26/navigator_trackball"]
}
```

Keycodes:

| Keycode | Alias | Description |
|---|---|---|
| `DRAG_SCROLL` | `NV_DSCR` | While held, the ball scrolls |
| `TOGGLE_SCROLL` | `NV_TSCR` | Toggle scrolling with the ball |
| `TOGGLE_SCROLL_VERTICAL` | `NV_VSCR` | Toggle vertical-only scrolling |
| `NAVIGATOR_INC_CPI` / `NAVIGATOR_DEC_CPI` | `NV_CPIU` / `NV_CPID` | Pointer speed up / down (not saved across restarts) |
| `NAVIGATOR_TURBO` / `NAVIGATOR_AIM` | `NV_TRBO` / `NV_AIM` | While held, faster / slower pointer |
| `TOGGLE_TURBO` / `TOGGLE_AIM` | `NV_TTRB` / `NV_TAIM` | Toggle faster / slower pointer |
| `NAVIGATOR_CLEAR_SPEED` | `NV_CSPD` | Turn off turbo and aim |

Options for `config.h` (defaults in parentheses):

| Option | Description |
|---|---|
| `NAVIGATOR_TRACKBALL_CPI` (40) | Pointer speed at startup, 5 to 125 |
| `NAVIGATOR_TRACKBALL_ROTATION` (0) | Rotate the ball's axes by this many degrees |
| `NAVIGATOR_DRAG_SCROLL_LAYERS` | List of layers on which the ball scrolls, e.g. `{5}` |
| `NAVIGATOR_TURBO_LAYERS`, `NAVIGATOR_AIM_LAYERS` | Layers with a faster / slower pointer |
| `NAVIGATOR_SCROLL_DIVIDER` (10) | Scroll sensitivity; lower is faster |
| `NAVIGATOR_SCROLL_INVERT_X`, `NAVIGATOR_SCROLL_INVERT_Y` | Reverse the scroll direction |
| `NAVIGATOR_TRACKBALL_SCROLL_ONLY` | The ball always scrolls |
