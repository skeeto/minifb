#ifndef _MINIFB_H_
#define _MINIFB_H_

#include <stdint.h>
#include <stdbool.h>

#ifndef MFB_API
#  if _WIN32
#    define MFB_API __declspec(dllimport)
#  else
#    define MFB_API
#  endif
#endif

// Enums
typedef enum {
    STATE_OK             =  0,
    STATE_EXIT           = -1,
    STATE_INVALID_WINDOW = -2,
    STATE_INVALID_BUFFER = -3,
    STATE_INTERNAL_ERROR = -4,
} mfb_update_state;

typedef enum {
    MOUSE_BTN_0, // No mouse button
    MOUSE_BTN_1,
    MOUSE_BTN_2,
    MOUSE_BTN_3,
    MOUSE_BTN_4,
    MOUSE_BTN_5,
    MOUSE_BTN_6,
    MOUSE_BTN_7,
} mfb_mouse_button;
#define MOUSE_LEFT   MOUSE_BTN_1
#define MOUSE_RIGHT  MOUSE_BTN_2
#define MOUSE_MIDDLE MOUSE_BTN_3

typedef enum {
    KB_KEY_UNKNOWN       = -1,

    KB_KEY_SPACE         = 32,
    KB_KEY_APOSTROPHE    = 39,
    KB_KEY_COMMA         = 44,
    KB_KEY_MINUS         = 45,
    KB_KEY_PERIOD        = 46,
    KB_KEY_SLASH         = 47,
    KB_KEY_0             = 48,
    KB_KEY_1             = 49,
    KB_KEY_2             = 50,
    KB_KEY_3             = 51,
    KB_KEY_4             = 52,
    KB_KEY_5             = 53,
    KB_KEY_6             = 54,
    KB_KEY_7             = 55,
    KB_KEY_8             = 56,
    KB_KEY_9             = 57,
    KB_KEY_SEMICOLON     = 59,
    KB_KEY_EQUAL         = 61,
    KB_KEY_A             = 65,
    KB_KEY_B             = 66,
    KB_KEY_C             = 67,
    KB_KEY_D             = 68,
    KB_KEY_E             = 69,
    KB_KEY_F             = 70,
    KB_KEY_G             = 71,
    KB_KEY_H             = 72,
    KB_KEY_I             = 73,
    KB_KEY_J             = 74,
    KB_KEY_K             = 75,
    KB_KEY_L             = 76,
    KB_KEY_M             = 77,
    KB_KEY_N             = 78,
    KB_KEY_O             = 79,
    KB_KEY_P             = 80,
    KB_KEY_Q             = 81,
    KB_KEY_R             = 82,
    KB_KEY_S             = 83,
    KB_KEY_T             = 84,
    KB_KEY_U             = 85,
    KB_KEY_V             = 86,
    KB_KEY_W             = 87,
    KB_KEY_X             = 88,
    KB_KEY_Y             = 89,
    KB_KEY_Z             = 90,
    KB_KEY_LEFT_BRACKET  = 91,
    KB_KEY_BACKSLASH     = 92,
    KB_KEY_RIGHT_BRACKET = 93,
    KB_KEY_GRAVE_ACCENT  = 96,
    KB_KEY_WORLD_1       = 161,
    KB_KEY_WORLD_2       = 162,

    KB_KEY_ESCAPE        = 256,
    KB_KEY_ENTER         = 257,
    KB_KEY_TAB           = 258,
    KB_KEY_BACKSPACE     = 259,
    KB_KEY_INSERT        = 260,
    KB_KEY_DELETE        = 261,
    KB_KEY_RIGHT         = 262,
    KB_KEY_LEFT          = 263,
    KB_KEY_DOWN          = 264,
    KB_KEY_UP            = 265,
    KB_KEY_PAGE_UP       = 266,
    KB_KEY_PAGE_DOWN     = 267,
    KB_KEY_HOME          = 268,
    KB_KEY_END           = 269,
    KB_KEY_CAPS_LOCK     = 280,
    KB_KEY_SCROLL_LOCK   = 281,
    KB_KEY_NUM_LOCK      = 282,
    KB_KEY_PRINT_SCREEN  = 283,
    KB_KEY_PAUSE         = 284,
    KB_KEY_F1            = 290,
    KB_KEY_F2            = 291,
    KB_KEY_F3            = 292,
    KB_KEY_F4            = 293,
    KB_KEY_F5            = 294,
    KB_KEY_F6            = 295,
    KB_KEY_F7            = 296,
    KB_KEY_F8            = 297,
    KB_KEY_F9            = 298,
    KB_KEY_F10           = 299,
    KB_KEY_F11           = 300,
    KB_KEY_F12           = 301,
    KB_KEY_F13           = 302,
    KB_KEY_F14           = 303,
    KB_KEY_F15           = 304,
    KB_KEY_F16           = 305,
    KB_KEY_F17           = 306,
    KB_KEY_F18           = 307,
    KB_KEY_F19           = 308,
    KB_KEY_F20           = 309,
    KB_KEY_F21           = 310,
    KB_KEY_F22           = 311,
    KB_KEY_F23           = 312,
    KB_KEY_F24           = 313,
    KB_KEY_F25           = 314,
    KB_KEY_KP_0          = 320,
    KB_KEY_KP_1          = 321,
    KB_KEY_KP_2          = 322,
    KB_KEY_KP_3          = 323,
    KB_KEY_KP_4          = 324,
    KB_KEY_KP_5          = 325,
    KB_KEY_KP_6          = 326,
    KB_KEY_KP_7          = 327,
    KB_KEY_KP_8          = 328,
    KB_KEY_KP_9          = 329,
    KB_KEY_KP_DECIMAL    = 330,
    KB_KEY_KP_DIVIDE     = 331,
    KB_KEY_KP_MULTIPLY   = 332,
    KB_KEY_KP_SUBTRACT   = 333,
    KB_KEY_KP_ADD        = 334,
    KB_KEY_KP_ENTER      = 335,
    KB_KEY_KP_EQUAL      = 336,
    KB_KEY_LEFT_SHIFT    = 340,
    KB_KEY_LEFT_CONTROL  = 341,
    KB_KEY_LEFT_ALT      = 342,
    KB_KEY_LEFT_SUPER    = 343,
    KB_KEY_RIGHT_SHIFT   = 344,
    KB_KEY_RIGHT_CONTROL = 345,
    KB_KEY_RIGHT_ALT     = 346,
    KB_KEY_RIGHT_SUPER   = 347,
    KB_KEY_MENU          = 348
} mfb_key;
#define KB_KEY_LAST     KB_KEY_MENU

