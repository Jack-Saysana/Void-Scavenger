#include <camera.h>

/*                                  CAMERA.C

  Responsible for creating an easy interface for manipulating a camera model
  and returning the proper view matrix.

*/
void reset_camera(CAM *cam) {
  glm_mat4_identity(cam->view);
  glm_vec3_zero(cam->pos);
  cam->pitch = 0.0;
  cam->yaw = -90.0;
}

void get_cam_matrix(CAM *cam, mat4 dest) {
  if (mode == STATION) {
    vec3 negcam = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(st_player.ent->translation, cam->pos);
    cam->pos[1] += 0.65;
    vec3 player_forward;
    mat4 playerrot;
    glm_quat_mat4(st_player.ent->rotation, playerrot);
    glm_mat4_mulv3(playerrot, (vec3){-1.0, 0.0, 0.0}, 1.0, player_forward);
    glm_vec3_scale(player_forward, 0.15, player_forward);
    glm_vec3_add(cam->pos, player_forward, cam->pos);
    glm_vec3_negate_to(cam->pos, negcam);
    glm_mat4_identity(cam->view);
    glm_rotate_x(cam->view, glm_rad(cam->pitch), cam->view);
    glm_rotate_y(cam->view, glm_rad(cam->yaw), cam->view);
    glm_translate(cam->view, negcam);
    glm_mat4_copy(cam->view, dest);
  } else if (mode == SPACE) {
    glm_mat4_identity(cam->view);
    mat4 shiprot;
    glm_quat_mat4(player_ship.ent->rotation, shiprot);
    vec3 ship_forward;
    vec3 ship_up;
    vec3 ship_side;
    if (holding_alpha_key('R')) {
      glm_mat4_mulv3(shiprot, (vec3){1.0, 0.0, 0.0}, 1.0, ship_forward);
      glm_mat4_mulv3(shiprot, (vec3){0.0, 1.0, 0.0}, 1.0, ship_up);
      glm_mat4_mulv3(shiprot, (vec3){0.0, 0.0, 1.0}, 1.0, ship_side);
    } else {
      glm_mat4_mulv3(shiprot, (vec3){-1.0, 0.0, 0.0}, 1.0, ship_forward);
      glm_mat4_mulv3(shiprot, (vec3){0.0, 1.0, 0.0}, 1.0, ship_up);
      glm_mat4_mulv3(shiprot, (vec3){0.0, 0.0, -1.0}, 1.0, ship_side);
    }
    mat4 ship_view = GLM_MAT4_IDENTITY_INIT;
    glm_vec3_copy(ship_side, ship_view[0]);
    glm_vec3_copy(ship_up, ship_view[1]);
    glm_vec3_negate_to(ship_forward, ship_view[2]);
    glm_mat4_inv(ship_view, ship_view);
    mat4 trans = GLM_MAT4_IDENTITY_INIT;

    float speed_offset = 0.0;
    if (player_ship.thruster.max_vel != 0.0) {
      speed_offset = (player_ship.cur_speed /
                      player_ship.thruster.max_vel) * 20.0;
    }

    glm_translate(trans, (vec3){0.0, -3.0, -20.0 - speed_offset});
    mat4 to_ship = GLM_MAT4_IDENTITY_INIT;
    vec3 negpos;
    glm_vec3_negate_to(player_ship.ent->translation, negpos);
    glm_translate(to_ship, negpos);
    glm_mat4_mul(trans, ship_view, ship_view);
    glm_mat4_mul(ship_view, to_ship, cam->view);
    glm_mat4_copy(cam->view, dest);
  }
}

void move_camera(CAM *cam, MOVE_DIR dir) {
  vec3 forward;
  forward[0] = cam->view[2][0];
  forward[1] = 0.0;
  forward[2] = -cam->view[2][2];
  glm_vec3_normalize(forward);
  vec3 up = {0.0, 1.0, 0.0};
  vec3 left;
  vec3 up_mov;
  glm_vec3_cross(forward, up, left);
  glm_vec3_negate(left);
  glm_vec3_normalize(left);
  glm_vec3_scale(forward, (DELTA_TIME * st_player.speed), forward);
  glm_vec3_scale(left, (DELTA_TIME * st_player.speed), left);
  glm_vec3_scale(up, (DELTA_TIME * st_player.speed), up_mov);
  if (dir == MOVE_FORWARD) {
    cam->pos[0] += forward[0];
    cam->pos[2] += forward[2];
  } else if (dir == MOVE_BACKWARD) {
    cam->pos[0] -= forward[0];
    cam->pos[2] -= forward[2];
  } else if (dir == MOVE_LEFT) {
    cam->pos[0] += left[0];
    cam->pos[2] += left[2];
  } else if (dir == MOVE_RIGHT) {
    cam->pos[0] -= left[0];
    cam->pos[2] -= left[2];
  } else if (dir == MOVE_UP) {
    cam->pos[1] += up_mov[1];
  } else if (dir == MOVE_DOWN) {
    cam->pos[1] -= up_mov[1];
  }
}
