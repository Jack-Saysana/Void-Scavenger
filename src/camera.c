#include <camera.h>

/*                                  CAMERA.C

  Responsible for creating an easy interface for manipulating a camera model
  and returning the proper view matrix.

*/

void get_cam_matrix(CAM *cam, mat4 dest) {
  vec3 negcam = GLM_VEC3_ZERO_INIT;
  glm_vec3_negate_to(cam->pos, negcam);
  glm_mat4_identity(cam->view);
  glm_rotate_x(cam->view, glm_rad(cam->pitch), cam->view);
  glm_rotate_y(cam->view, glm_rad(cam->yaw), cam->view);
  glm_translate(cam->view, negcam);
  glm_mat4_copy(cam->view, dest);
}

void move_camera(CAM *cam, char dir) {
  vec3 forward;
  forward[0] = cam->view[2][0];
  forward[1] = 0.0;
  forward[2] = -cam->view[2][2];
  glm_vec3_normalize(forward);
  vec3 up = {0.0, 1.0, 0.0};
  vec3 left;
  glm_vec3_cross(forward, up, left);
  glm_vec3_negate(left);
  glm_vec3_normalize(left);
  glm_vec3_scale(forward, (DELTA_TIME * st_player.speed), forward);
  glm_vec3_scale(left, (DELTA_TIME * st_player.speed), left);
  if (dir == 'w') {
    cam->pos[0] += forward[0];
    cam->pos[2] += forward[2];
  } else if (dir == 's') {
    cam->pos[0] -= forward[0];
    cam->pos[2] -= forward[2];
  } else if (dir == 'a') {
    cam->pos[0] += left[0];
    cam->pos[2] += left[2];
  } else if (dir == 'd') {
    cam->pos[0] -= left[0];
    cam->pos[2] -= left[2];
  }
}