typedef enum {
    KB_MOD_SHIFT        = 0x0001,
    KB_MOD_CONTROL      = 0x0002,
    KB_MOD_ALT          = 0x0004,
    KB_MOD_SUPER        = 0x0008,
    KB_MOD_CAPS_LOCK    = 0x0010,
    KB_MOD_NUM_LOCK     = 0x0020
} mfb_key_mod;

typedef enum {
    WF_RESIZABLE          = 0x01,
    WF_FULLSCREEN         = 0x02,
    WF_FULLSCREEN_DESKTOP = 0x04,
    WF_BORDERLESS         = 0x08,
    WF_ALWAYS_ON_TOP      = 0x10,
} mfb_window_flags;

// Opaque pointer
struct mfb_window;
struct mfb_timer;

// Event callbacks
typedef void(*mfb_active_func)(struct mfb_window *window, bool isActive);
typedef void(*mfb_resize_func)(struct mfb_window *window, int width, int height);
typedef bool(*mfb_close_func)(struct mfb_window* window);
typedef void(*mfb_keyboard_func)(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed);
typedef void(*mfb_char_input_func)(struct mfb_window *window, unsigned int code);
typedef void(*mfb_mouse_button_func)(struct mfb_window *window, mfb_mouse_button button, mfb_key_mod mod, bool isPressed);
typedef void(*mfb_mouse_move_func)(struct mfb_window *window, int x, int y);
typedef void(*mfb_mouse_scroll_func)(struct mfb_window *window, mfb_key_mod mod, float deltaX, float deltaY);


#define MFB_RGB(r, g, b)    (((uint32_t) r) << 16) | (((uint32_t) g) << 8) | ((uint32_t) b)

// Create a window that is used to display the buffer sent into the mfb_update function, returns 0 if fails
MFB_API struct mfb_window * mfb_open(const char *title, unsigned width, unsigned height);
MFB_API struct mfb_window * mfb_open_ex(const char *title, unsigned width, unsigned height, unsigned flags);

