# MiniFB [LIGHTWEIGHT FORK]

MiniFB (Mini FrameBuffer) is a small cross platform library that makes it easy to render (32-bit) pixels in a window.

An example is the best way to show how it works:

```c
struct mfb_window *window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
if (!window)
    return 0;

buffer = (uint32_t *) malloc(800 * 600 * 4);

do {
    int state;

    // TODO: add some fancy rendering to the buffer of size 800 * 600

    state = mfb_update_ex(window, buffer, 800, 600);

    if (state < 0) {
        window = NULL;
        break;
    }
} while(mfb_wait_sync(window));
```

1. First the application creates a **window** calling **mfb_open** or **mfb_open_ex**.
2. Next it's the application responsibility to allocate a buffer to work with.
3. Next calling **mfb_update** or **mfb_update_ex** the buffer will be copied over to the window and displayed. If this function return a value lower than 0 the window will have been destroyed internally and cannot be used anymore.
4. Last the code waits to synchronize with the monitor calling **mfb_wait_sync**.

Note that, by default, if ESC key is pressed **mfb_update** / **mfb_update_ex** will return -1 (and the window will have been destroyed internally).

# Supported Platforms:

 - Windows
 - X11 (FreeBSD, Linux, \*nix)
 - Wayland (Linux) [there are some issues]

MiniFB has been tested on Windows and Linux but may of course have trouble depending on your setup. Currently the code will not do any converting of data if not a proper 32-bit display can be created.

# Features:

 - Window creation
 - Callbacks to window events
 - Get information from windows
 - Add per window data
 - Timers and target FPS
 - C interface

## Callbacks to window events:

You can _add callbacks to the windows_:

```c
void active(struct mfb_window *window, bool isActive) {
    ...
}

void resize(struct mfb_window *window, int width, int height) {
    ...
    // Optionally you can also change the viewport size
    mfb_set_viewport(window, x, y, width, height);
    // or let mfb caclculate the best fit from your original framebuffer size
    mfb_set_viewport_best_fit(window, old_width, old_height);

}

bool close(struct mfb_window *window) {
    ...
    return true;    // true => confirm close
                    // false => don't close
}

void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) {
    ...
    // Remember to close the window in some way
    if(key == KB_KEY_ESCAPE) {
        mfb_close(window);
    }
}

void char_input(struct mfb_window *window, unsigned int charCode) {
    ...
}

void mouse_btn(struct mfb_window *window, mfb_mouse_button button, mfb_key_mod mod, bool isPressed) {
    ...
}

// Use wisely this event. It can be sent too often
void mouse_move(struct mfb_window *window, int x, int y) {
    ...
}

// Mouse wheel
void mouse_scroll(struct mfb_window *window, mfb_key_mod mod, float deltaX, float deltaY) {
    ...
}


int main(int argc, char argv[]) {

    struct mfb_window *window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
    if (!window)
        return 0;

    mfb_set_active_callback(window, active);
    mfb_set_resize_callback(window, resize);
    mfb_set_close_callback(window, close);
    mfb_set_keyboard_callback(window, keyboard);
    mfb_set_char_input_callback(window, char_input);
    mfb_set_mouse_button_callback(window, mouse_btn);
    mfb_set_mouse_move_callback(window, mouse_move);
    mfb_set_mouse_scroll_callback(window, mouse_scroll);

    ...
}
```

## Get information from windows (direct interface)

If you don't want to use callbacks, you can _get information about the window events directly_:

```c
bool                mfb_is_window_active(struct mfb_window *window);

unsigned            mfb_get_window_width(struct mfb_window *window);
unsigned            mfb_get_window_height(struct mfb_window *window);

int                 mfb_get_mouse_x(struct mfb_window *window);             // Last mouse pos X
int                 mfb_get_mouse_y(struct mfb_window *window);             // Last mouse pos Y

float               mfb_get_mouse_scroll_x(struct mfb_window *window);      // Mouse wheel X as a sum. When you call this function it resets.
float               mfb_get_mouse_scroll_y(struct mfb_window *window);      // Mouse wheel Y as a sum. When you call this function it resets.

const uint8_t *     mfb_get_mouse_button_buffer(struct mfb_window *window); // One byte for every button. Press (1), Release 0. (up to 8 buttons)

const uint8_t *     mfb_get_key_buffer(struct mfb_window *window);          // One byte for every key. Press (1), Release 0.
```

## Add per window data

Additionally you can _set per window data and recover it_:

```c
mfb_set_user_data(window, (void *) myData);
...
myData = (someCast *) mfb_get_user_data(window);
```

## Timers and target FPS

You can create timers for your own purposes.

```c
struct mfb_timer *  mfb_timer_create();
void                mfb_timer_destroy(struct mfb_timer *tmr);

void                mfb_timer_reset(struct mfb_timer *tmr);
double              mfb_timer_now(struct mfb_timer *tmr);
double              mfb_timer_delta(struct mfb_timer *tmr);

double              mfb_timer_get_frequency();
double              mfb_timer_get_resolution();
```

Furthermore you can set (and get) a target fps for the application. The default is 60 frames per second.

```c
void                mfb_set_target_fps(uint32_t fps);
unsigned            mfb_get_target_fps();
```

This avoid the problem of update too fast the window collapsing the redrawing in fast processors.

Note: OpenGL and iOS have hardware support for syncing. Other systems will use software syncing. Including MacOS Metal.

In order to be able to use it you need to call the function:

```c
bool                mfb_wait_sync(struct mfb_window *window);
```

Note that if you have several windows running on the same thread it makes no sense to wait them all...

# Build instructions

No build system required, just compile the top-level source file for your target platform using your C toolchain. Adjust to taste.

## Dynamic library

Application build needs only the dynamic library and `MiniFB.h`.

### Windows (Mingw-w64):

    $ cc -shared -o mfb.dll windows.c -lwinmm -lgdi32 -lopengl32

### Windows (MSVC):

    $ cl /LD /Fe:mfb.dll windows.c

### Linux (X11):

    $ cc -shared -fPIC -o libmfb.so x11.c -lX11 -lGL

### Linux (Wayland):

    $ cc -shared -fPIC -o libmfb.so wayland.c -lwayland-client -lwayland-cursor

## Static library

Application build needs only the static library and `MiniFB.h`.

### Linux and Windows (Mingw-w64):

    $ cc -c -DMFB_API= PLATFORM.c
    $ ar r mfc.a PLATFORM.o

### Windows (MSVC):

    $ cl /c /DMFB_API= windows.c
    $ lib /out:mfb.lib windows.obj

## Embedded

Define `MFB_API` to `static` (optional), then include the platform-specific source from your own program (in place of `MiniFB.h`).

```c
#define MFB_API static
#include "PLATFORM.c"
```
