# Custom keyboard layouts

* [NW1](keyboards/gmmk/gmmk2/p96/iso/keymaps/nw1/README.md) for [GMMK2 96% ISO](https://www.gloriousgaming.com/products/gmmk2)

## How to build

1. Setup QMK as described in [QMK Docs](https://docs.qmk.fm/#/newbs)
2. Clone this repo locally
3. Setup QMK to use this repo: 
```
$ qmk config user.overlay_dir="$(realpath qmk_userspace)"
```
4. Compile the firmware:
```
$ qmk compile -kb gmmk/gmmk2/p96/iso -km nw1
```

## How to flash

1. To flash put the keyboard into bootloader mode (by hitting the `QK_BOOT` keycode or [similar](https://docs.qmk.fm/#/newbs_flashing))
2. And initiate the flashing process:
```
$ qmk flash -kb gmmk/gmmk2/p96/iso -km nw1
```
