#include <main.h>

/*                                   MAIN.C

  Entrypoint of the application. Triggers window and game initialization and
  organizes the central components of the game into a single game loop. Also
  invokes cleanup code on game exit.

*/

int main() {
  window = init_gl("Void Scavenger");
  if (!window) {
    return -1;
  }

  //read_settings();
  //update_resolution();

  int status = barebones_init();
  if (status) {
    return -1;
  }

  loading_init();

  // Starting Tick
  add_timer(TICK_RATE, tick, FUNCTION_PTR, NULL);

  while (!glfwWindowShouldClose(window)) {
    float CUR_TIME = glfwGetTime();
    DELTA_TIME = CUR_TIME - LAST_FRAME;
    LAST_FRAME = CUR_TIME;
    REAL_DELTA = DELTA_TIME;
    if (DELTA_TIME > 0.032) {
      DELTA_TIME = 0.032;
    }

    if (mode == LOADING) {
      status = query_loading_status();
      if (status) {
        return -1;
      }
    }

    // Insert all simulation logic here:
    // - collision detection/response
    // - pathfinding
    // - win-condition tracking
    // - etc...
    keyboard_input(window);
    handle_collisions();
    decrement_current_timer(DELTA_TIME);

    //enemy_behavior();
    //player_ship_thrust_move();
    //recharge_player_shield();
    refresh_objects();
    update_ui_components();
    render_scene(window);
    //delete_stale_objects();
  }

  cleanup_game();
  return 0;
}

GLFWwindow *get_game_window() {
  return window;
}
