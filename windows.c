#ifndef MFB_API
#  define MFB_API __declspec(dllexport)
#endif
#if _MSC_VER
#  pragma comment(lib, "winmm.lib")
#  pragma comment(lib, "user32.lib")
#  pragma comment(lib, "gdi32.lib")
#endif
#if USE_OPENGL_API != 0
#  include "src/gl/MiniFB_GL.c"
#  if _MSC_VER
#    pragma comment(lib, "opengl32.lib")
#endif
#endif
#include "src/MiniFB_common.c"
#include "src/MiniFB_internal.c"
#include "src/MiniFB_timer.c"
#include "src/windows/WinMiniFB.c"
