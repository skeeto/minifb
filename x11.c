#ifndef MFB_API
#  define MFB_API __attribute__((visibility("default")))
#endif
#if USE_OPENGL_API != 0
#  include "src/gl/MiniFB_GL.c"
#endif
#include "src/MiniFB_common.c"
#include "src/MiniFB_internal.c"
#include "src/MiniFB_timer.c"
#include "src/MiniFB_linux.c"
#include "src/x11/X11MiniFB.c"
