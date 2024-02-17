#include <main.h>

/*                                   MAIN.C

  Entrypoint of the application. Triggers window and game initialization and
  organizes the central components of the game into a single game loop. Also
  invokes cleanup code on game exit.

*/

int main() {
  GLFWwindow *window = init_gl("Void Scavenger");
  if (!window) {
    return -1;
  }

  int status = init_game();
  if (status) {
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    float CUR_TIME = glfwGetTime();
    DELTA_TIME = CUR_TIME - LAST_FRAME;
    LAST_FRAME = CUR_TIME;
    if (DELTA_TIME > 0.016) {
      DELTA_TIME = 0.016;
    }

    // Insert all simulation logic here:
    // - collision detection/response
    // - pathfinding
    // - win-condition tracking
    // - etc...
    keyboard_input(window);
    decrement_current_timer(DELTA_TIME);
    enemy_behavior();
    player_ship_thrust_move();
    handle_collisions();
    refresh_objects();
    update_ui_components();
    render_scene(window);
    delete_stale_objects();
  }

  cleanup_game();
  return 0;
}
