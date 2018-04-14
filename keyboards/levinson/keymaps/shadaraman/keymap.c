#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 3
#define _RAISE 4
#define _NUMBER 5
#define _SYMBOL 6
#define _NAV 7
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  NUMBER,
  SYMBOL,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom aliases
#define KC_STAB SFT_T(KC_TAB)
#define KC_WINL LCTL(LALT(KC_LEFT))
#define KC_WIND LCTL(LALT(KC_DOWN))
#define KC_WINU LCTL(LALT(KC_UP))
#define KC_WINR LCTL(LALT(KC_RGHT))
#define KC_CAD  LCTL(LALT(KC_DEL))
#define KC_OSFT OSM(MOD_LSFT)
#define KC_QSFT SFT_T(KC_QUOT)
#define NAV MO(_NAV)
#define KC_CTLZ  LCTL(KC_Z)
#define KC_CTLC  LCTL(KC_C)
#define KC_CTLX  LCTL(KC_X)
#define KC_CTLV  LCTL(KC_V)
#define KC_CTLY  LCTL(KC_Y)
#define KC_CBSP  CTL_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CtlBsp|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Nav  | Alt  |Adjust|Lower |Enter |Space |Raise | GUI  | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_CBSP, KC_A,    KC_S,    KC_D,  KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_OSFT, KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_OSFT, \
  KC_ESC,  NAV,     KC_LALT, ADJUST,SYMBOL,  KC_ENT,  KC_SPC,  NUMBER,  KC_LGUI, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Colemak (Mod-DH)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CtlBsp|   A  |   R  |   S  |   T  |   G  |   K  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   D  |   V  |   M  |   H  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Nav  | Alt  |Adjust|Lower |Enter |Space |Raise | GUI  | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,  KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_CBSP, KC_A,    KC_R,    KC_S,  KC_T,    KC_G,    KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_OSFT, KC_Z,    KC_X,    KC_C,  KC_D,    KC_V,    KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_OSFT, \
  KC_ESC,  NAV,     KC_LALT, ADJUST,SYMBOL,  KC_ENT,  KC_SPC,  NUMBER,  KC_LGUI, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left |  Up  | Down |Right |  *   |  =   |   4  |   5  |   6  |   +  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |   .  |   =  |   /  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7, KC_8,  KC_9,   KC_0,    KC_DEL, \
  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_AMPR, KC_EQL,     KC_4, KC_5,  KC_6,   KC_PLUS, KC_PIPE, \
  _______, _______, _______, _______, _______, KC_SLSH, KC_UNDS,    KC_1, KC_2,  KC_3,   KC_MINS, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,  KC_DOT, KC_EQL,  KC_SLSH \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Home | PgUp | PgDn | End  |   {  |   }  | Left | Down |  Up  |Right |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |   (  |   [  |   ]  |   )  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  _______, KC_HOME, KC_PGUP, KC_PGDN,  KC_END,  KC_LCBR,  KC_RCBR,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSLS, \
  _______, _______, _______, _______, KC_LPRN,  KC_LBRC,  KC_RBRC,  KC_RPRN, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,  _______,  _______,  _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Number
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = KEYMAP( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   =  |   [  |   {  |   (  |  +   |   _  |   )  |   }  |   ]  |   -  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
  KC_GRV,  KC_EQL, KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS, KC_UNDS, KC_RPRN, KC_RCBR, KC_RBRC, KC_MINS, KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Nav (Symbol + Number)
 * ,-----------------------------------------------------------------------------------.
 * |      | Esc  |  OS  | Back | Fwd  |WhlUp | PgUp | Home |  Up  | End  | Del  | Ins  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Alt  |  ^Y  |Shift | Ctrl |WhlDn | PgDn | Left | Down |Right | Bspc |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  ^Z  |  ^X  |  ^C  |  ^V  |  ^V  | Calc | CAD  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Sleep |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = KEYMAP( \
  _______, KC_ESC,  KC_LGUI, KC_WBAK, KC_WFWD, KC_WH_U,  KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_DEL,  KC_INS, \
  _______, KC_LALT, KC_CTLY, KC_LSFT, KC_LCTL, KC_WH_D,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_ENT, \
  _______, KC_CTLZ, KC_CTLX, KC_CTLC, KC_CTLV, KC_CTLV,  KC_CALC, KC_CAD,  _______, _______, _______, _______, \
  KC_SLEP, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Mute | Vol- | Vol+ | Play |Sleep | Calc |WLeft |WDown | WUp  |WRight|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Prev |      |      | Next |  CAD |      |      |      |      |AGnorm|AGswap|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Qwerty|Colemk|Reset |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , \
  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_SLEP, KC_CALC, KC_WINL, KC_WIND, KC_WINU, KC_WINR, _______, \
  _______, KC_MPRV, _______, _______, KC_MNXT, KC_CAD , _______, _______, _______, _______, AG_NORM, AG_SWAP, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY , COLEMAK, RESET \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NUMBER:
      if (record->event.pressed) {
        layer_on(_NUMBER);
        update_tri_layer(_NUMBER, _SYMBOL, _NAV);
      } else {
        layer_off(_NUMBER);
        update_tri_layer(_NUMBER, _SYMBOL, _NAV);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer(_NUMBER, _SYMBOL, _NAV);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer(_NUMBER, _SYMBOL, _NAV);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
