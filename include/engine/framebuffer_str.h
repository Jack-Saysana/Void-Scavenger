#ifndef __FRAMEBUFFER_STR_H__
#define __FRAMEBUFFER_STR_H__

typedef struct framebuffer {
  unsigned int FBO;
  unsigned int color_texture;
  unsigned int depth_stencil_rbo;
} FRAMEBUFFER;

#endif
