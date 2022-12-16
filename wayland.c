#ifndef MFB_API
#  define MFB_API __attribute__((visibility("default")))
#endif
#include "src/MiniFB_common.c"
#include "src/MiniFB_internal.c"
#include "src/MiniFB_timer.c"
#include "src/MiniFB_linux.c"
#include "src/wayland/WaylandMiniFB.c"
