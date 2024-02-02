#ifndef __CAMERA_STR_H__
#define __CAMERA_STR_H__

typedef struct camera {
  mat4 view;
  vec3 pos;
  float pitch;
  float yaw;
} CAM;

typedef enum move_dir {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  MOVE_LEFT,
  MOVE_RIGHT
} MOVE_DIR;

#endif
