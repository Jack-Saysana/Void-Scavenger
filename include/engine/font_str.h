#ifndef __ENGINE_FONT_STR_H__
#define __ENGINE_FONT_STR_H__

typedef struct font_glyph {
  // Vertex info for rendering
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
  unsigned int texture;

  // Height of character as a ratio of some line height
  float height;
  // Width of character as a ratio of some line height
  float width;
  /*
  Distance form origin of character to left of next character as a ratio of
  some line height
  */
  float advance;
  // Offset from origin to left side of the glyph as a ratio of line height
  float x_offset;
  // Offset from top of line to top of glyph as a ratio of line height
  float y_offset;
  float base; // Offset from origin to top of line as a ratio of line height
  // ASCII id of glyph
  int id;
} F_GLYPH;

#endif
