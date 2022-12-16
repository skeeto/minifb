#pragma once
#include "../WindowData.h"
bool create_GL_context(SWindowData *);
void destroy_GL_context(SWindowData *);
void init_GL(SWindowData *);
void redraw_GL(SWindowData *, const void *pixels);
void resize_GL(SWindowData *);
