// Copyright 2014 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FPLBASE_KEYBOARD_KEYCODES_H
#define FPLBASE_KEYBOARD_KEYCODES_H

#include <stdint.h>
#include "fplbase/config.h"  // Must come first.

#include "keyboard_scancodes.h"

namespace fplbase {

/// @file
/// @defgroup fplbase_key_codes Key Codes
/// @brief Keyboard key codes used by FPLBase, which correspond to a key press's
/// value, as mapped by the current operating system. This is ideal for
/// character-dependent controls.
///
/// For example, let's imagine a game that requires the `a` key to be pressed to
/// trigger `a` for <b>a</b>ttack. If a player mapped a given key (`a`),
/// on the physical keyboard, to produce the German a-umlaut (`ä`), then this
/// key would no longer produce the `FPLK_a` keycode (but it <b>would</b> still
/// produce the `FPL_SCANCODE_A`, which may not be what the user expects).
///
/// Let's pretend they now have mapped `F1` to generate the actual `a`
/// keystroke. They would expect to press `F1` to generate the `a` keystroke for
/// <b>a</b>ttack, which would correctly correspond to the `FPLK_a`
/// keycode, but would generate the incorrect scancode `FPL_SCANCODE_F1`.
///
/// @ingroup fplbase_keyboardcodes
/// @{

// Keycodes used by FPL:

typedef int32_t FPL_Keycode;

#define FPLK_SCANCODE_MASK (1 << 30)
#define FPL_SCANCODE_TO_KEYCODE(X) (X | FPLK_SCANCODE_MASK)

enum {
  FPLK_UNKNOWN = 0,
  FPLK_RETURN = '\r',
  FPLK_ESCAPE = '\033',
  FPLK_BACKSPACE = '\b',
  FPLK_TAB = '\t',
  FPLK_SPACE = ' ',
  FPLK_EXCLAIM = '!',
  FPLK_QUOTEDBL = '"',
  FPLK_HASH = '#',
  FPLK_PERCENT = '%',
  FPLK_DOLLAR = '$',
  FPLK_AMPERSAND = '&',
  FPLK_QUOTE = '\'',
  FPLK_LEFTPAREN = '(',
  FPLK_RIGHTPAREN = ')',
  FPLK_ASTERISK = '*',
  FPLK_PLUS = '+',
  FPLK_COMMA = ',',
  FPLK_MINUS = '-',
  FPLK_PERIOD = '.',
  FPLK_SLASH = '/',
  FPLK_0 = '0',
  FPLK_1 = '1',
  FPLK_2 = '2',
  FPLK_3 = '3',
  FPLK_4 = '4',
  FPLK_5 = '5',
  FPLK_6 = '6',
  FPLK_7 = '7',
  FPLK_8 = '8',
  FPLK_9 = '9',
  FPLK_COLON = ':',
  FPLK_SEMICOLON = ';',
  FPLK_LESS = '<',
  FPLK_EQUALS = '=',
  FPLK_GREATER = '>',
  FPLK_QUESTION = '?',
  FPLK_AT = '@',
  /*
     Skip uppercase letters
   */
  FPLK_LEFTBRACKET = '[',
  FPLK_BACKSLASH = '\\',
  FPLK_RIGHTBRACKET = ']',
  FPLK_CARET = '^',
  FPLK_UNDERSCORE = '_',
  FPLK_BACKQUOTE = '`',
  FPLK_a = 'a',
  FPLK_b = 'b',
  FPLK_c = 'c',
  FPLK_d = 'd',
  FPLK_e = 'e',
  FPLK_f = 'f',
  FPLK_g = 'g',
  FPLK_h = 'h',
  FPLK_i = 'i',
  FPLK_j = 'j',
  FPLK_k = 'k',
  FPLK_l = 'l',
  FPLK_m = 'm',
  FPLK_n = 'n',
  FPLK_o = 'o',
  FPLK_p = 'p',
  FPLK_q = 'q',
  FPLK_r = 'r',
  FPLK_s = 's',
  FPLK_t = 't',
  FPLK_u = 'u',
  FPLK_v = 'v',
  FPLK_w = 'w',
  FPLK_x = 'x',
  FPLK_y = 'y',
  FPLK_z = 'z',
  FPLK_CAPSLOCK = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CAPSLOCK),
  FPLK_F1 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F1),
  FPLK_F2 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F2),
  FPLK_F3 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F3),
  FPLK_F4 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F4),
  FPLK_F5 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F5),
  FPLK_F6 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F6),
  FPLK_F7 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F7),
  FPLK_F8 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F8),
  FPLK_F9 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F9),
  FPLK_F10 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F10),
  FPLK_F11 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F11),
  FPLK_F12 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F12),
  FPLK_PRINTSCREEN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PRINTSCREEN),
  FPLK_SCROLLLOCK = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_SCROLLLOCK),
  FPLK_PAUSE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PAUSE),
  FPLK_INSERT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_INSERT),
  FPLK_HOME = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_HOME),
  FPLK_PAGEUP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PAGEUP),
  FPLK_DELETE = '\177',
  FPLK_END = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_END),
  FPLK_PAGEDOWN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PAGEDOWN),
  FPLK_RIGHT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RIGHT),
  FPLK_LEFT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_LEFT),
  FPLK_DOWN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_DOWN),
  FPLK_UP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_UP),
  FPLK_NUMLOCKCLEAR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_NUMLOCKCLEAR),
  FPLK_KP_DIVIDE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_DIVIDE),
  FPLK_KP_MULTIPLY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MULTIPLY),
  FPLK_KP_MINUS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MINUS),
  FPLK_KP_PLUS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_PLUS),
  FPLK_KP_ENTER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_ENTER),
  FPLK_KP_1 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_1),
  FPLK_KP_2 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_2),
  FPLK_KP_3 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_3),
  FPLK_KP_4 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_4),
  FPLK_KP_5 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_5),
  FPLK_KP_6 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_6),
  FPLK_KP_7 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_7),
  FPLK_KP_8 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_8),
  FPLK_KP_9 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_9),
  FPLK_KP_0 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_0),
  FPLK_KP_PERIOD = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_PERIOD),
  FPLK_APPLICATION = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_APPLICATION),
  FPLK_POWER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_POWER),
  FPLK_KP_EQUALS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_EQUALS),
  FPLK_F13 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F13),
  FPLK_F14 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F14),
  FPLK_F15 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F15),
  FPLK_F16 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F16),
  FPLK_F17 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F17),
  FPLK_F18 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F18),
  FPLK_F19 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F19),
  FPLK_F20 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F20),
  FPLK_F21 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F21),
  FPLK_F22 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F22),
  FPLK_F23 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F23),
  FPLK_F24 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_F24),
  FPLK_EXECUTE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_EXECUTE),
  FPLK_HELP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_HELP),
  FPLK_MENU = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_MENU),
  FPLK_SELECT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_SELECT),
  FPLK_STOP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_STOP),
  FPLK_AGAIN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AGAIN),
  FPLK_UNDO = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_UNDO),
  FPLK_CUT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CUT),
  FPLK_COPY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_COPY),
  FPLK_PASTE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PASTE),
  FPLK_FIND = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_FIND),
  FPLK_MUTE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_MUTE),
  FPLK_VOLUMEUP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_VOLUMEUP),
  FPLK_VOLUMEDOWN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_VOLUMEDOWN),
  FPLK_KP_COMMA = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_COMMA),
  FPLK_KP_EQUALSAS400 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_EQUALSAS400),
  FPLK_ALTERASE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_ALTERASE),
  FPLK_SYSREQ = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_SYSREQ),
  FPLK_CANCEL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CANCEL),
  FPLK_CLEAR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CLEAR),
  FPLK_PRIOR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_PRIOR),
  FPLK_RETURN2 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RETURN2),
  FPLK_SEPARATOR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_SEPARATOR),
  FPLK_OUT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_OUT),
  FPLK_OPER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_OPER),
  FPLK_CLEARAGAIN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CLEARAGAIN),
  FPLK_CRSEL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CRSEL),
  FPLK_EXSEL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_EXSEL),
  FPLK_KP_00 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_00),
  FPLK_KP_000 = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_000),
  FPLK_THOUSANDSSEPARATOR =
      FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_THOUSANDSSEPARATOR),
  FPLK_DECIMALSEPARATOR =
      FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_DECIMALSEPARATOR),
  FPLK_CURRENCYUNIT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CURRENCYUNIT),
  FPLK_CURRENCYSUBUNIT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CURRENCYSUBUNIT),
  FPLK_KP_LEFTPAREN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_LEFTPAREN),
  FPLK_KP_RIGHTPAREN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_RIGHTPAREN),
  FPLK_KP_LEFTBRACE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_LEFTBRACE),
  FPLK_KP_RIGHTBRACE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_RIGHTBRACE),
  FPLK_KP_TAB = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_TAB),
  FPLK_KP_BACKSPACE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_BACKSPACE),
  FPLK_KP_A = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_A),
  FPLK_KP_B = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_B),
  FPLK_KP_C = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_C),
  FPLK_KP_D = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_D),
  FPLK_KP_E = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_E),
  FPLK_KP_F = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_F),
  FPLK_KP_XOR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_XOR),
  FPLK_KP_POWER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_POWER),
  FPLK_KP_PERCENT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_PERCENT),
  FPLK_KP_LESS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_LESS),
  FPLK_KP_GREATER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_GREATER),
  FPLK_KP_AMPERSAND = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_AMPERSAND),
  FPLK_KP_DBLAMPERSAND = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_DBLAMPERSAND),
  FPLK_KP_VERTICALBAR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_VERTICALBAR),
  FPLK_KP_DBLVERTICALBAR =
      FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_DBLVERTICALBAR),
  FPLK_KP_COLON = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_COLON),
  FPLK_KP_HASH = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_HASH),
  FPLK_KP_SPACE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_SPACE),
  FPLK_KP_AT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_AT),
  FPLK_KP_EXCLAM = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_EXCLAM),
  FPLK_KP_MEMSTORE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMSTORE),
  FPLK_KP_MEMRECALL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMRECALL),
  FPLK_KP_MEMCLEAR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMCLEAR),
  FPLK_KP_MEMADD = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMADD),
  FPLK_KP_MEMSUBTRACT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMSUBTRACT),
  FPLK_KP_MEMMULTIPLY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMMULTIPLY),
  FPLK_KP_MEMDIVIDE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_MEMDIVIDE),
  FPLK_KP_PLUSMINUS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_PLUSMINUS),
  FPLK_KP_CLEAR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_CLEAR),
  FPLK_KP_CLEARENTRY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_CLEARENTRY),
  FPLK_KP_BINARY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_BINARY),
  FPLK_KP_OCTAL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_OCTAL),
  FPLK_KP_DECIMAL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_DECIMAL),
  FPLK_KP_HEXADECIMAL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KP_HEXADECIMAL),
  FPLK_LCTRL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_LCTRL),
  FPLK_LSHIFT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_LSHIFT),
  FPLK_LALT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_LALT),
  FPLK_LGUI = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_LGUI),
  FPLK_RCTRL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RCTRL),
  FPLK_RSHIFT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RSHIFT),
  FPLK_RALT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RALT),
  FPLK_RGUI = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_RGUI),
  FPLK_MODE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_MODE),
  FPLK_AUDIONEXT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AUDIONEXT),
  FPLK_AUDIOPREV = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AUDIOPREV),
  FPLK_AUDIOSTOP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AUDIOSTOP),
  FPLK_AUDIOPLAY = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AUDIOPLAY),
  FPLK_AUDIOMUTE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AUDIOMUTE),
  FPLK_MEDIASELECT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_MEDIASELECT),
  FPLK_WWW = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_WWW),
  FPLK_MAIL = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_MAIL),
  FPLK_CALCULATOR = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_CALCULATOR),
  FPLK_COMPUTER = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_COMPUTER),
  FPLK_AC_SEARCH = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_SEARCH),
  FPLK_AC_HOME = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_HOME),
  FPLK_AC_BACK = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_BACK),
  FPLK_AC_FORWARD = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_FORWARD),
  FPLK_AC_STOP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_STOP),
  FPLK_AC_REFRESH = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_REFRESH),
  FPLK_AC_BOOKMARKS = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_AC_BOOKMARKS),
  FPLK_BRIGHTNESSDOWN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_BRIGHTNESSDOWN),
  FPLK_BRIGHTNESSUP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_BRIGHTNESSUP),
  FPLK_DISPLAYSWITCH = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_DISPLAYSWITCH),
  FPLK_KBDILLUMTOGGLE = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KBDILLUMTOGGLE),
  FPLK_KBDILLUMDOWN = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KBDILLUMDOWN),
  FPLK_KBDILLUMUP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_KBDILLUMUP),
  FPLK_EJECT = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_EJECT),
  FPLK_SLEEP = FPL_SCANCODE_TO_KEYCODE(FPL_SCANCODE_SLEEP)
};

