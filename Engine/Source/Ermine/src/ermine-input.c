#include "ermine.h"
#include "ermine-input.h"

#define MAX_KEYBOARD_KEYS 512
#define MAX_MOUSE_BUTTONS 8
#define MAX_GAMEPADS 4
#define MAX_GAMEPAD_AXIS 8
#define MAX_GAMEPAD_BUTTONS 32
#define MAX_TOUCH_POINTS 8

// STATE EVENTS
typedef struct InputCore
{
    struct
    {
        char currentButtonState[MAX_MOUSE_BUTTONS];
        char previousButtonState[MAX_MOUSE_BUTTONS];
    } Mouse;

    struct
    {
        char currentTouchState[MAX_TOUCH_POINTS];
        char previousTouchState[MAX_TOUCH_POINTS];
        evect2 position;
    } Touch;

    struct
    {
        char currentKeyState[MAX_KEYBOARD_KEYS];
        char previousKeyState[MAX_KEYBOARD_KEYS];
    } Key;

    struct
    {
        char currentButtonState[MAX_GAMEPADS][MAX_GAMEPAD_BUTTONS];
        char previousButtonState[MAX_GAMEPADS][MAX_GAMEPAD_BUTTONS];
    } GamePad;
} InputCore;

InputCore Input;

//

void init_input(void)
{
}

void input_pollinput(void)
{
    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) Input.Key.previousKeyState[i] = Input.Key.currentKeyState[i];
    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) Input.Mouse.previousButtonState[i] = Input.Mouse.currentButtonState[i];
}

void input_key_set_down(int key)
{
    Input.Key.currentKeyState[key] = 1;
}

void input_key_set_up(int key)
{
    Input.Key.currentKeyState[key] = 0;
}

// INPUT KEYBOARD

bool is_key_pressed(int key)
{
    bool pressed = false;

    if (Input.Key.previousKeyState[key] == 0 && Input.Key.currentKeyState[key] == 1)
        pressed = true;

    return pressed;
}

bool is_key_down(int key)
{
    if (Input.Key.currentKeyState[key] == 1)
        return true;
    else
        return false;
}

bool is_key_relased(int key)
{
    bool released = false;
    if (Input.Key.previousKeyState[key] == 1 && Input.Key.currentKeyState[key] == 0)
        released = true;
    return released;
}

bool is_key_up(int key)
{
    if (Input.Key.currentKeyState[key] == 0)
        return true;
    else
        return false;
}

// INPUT MOUSE

bool is_mouse_button_down(int button)
{
    bool down = false;
    if (Input.Mouse.currentButtonState[button] == 1)
        down = true;

    return down;
}

// INPUT GAMEDPAD
