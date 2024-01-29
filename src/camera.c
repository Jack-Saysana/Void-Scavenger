#include <camera.h>

/*                                  CAMERA.C

  Responsible for creating an easy interface for manipulating a camera model
  and returning the proper view matrix.

*/

void get_cam_matrix(CAM *cam, mat4 dest) {
  glm_mat4_identity(dest);
  vec3 cam_x = GLM_VEC3_ZERO_INIT;
  vec3 cam_y = GLM_VEC3_ZERO_INIT;
  vec3 cam_z = GLM_VEC3_ZERO_INIT;

  glm_vec3_copy(cam->up, cam_y);
  glm_vec3_negate_to(cam->forward, cam_z);
  glm_vec3_cross(cam_y, cam_z, cam_x);
  glm_vec3_normalize(cam_x);
  glm_vec3_normalize(cam_y);
  glm_vec3_normalize(cam_z);

  glm_vec3_copy(cam_x, dest[X]);
  glm_vec3_copy(cam_y, dest[Y]);
  glm_vec3_copy(cam_z, dest[Z]);
  glm_vec3_negate_to(cam->pos, dest[W]);
}
