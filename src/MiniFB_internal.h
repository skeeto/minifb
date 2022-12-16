#pragma once

#include "MiniFB.h"
#include "WindowData.h"

#define kCall(func, ...)    if(window_data && window_data->func) window_data->func((struct mfb_window *) window_data, __VA_ARGS__);
#define kUnused(var)        (void) var;

typedef struct mfb_timer {
    int64_t     start_time;
    int64_t     delta_counter;
    uint64_t    time;
} mfb_timer;

static void keyboard_default(struct mfb_window *, mfb_key, mfb_key_mod, bool isPressed);
static void calc_dst_factor(SWindowData *, uint32_t width, uint32_t height);
static void resize_dst(SWindowData *, uint32_t width, uint32_t height);
static void set_target_fps_aux(void);
