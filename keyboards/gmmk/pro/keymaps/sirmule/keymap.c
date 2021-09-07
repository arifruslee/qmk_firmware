/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum my_keycodes {
  DEF1 = SAFE_RANGE,
  PRNTHSV,
  RGBINDEXUP,
  RGBINDEXDOWN
};

uint16_t rgbIndex = 0;

// Indices//
//      ESC/0      F1/6       F2/12       F3/18       F4/23       F5/28       F6/34       F7/39       F8/44       F9/50       F10/56      F11/61      F12/66	     Prt/69               Rotary(Mute)
//      ~/1        1/7        2/13        3/19        4/24        5/29        6/35        7/40        8/45        9/51        0/57         -/62       (=)/78	     BackSpc/85           Del/72
//      Tab/2      Q/8        W/14        E/20        R/25        T/30        Y/36        U/41        I/46        O/52        P/58        [/63        ]/89           \/93                 PgUp/75
//      Caps/3     A/9        S/15        D/21        F/26        G/31        H/37        J/42        K/47        L/53        ;/59        "/64                       Enter/96             PgDn/86
//      Sh_L/4     Z/10       X/16        C/22        V/27        B/32        N/38        M/43        ,/48        ./54        ?/60                 	  Sh_R/90        Up/94                End/82
//      Ct_L/5     Win_L/11   Alt_L/17                               SPACE/33                         Alt_R/49    FN/55       			  Ct_R/65     Left/95        Down/97              Right/79

// Indices do NOT have to be listed in ascending order for this to work, I just thought it looked nice.
int LAY1_A[] = {1,72,8,14,9,15,10,52,58,47,53,38,43,82};
int LAY1_B[] = {93};
int LAY1_C[] = {6,12,69};

int LAY_Caps[] = {0,6,12,18,23,28,34,39,44,50,56,61,66,69,72,75,86,82,79,97,95,65,55,49,33,17,11,5,4,3,2,1};

// Find sizes of the arrays using a method described here: https://www.geeksforgeeks.org/how-to-find-size-of-array-in-cc-without-using-sizeof-operator/
int LAY1_A_SIZE = *(&LAY1_A + 1) - LAY1_A;
int LAY1_B_SIZE = *(&LAY1_B + 1) - LAY1_B;
int LAY1_C_SIZE = *(&LAY1_C + 1) - LAY1_C;

int LAY_Caps_SIZE = *(&LAY_Caps + 1) - LAY_Caps;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [0] = LAYOUT(
	KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_MUTE,
	KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
	KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
	KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END,
	KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),
	[1] = LAYOUT(
	KC_TRNS, RGBINDEXUP, RGBINDEXDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, PRNTHSV, KC_TRNS,
	RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
	KC_TRNS, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUD, RGB_HUI, KC_TRNS, KC_TRNS, RESET, KC_TRNS,
	KC_TRNS, RGB_SPD, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAD, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, DEF1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

// These shorthands are used below to set led colors on each matrix cycle
//Pink ALL
void all_colorset_A(void) {
    rgb_matrix_sethsv(200, 143, 159);
}
//Orange
void loop_colorset_Orange(int *indices, int array_size) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], 255, 153, 0);
  }
}
//Red
void loop_colorset_Red(int *indices, int array_size) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], 255, 0, 0);
  }
}
//Blue
void loop_colorset_Blue(int *indices, int array_size) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], 51, 51, 255);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case DEF1:
		all_colorset_A();
		return false; // skip all further processing of this key'
	case PRNTHSV:
		// If console is enabled, it will print the matrix position and status of each key pressed
		#ifdef CONSOLE_ENABLE
			if (record->event.pressed) {
				uprintf("h: %d, s: %d, v: %d\n", rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val());
			}
		#endif
		return false; // skip all further processing of this key
	case RGBINDEXUP:
		// If console is enabled, it will print the matrix position and status of each key pressed
		#ifdef CONSOLE_ENABLE
			if (record->event.pressed) {
				if (rgbIndex < DRIVER_LED_TOTAL)
					rgbIndex = rgbIndex + 1;
				uprintf("RGB Index: %d\n", rgbIndex);				
			}
		#endif
		return false; // skip all further processing of this key
	case RGBINDEXDOWN:
		// If console is enabled, it will print the matrix position and status of each key pressed
		#ifdef CONSOLE_ENABLE
			if (record->event.pressed) {
				if (rgbIndex > 0)
					rgbIndex = rgbIndex - 1;
				uprintf("RGB Index: %d\n", rgbIndex);			
			}
		#endif
		return false; // skip all further processing of this key
    default:
		return true; // process all other keycodes normally
  }  
}

// Code to change some led colors on layer change, using the above function
void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
	case 1:
      loop_colorset_Orange(LAY1_A, LAY1_A_SIZE);  // Set LEDs listed to Orange
	  loop_colorset_Red(LAY1_B, LAY1_B_SIZE);  // Set LEDs listed to Red
	  loop_colorset_Blue(LAY1_C, LAY1_C_SIZE);  // Set LEDs listed to Blue
      break;
    default:
	  //Indicator Capslock
	  if (host_keyboard_led_state().caps_lock)
		loop_colorset_Red(LAY_Caps, LAY_Caps_SIZE);
	  else
		all_colorset_A();
	  break;
  }
  #endif
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}
