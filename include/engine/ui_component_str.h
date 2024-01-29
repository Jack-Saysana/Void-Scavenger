#ifndef __ENGINE_UI_COMPONENT_STR_H__
#define __ENGINE_UI_COMPONENT_STR_H__

#include <cglm/vec2.h>
#include <cglm/vec3.h>
#include "./font_str.h"

/*
                               UI_COMPONENT_STR.h
Describes the struct representing the building block of ui supported by the
engine.
*/

#define UI_ROOT_COMP (&ui_root)

#define RELATIVE_POS          (0x0)
#define ABSOLUTE_POS          (0x1)

#define POS_X_UNIT_RATIO_X    (0x2)
#define POS_X_UNIT_RATIO_Y    (0x4)
#define POS_X_UNIT_PIXEL      (0x6)

#define POS_Y_UNIT_RATIO_X    (0x8)
#define POS_Y_UNIT_RATIO_Y    (0x10)
#define POS_Y_UNIT_PIXEL      (0x18)

#define POS_UNIT_RATIO_X      (0xA)
#define POS_UNIT_RATIO_Y      (0x14)
#define POS_UNIT_PIXEL        (0x1E)
#define POS_UNIT_RATIO        (0x12)

#define WIDTH_UNIT_RATIO_X    (0x20)
#define WIDTH_UNIT_RATIO_Y    (0x40)
#define WIDTH_UNIT_PIXEL      (0x60)

#define HEIGHT_UNIT_RATIO_X   (0x80)
#define HEIGHT_UNIT_RATIO_Y   (0x100)
#define HEIGHT_UNIT_PIXEL     (0x180)

#define LINE_UNIT_RATIO_X     (0x200)
#define LINE_UNIT_RATIO_Y     (0x400)
#define LINE_UNIT_PIXEL       (0x600)

#define SIZE_UNIT_RATIO_X     (0x2A0)
#define SIZE_UNIT_RATIO_Y     (0x540)
#define SIZE_UNIT_PIXEL       (0x7E0)
#define SIZE_UNIT_RATIO       (0x520)

#define UI_TRUE  (1)
#define UI_FALSE (0)

#define INVALID_COMP_OPTIONS (0xFFFFFFFF)
#define CHILD_BUF_SIZE_INIT (5)

typedef enum pivot {
  PIVOT_CENTER = 0,
  PIVOT_TOP = 1,
  PIVOT_BOTTOM = 2,
  PIVOT_LEFT = 3,
  PIVOT_RIGHT = 4,
  PIVOT_TOP_LEFT = 5,
  PIVOT_TOP_RIGHT = 6,
  PIVOT_BOTTOM_LEFT = 7,
  PIVOT_BOTTOM_RIGHT = 8
} PIVOT;

extern vec2 UI_PIVOT_OFFSETS[9];

typedef enum text_anchor {
  T_CENTER,
  T_LEFT,
  T_RIGHT
} TEXT_ANCHOR;

typedef struct ui_component {
  void (*on_click)(struct ui_component *, void *);
  void (*on_release)(struct ui_component *, void *);
  void (*on_hover)(struct ui_component *, void *);
  void (*on_no_hover)(struct ui_component *, void *);
  void *click_args;
  void *release_args;
  void *hover_args;
  void *no_hover_args;

  // List of child components
  struct ui_component *children;
  size_t num_children;
  size_t child_buf_size;

  F_GLYPH *font;
  char *text;
  size_t text_len;

  // Specifies text color
  vec3 text_col;

  // Position
  vec3 pos;
  // Sizing (Unit determines on the options passed into "numerical_options")
  float width;
  float height;
  float line_height;
  int manual_layer;

  /*
    Position in pixels relative to center of root ui component

    Calculated on each render and is used in the actual positioning of the
    component on the screen by the renderer, since the actual position of the
    component can change based on the position of its parent, even if "pos"
    remains fixed.
  */
  vec3 pix_pos;
  /*
    Sizing in pixels (same as above if componment uses pixels as sizing units)

    Calculated on each render and is used in the actual sizing of the
    component on the screen by the renderer, since the actual size of the
    component can change based on the size of its parent, even if the relative
    size remains fixed.
  */
  float pix_width;
  float pix_height;
  float pix_line_height;

  /*
  Determines "pivot point" of component, i.e which point on the component will
  be located at the offset given by "pos".
  */
  PIVOT pivot;
  // Specifies text alignment inside component
  TEXT_ANCHOR txt_anc;
  /*
  Bitstring determining the options regarding positioning and unit type.
  See add_ui_comp() for details
  */
  int numerical_options;

  /*
  Whether or not the component will be rendered. Children will still be
  rendered and callbacks will still fire.
  */
  int display;

  /*
  Whether or not the component and it's children will be rendered and its
  event callbacks will fire.
  */
  int enabled;

  // Whether or not the component is textured
  int textured;

  // Texture of component
  unsigned int texture;
} UI_COMP;

#define INVALID_COMP_INIT { NULL, NULL, NULL,     \
                            NULL, NULL, NULL,     \
                            NULL, NULL,           \
                            NULL,                 \
                            0, 0,                 \
                            NULL, 0,              \
                            { 0.0, 0.0, 0.0 },    \
                            { 0.0, 0.0, 0.0 },    \
                            0.0, 0.0, 0.0, 0,     \
                            { 0.0, 0.0 },         \
                            0.0, 0.0, 0.0,        \
                            PIVOT_CENTER,         \
                            T_CENTER,             \
                            INVALID_COMP_OPTIONS, \
                            0, 0, 0, 0}

extern UI_COMP ui_root;
#endif