// Update the display
// Input buffer is assumed to be a 32-bit buffer of the size given in the open call
// Will return a negative status if something went wrong or the user want to exit
// Also updates the window events
MFB_API mfb_update_state    mfb_update(struct mfb_window *window, void *buffer);

MFB_API mfb_update_state    mfb_update_ex(struct mfb_window *window, void *buffer, unsigned width, unsigned height);

// Only updates the window events
MFB_API mfb_update_state    mfb_update_events(struct mfb_window *window);

// Close the window
MFB_API void                mfb_close(struct mfb_window *window);

// Set user data
MFB_API void                mfb_set_user_data(struct mfb_window *window, void *user_data);
MFB_API void *              mfb_get_user_data(struct mfb_window *window);

// Set viewport (useful when resize)
MFB_API bool                mfb_set_viewport(struct mfb_window *window, unsigned offset_x, unsigned offset_y, unsigned width, unsigned height);
// Let mfb to calculate the best fit from your framebuffer original size
MFB_API bool                mfb_set_viewport_best_fit(struct mfb_window *window, unsigned old_width, unsigned old_height);

// DPI
// [Deprecated]: Probably a better name will be mfb_get_monitor_scale
MFB_API void                mfb_get_monitor_dpi(struct mfb_window *window, float *dpi_x, float *dpi_y);
// Use this instead
MFB_API void                mfb_get_monitor_scale(struct mfb_window *window, float *scale_x, float *scale_y);

// Callbacks
MFB_API void                mfb_set_active_callback(struct mfb_window *window, mfb_active_func callback);
MFB_API void                mfb_set_resize_callback(struct mfb_window *window, mfb_resize_func callback);
MFB_API void                mfb_set_close_callback(struct mfb_window* window, mfb_close_func callback);
MFB_API void                mfb_set_keyboard_callback(struct mfb_window *window, mfb_keyboard_func callback);
MFB_API void                mfb_set_char_input_callback(struct mfb_window *window, mfb_char_input_func callback);
MFB_API void                mfb_set_mouse_button_callback(struct mfb_window *window, mfb_mouse_button_func callback);
MFB_API void                mfb_set_mouse_move_callback(struct mfb_window *window, mfb_mouse_move_func callback);
MFB_API void                mfb_set_mouse_scroll_callback(struct mfb_window *window, mfb_mouse_scroll_func callback);

// Getters
MFB_API const char *        mfb_get_key_name(mfb_key key);

MFB_API bool                mfb_is_window_active(struct mfb_window *window);
MFB_API unsigned            mfb_get_window_width(struct mfb_window *window);
MFB_API unsigned            mfb_get_window_height(struct mfb_window *window);
MFB_API int                 mfb_get_mouse_x(struct mfb_window *window);             // Last mouse pos X
MFB_API int                 mfb_get_mouse_y(struct mfb_window *window);             // Last mouse pos Y
MFB_API float               mfb_get_mouse_scroll_x(struct mfb_window *window);      // Mouse wheel X as a sum. When you call this function it resets.
MFB_API float               mfb_get_mouse_scroll_y(struct mfb_window *window);      // Mouse wheel Y as a sum. When you call this function it resets.
MFB_API const uint8_t *     mfb_get_mouse_button_buffer(struct mfb_window *window); // One byte for every button. Press (1), Release 0. (up to 8 buttons)
MFB_API const uint8_t *     mfb_get_key_buffer(struct mfb_window *window);          // One byte for every key. Press (1), Release 0.

// FPS
MFB_API void                mfb_set_target_fps(uint32_t fps);
MFB_API unsigned            mfb_get_target_fps(void);
MFB_API bool                mfb_wait_sync(struct mfb_window *window);

// Timer
MFB_API struct mfb_timer *  mfb_timer_create(void);
MFB_API void                mfb_timer_destroy(struct mfb_timer *tmr);
MFB_API void                mfb_timer_reset(struct mfb_timer *tmr);
MFB_API double              mfb_timer_now(struct mfb_timer *tmr);
MFB_API double              mfb_timer_delta(struct mfb_timer *tmr);
MFB_API double              mfb_timer_get_frequency(void);
MFB_API double              mfb_timer_get_resolution(void);

#endif