/**
 * \brief Enumeration of valid key mods (possibly OR'd together).
 */
typedef enum {
  FPL_KMOD_NONE = 0x0000,
  FPL_KMOD_LSHIFT = 0x0001,
  FPL_KMOD_RSHIFT = 0x0002,
  FPL_KMOD_LCTRL = 0x0040,
  FPL_KMOD_RCTRL = 0x0080,
  FPL_KMOD_LALT = 0x0100,
  FPL_KMOD_RALT = 0x0200,
  FPL_KMOD_LGUI = 0x0400,
  FPL_KMOD_RGUI = 0x0800,
  FPL_KMOD_NUM = 0x1000,
  FPL_KMOD_CAPS = 0x2000,
  FPL_KMOD_MODE = 0x4000,
  FPL_KMOD_RESERVED = 0x8000
} FPL_Keymod;

#define FPL_KMOD_CTRL (::fplbase::FPL_KMOD_LCTRL | ::fplbase::FPL_KMOD_RCTRL)
#define FPL_KMOD_SHIFT (::fplbase::FPL_KMOD_LSHIFT | ::fplbase::FPL_KMOD_RSHIFT)
#define FPL_KMOD_ALT (::fplbase::FPL_KMOD_LALT | ::fplbase::FPL_KMOD_RALT)
#define FPL_KMOD_GUI (::fplbase::FPL_KMOD_LGUI | ::fplbase::FPL_KMOD_RGUI)

/// @}
}  // namespace fplbase

#endif  // FPLBASE_KEYBOARD_KEYCODES_H
