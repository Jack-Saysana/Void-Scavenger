#include <camera.h>

/*                                  CAMERA.C

  Responsible for creating an easy interface for manipulating a camera model
  and returning the proper view matrix.

*/

void get_cam_matrix(CAM *cam, mat4 dest) {
  vec3 negcam = GLM_VEC3_ZERO_INIT;
  glm_vec3_negate_to(cam->pos, negcam);
  mat4 view;
  glm_mat4_identity(view);
  glm_rotate_x(view, glm_rad(cam->pitch), view);
  glm_rotate_y(view, glm_rad(cam->yaw), view);
  glm_translate(view, negcam);
  glm_mat4_copy(view, dest);

}
