#include "print.h"
#include QMK_KEYBOARD_H

/* layer names */
#define _DL 0
#define _FL 1

/* tap dance */
enum {
    _DC,
};

tap_dance_action_t tap_dance_actions[] = {
    // tap once for KC_DOT, twice for KC_COMM
    [_DC] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
};

/* function layer tap */
#define _FLTAP LGUI_T(KC_F13)
#define _FLTAP_TIMEOUT 300 // ms.

/* variables to track keyboard state */
static bool _fltap_active = false;
static uint16_t _fltap_timer = 0;

/* layers */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* default layer */
  [_DL] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
  // │ ESC    │ F1     │ F2     │ F3     │ F4     │ F5     │ F6     │ F7     │ F8     │ F9     │ F10    │ F11    │ F12    │ DEL    │ HOME   │ END    │ PSCR   │ PGUP   │
       QK_GESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL , KC_HOME, KC_END , KC_PSCR, KC_PGUP,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ °      │ 1      │ 2      │ 3      │ 4      │ 5      │ 6      │ 7      │ 8      │ 9      │ 0      │ ß      │ ´      │ BSPC   │ NUM    │ ÷      │ *      │ -      │
       KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_PSLS, KC_PAST, KC_PMNS,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ TAB    │ q      │ w      │ e      │ r      │ t      │ z      │ u      │ i      │ o      │ p      │ ü      │ +      │ ENT    │ 7      │ 8      │ 9      │ +      │
       KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O,    KC_P   , KC_LBRC, KC_RBRC, KC_ENT , KC_P7  , KC_P8  , KC_P9,   KC_PPLS,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┤        │
  // │ CAPS   │ a      │ s      │ d      │ f      │ g      │ h      │ j      │ k      │ l      │ ö      │ ä      │ #      │        │ 4      │ 5      │ 6      │        │
       KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,          KC_P4,   KC_P5  , KC_P6  ,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ LSFT   │ <      │ y      │ x      │ c      │ v      │ b      │ n      │ m      │ ,      │ .      │ -      │ RSFT   │ UP     │ 1      │ 2      │ 3      │ ENT    │
       KC_LSFT, KC_NUBS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_UP,   KC_P1,   KC_P2  , KC_P3,   KC_PENT,
  // ├────────┼────────┼────────┼────────┴────────┴────────┴────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤        │
  // │ LCTL   │ WIN    │ LALT   │                   SPC                               │ RALT   │ FN     │ RCTL   │ LEFT   │ DOWN   │ RGHT   │ 0      │ ,      │        │
       KC_LCTL, _FLTAP , KC_LALT,                   KC_SPC                            , KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0  , TD(_DC)
  // ╰────────┴────────┴────────┴─────────────────────────────────────────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────╯
  ),

  /* functions layer */
  [_FL] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
  // │ ESC    │ F1     │ F2     │ F3     │ F4     │ F5     │ F6     │ F7     │ F8     │ F9     │ F10    │ F11    │ F12    │ DEL    │ HOME   │ END    │ PSCR   │ PGUP   │
       _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MRWD, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLU, KC_VOLD, _______, _______, _______, _______, DB_TOGG, QK_BOOT,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ °      │ 1      │ 2      │ 3      │ 4      │ 5      │ 6      │ 7      │ 8      │ 9      │ 0      │ ß      │ ´      │ BSPC   │ NUM    │ ÷      │ *      │ -      │
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NUM , _______, _______, _______,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ TAB    │ q      │ w      │ e      │ r      │ t      │ z      │ u      │ i      │ o      │ p      │ ü      │ +      │ ENT    │ 7      │ 8      │ 9      │ +      │
       _______, RGB_TOG, _______, RGB_MOD, RGB_SAI, RGB_HUI, _______, _______, _______, _______, _______, _______, RGB_SPI, _______, _______, _______, _______, _______,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┤        │
  // │ CAPS   │ a      │ s      │ d      │ f      │ g      │ h      │ j      │ k      │ l      │ ö      │ ä      │ #      │        │ 4      │ 5      │ 6      │        │
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,          _______, _______, _______,
  // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  // │ LSFT   │ <      │ y      │ x      │ c      │ v      │ b      │ n      │ m      │ ,      │ .      │ -      │ RSFT   │ UP     │ 1      │ 2      │ 3      │ ENT    │
       _______, _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,_______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______,
  // ├────────┼────────┼────────┼────────┴────────┴────────┴────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤        │
  // │ LCTL   │ WIN    │ LALT   │                   SPC                               │ RALT   │ FN     │ RCTL   │ LEFT   │ DOWN   │ RGHT   │ 0      │ ,      │        │
       _______, _______, _______,                   _______                           , _______, _______, _______, KC_HOME, KC_PGDN, KC_END , _______, _______
  // ╰────────┴────────┴────────┴─────────────────────────────────────────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────╯
  )
};

/* customizing function */
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case _FLTAP:
      if (!_fltap_active && record->tap.count) { // on tap
        if (record->event.pressed) { // key press
          dprint("set_oneshot_layer\n");
          set_oneshot_layer(_FL, ONESHOT_START);
          _fltap_active = true;
          _fltap_timer = timer_read();
        }
        return false; // ignore further processing of key
      }
      break;
    default:
      if (_fltap_active && !record->event.pressed) {
        dprint("clear_oneshot_layer_state\n");
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        _fltap_active = false;
      }
  }
  return true; // Continue default handling.
}

/* custom processing */
void matrix_scan_user(void) {
  if (_fltap_active) {
    dprintf("_fltap_active, elapsed: %d\n", timer_elapsed(_fltap_timer));
    if (timer_elapsed(_fltap_timer) > _FLTAP_TIMEOUT) {
      // timeout occurred, deactivate layer
      dprint("timeout! clear_oneshot_layer_state\n");
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      _fltap_active = false;
    }
  }
}
