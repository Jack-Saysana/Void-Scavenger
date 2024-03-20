#ifndef __ENGINE_FRAMEBUFFER_H__
#define __ENGINE_FRAMEBUFFER_H__

#include "./framebuffer_str.h"

FRAMEBUFFER framebuffer_init(float res_x, float res_y);
void framebuffer_delete(FRAMEBUFFER fb);

#endif
