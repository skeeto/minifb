#pragma once

#include "../MiniFB.h"
#include <windows.h>

typedef struct {
    HWND                window;
    WNDCLASS            wc;
    HDC                 hdc;
#if defined(USE_OPENGL_API)
    HGLRC               hGLRC;
    uint32_t            text_id;
#else
    BITMAPINFO          *bitmapInfo;
#endif
    struct mfb_timer    *timer;
    bool                mouse_inside;
} SWindowData_Win;
