#include "MiniFB.h"
#include "MiniFB_internal.h"
#include <stdlib.h>

//-------------------------------------
static double      g_timer_frequency;
static double      g_timer_resolution;
static double      g_time_for_frame = 1.0 / 60.0;
static bool        g_use_hardware_sync = false;

//-------------------------------------
MFB_API uint64_t mfb_timer_tick(void);
MFB_API void mfb_timer_init(void);

//-------------------------------------
MFB_API void
mfb_set_target_fps(uint32_t fps) {
    if(fps == 0) {
        g_time_for_frame = 0;
    }
    else {
        g_time_for_frame = 1.0 / fps;
    }
    set_target_fps_aux();
}

//-------------------------------------
MFB_API unsigned
mfb_get_target_fps() {
    if (g_time_for_frame == 0) {
        return 0;
    }
    else {
        return (unsigned) (1.0 / g_time_for_frame);
    }
}

//-------------------------------------
MFB_API struct mfb_timer *
mfb_timer_create() {
    static int  once = 1;
    mfb_timer   *tmr;

    if(once) {
        once = 0;
        mfb_timer_init();
    }

    tmr = malloc(sizeof(mfb_timer));
    mfb_timer_reset(tmr);

    return tmr;
}

//-------------------------------------
MFB_API void
mfb_timer_destroy(struct mfb_timer *tmr) {
    if(tmr != 0x0) {
        free(tmr);
    }
}

//-------------------------------------
MFB_API void
mfb_timer_reset(struct mfb_timer *tmr) {
    if(tmr == 0x0)
        return;

    tmr->start_time    = mfb_timer_tick();
    tmr->delta_counter = tmr->start_time;
    tmr->time          = 0;
}

//-------------------------------------
MFB_API double
mfb_timer_now(struct mfb_timer *tmr) {
    uint64_t    counter;

    if(tmr == 0x0)
        return 0.0;

    counter         = mfb_timer_tick();
    tmr->time      += (counter - tmr->start_time);
    tmr->start_time = counter;

    return tmr->time * g_timer_resolution;
}

//-------------------------------------
MFB_API double
mfb_timer_delta(struct mfb_timer *tmr) {
    int64_t     counter;
    uint64_t    delta;

    if(tmr == 0x0)
        return 0.0;

    counter            = mfb_timer_tick();
    delta              = (counter - tmr->delta_counter);
    tmr->delta_counter = counter;

    return delta * g_timer_resolution;
}

//-------------------------------------
MFB_API double
mfb_timer_get_frequency() {
    return g_timer_frequency;
}

//-------------------------------------
MFB_API double
mfb_timer_get_resolution() {
    return g_timer_resolution;
}
