/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <raylib.h>

#include <iostream>
#include <string>
#include <vector>

typedef enum {
    K_NULL = 0, // Key: NULL, used for no key pressed
    // Alphanumeric keys
    K_APOSTROPHE = 39,    // Key: '
    K_COMMA = 44,         // Key: ,
    K_MINUS = 45,         // Key: -
    K_PERIOD = 46,        // Key: .
    K_SLASH = 47,         // Key: /
    K_ZERO = 48,          // Key: 0
    K_ONE = 49,           // Key: 1
    K_TWO = 50,           // Key: 2
    K_THREE = 51,         // Key: 3
    K_FOUR = 52,          // Key: 4
    K_FIVE = 53,          // Key: 5
    K_SIX = 54,           // Key: 6
    K_SEVEN = 55,         // Key: 7
    K_EIGHT = 56,         // Key: 8
    K_NINE = 57,          // Key: 9
    K_SEMICOLON = 59,     // Key: ;
    K_EQUAL = 61,         // Key: =
    K_A = 65,             // Key: A | a
    K_B = 66,             // Key: B | b
    K_C = 67,             // Key: C | c
    K_D = 68,             // Key: D | d
    K_E = 69,             // Key: E | e
    K_F = 70,             // Key: F | f
    K_G = 71,             // Key: G | g
    K_H = 72,             // Key: H | h
    K_I = 73,             // Key: I | i
    K_J = 74,             // Key: J | j
    K_K = 75,             // Key: K | k
    K_L = 76,             // Key: L | l
    K_M = 77,             // Key: M | m
    K_N = 78,             // Key: N | n
    K_O = 79,             // Key: O | o
    K_P = 80,             // Key: P | p
    K_Q = 81,             // Key: Q | q
    K_R = 82,             // Key: R | r
    K_S = 83,             // Key: S | s
    K_T = 84,             // Key: T | t
    K_U = 85,             // Key: U | u
    K_V = 86,             // Key: V | v
    K_W = 87,             // Key: W | w
    K_X = 88,             // Key: X | x
    K_Y = 89,             // Key: Y | y
    K_Z = 90,             // Key: Z | z
    K_LEFT_BRACKET = 91,  // Key: [
    K_BACKSLASH = 92,     // Key: '\'
    K_RIGHT_BRACKET = 93, // Key: ]
    K_GRAVE = 96,         // Key: `
    // Function keys
    K_SPACE = 32,          // Key: Space
    K_ESCAPE = 256,        // Key: Esc
    K_ENTER = 257,         // Key: Enter
    K_TAB = 258,           // Key: Tab
    K_BACKSPACE = 259,     // Key: Backspace
    K_INSERT = 260,        // Key: Ins
    K_DELETE = 261,        // Key: Del
    K_RIGHT = 262,         // Key: Cursor right
    K_LEFT = 263,          // Key: Cursor left
    K_DOWN = 264,          // Key: Cursor down
    K_UP = 265,            // Key: Cursor up
    K_PAGE_UP = 266,       // Key: Page up
    K_PAGE_DOWN = 267,     // Key: Page down
    K_HOME = 268,          // Key: Home
    K_END = 269,           // Key: End
    K_CAPS_LOCK = 280,     // Key: Caps lock
    K_SCROLL_LOCK = 281,   // Key: Scroll down
    K_NUM_LOCK = 282,      // Key: Num lock
    K_PRINT_SCREEN = 283,  // Key: Print screen
    K_PAUSE = 284,         // Key: Pause
    K_F1 = 290,            // Key: F1
    K_F2 = 291,            // Key: F2
    K_F3 = 292,            // Key: F3
    K_F4 = 293,            // Key: F4
    K_F5 = 294,            // Key: F5
    K_F6 = 295,            // Key: F6
    K_F7 = 296,            // Key: F7
    K_F8 = 297,            // Key: F8
    K_F9 = 298,            // Key: F9
    K_F10 = 299,           // Key: F10
    K_F11 = 300,           // Key: F11
    K_F12 = 301,           // Key: F12
    K_LEFT_SHIFT = 340,    // Key: Shift left
    K_LEFT_CONTROL = 341,  // Key: Control left
    K_LEFT_ALT = 342,      // Key: Alt left
    K_LEFT_SUPER = 343,    // Key: Super left
    K_RIGHT_SHIFT = 344,   // Key: Shift right
    K_RIGHT_CONTROL = 345, // Key: Control right
    K_RIGHT_ALT = 346,     // Key: Alt right
    K_RIGHT_SUPER = 347,   // Key: Super right
    K_KB_MENU = 348,       // Key: KB menu
    // Keypad keys
    K_KP_0 = 320,        // Key: Keypad 0
    K_KP_1 = 321,        // Key: Keypad 1
    K_KP_2 = 322,        // Key: Keypad 2
    K_KP_3 = 323,        // Key: Keypad 3
    K_KP_4 = 324,        // Key: Keypad 4
    K_KP_5 = 325,        // Key: Keypad 5
    K_KP_6 = 326,        // Key: Keypad 6
    K_KP_7 = 327,        // Key: Keypad 7
    K_KP_8 = 328,        // Key: Keypad 8
    K_KP_9 = 329,        // Key: Keypad 9
    K_KP_DECIMAL = 330,  // Key: Keypad .
    K_KP_DIVIDE = 331,   // Key: Keypad /
    K_KP_MULTIPLY = 332, // Key: Keypad *
    K_KP_SUBTRACT = 333, // Key: Keypad -
    K_KP_ADD = 334,      // Key: Keypad +
    K_KP_ENTER = 335,    // Key: Keypad Enter
    K_KP_EQUAL = 336,    // Key: Keypad =
    // ndroid key buttons
    K_BACK = 4,        // Key: Android back button
    K_MENU = 82,       // Key: Android menu button
    K_VOLUME_UP = 24,  // Key: Android volume up button
    K_VOLUME_DOWN = 25 // Key: Android volume down button
} KeyList;

struct vec2int {
    int x;
    int y;
};

class Event
{
  public:
    struct mouse_t {
        std::pair<float, float> pos = {0, 0};
        bool right = false;
        bool left = false;
        bool middle = false;
        bool isVisible = false;
    };

    explicit Event() noexcept = default;
    Event(const Event& other) noexcept = default;
    Event(Event&& other) noexcept = default;
    ~Event() noexcept = default;

    Event& operator=(const Event&) noexcept = default;
    Event& operator=(Event&&) noexcept = default;

    mouse_t& updateMouseInfo();
    std::vector<KeyList>& updateKeysPressed();
    std::pair<std::vector<KeyList>&, mouse_t&> updateEvents();
    mouse_t& getMouseInfo();
    std::vector<KeyList>& getKeysPressed();
    std::pair<std::vector<KeyList>&, mouse_t&> getEvents();

  protected:
  private:
    mouse_t mouse;
    std::vector<KeyList> keyPressed = {};
};

#endif /* !EVENT_HPP_ */
