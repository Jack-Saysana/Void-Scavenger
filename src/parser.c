#include <parser.h>

/*
GRAMMAR:
command := simple_command end | end
simple_command := identifier | identifier argument
argument := (identifier)* | (number)*
*/
void parse() {
  init_parse_table();
  current.line = 0;
  current.token = 0;
  int cur_tok = 0;
  /* BEGIN: command  */
  /* Empty case should be handled by lexer */
  if (peek_token() == END) {
     return;
  }
  /* BEGIN: simple_command */
  if (peek_token() != IDENTIFIER) {
    command_not_found();
    return;
  }
  command[cur_tok++] = get_token();
  /* BEGIN: argument */
  while (lexer.lines[lexer.num_lines].num_tokens != current.token &&
        (peek_token() == NUMBER || peek_token() == IDENTIFIER ||
         peek_token() == DOT)) {
    command[cur_tok++] = get_token();
  }
  if (peek_token() != END) {
    command_not_found();
    return;
  } else if (lexer.lines[lexer.num_lines].num_tokens == 0 && peek_token() == END) {
    command[cur_tok++] = get_token();
  }
  /* END: argument */
  /* END: simple_command */
  /* END: command */
  console_dispatcher();
}

/* Responsible for calling appropriate console command with arguments */
/* passed through to the respective function  */
void console_dispatcher() {
  if (command[0].kind == IDENTIFIER) {
    if (strncmp(command[0].tok, SET, sizeof(SET)) == 0) {
      /* BEGIN: set */
      if (command[1].kind == IDENTIFIER) {
        if (strncmp(command[1].tok, CURSOR, sizeof(CURSOR)) == 0) {
          /* BEGIN: set cursor */
            if (command[2].kind == IDENTIFIER &&
                strncmp(command[2].tok, ON, sizeof(ON)) == 0) {
              /* BEGIN: set cursor on */
              cursor_on(1);
              /* END: set cursor on */
            } else if (command[2].kind == IDENTIFIER &&
                       strncmp(command[2].tok, OFF, sizeof(OFF)) == 0) {
              /* BEGIN: set cursor off */
              cursor_on(0);
              /* END: set cursor off */
            } else {
              command_not_found();
            }
          /* END: set cursor */
        } else  if (strncmp(command[1].tok, ESHOOT, sizeof(ESHOOT)) == 0) {
          /* BEGIN: set eshoot */
            if (command[2].kind == IDENTIFIER &&
                strncmp(command[2].tok, ON, sizeof(ON)) == 0) {
              /* BEGIN: set eshoot on */
              eshoot_on(1);
              /* END: set eshoot on */
            } else if (command[2].kind == IDENTIFIER &&
                       strncmp(command[2].tok, OFF, sizeof(OFF)) == 0) {
              /* BEGIN: set eshoot off */
              eshoot_on(0);
              /* END: set eshoot off */
            } else {
              command_not_found();
            }
          /* END: set eshoot */
        } else  if (strncmp(command[1].tok, INVENTORY, sizeof(INVENTORY)) == 0) {
          /* BEGIN: set inventory */
            if (command[2].kind == IDENTIFIER &&
                strncmp(command[2].tok, ON, sizeof(ON)) == 0) {
              /* BEGIN: set inventory on */
              space_inv_on(1);
              /* END: set inventory on */
            } else if (command[2].kind == IDENTIFIER &&
                       strncmp(command[2].tok, OFF, sizeof(OFF)) == 0) {
              /* BEGIN: set inventory off */
              space_inv_on(0);
              /* END: set inventory off */
            } else {
              command_not_found();
            }
          /* END: set eshoot */
        } else if (strncmp(command[1].tok, GAMEMODE, sizeof(GAMEMODE)) == 0) {
          /* BEGIN: set gamemode */
          if (command[2].kind == IDENTIFIER) {
            if (strncmp(command[2].tok, STATION_CMD, sizeof(STATION_CMD)) == 0) {
              /* BEGIN: set gamemode station */
              set_gamemode_station();
              /* END: set gamemode station */

            } else if (strncmp(command[2].tok, SPACE_CMD, sizeof(SPACE_CMD)) == 0) {
              /* BEGIN: set gamemode space */
              set_gamemode_space();
              /* END: set gamemode space */
            } else {
              command_not_found();
            }
          } else {
            command_not_found();
          }
          /* END: set gamemode */
        } else if (strncmp(command[1].tok, ARENA, sizeof(ARENA)) == 0) {
          /* BEGIN: set arena */
          if (command[2].kind == NUMBER &&
            (command[3].kind == DOT || command[3].kind == END)) {
            /* BEGIN: set arena [float] */
            float size = create_float(2);
            if (size != FLT_MAX) {
              set_arena(size);
            } else {
              command_not_found();
            }
            return;
            /* END: set arena [float] */
          } else {
            command_not_found();
          }
          /* END: set arena */
        } else  if (strncmp(command[1].tok, GUN, sizeof(GUN)) == 0) {
          /* BEGIN: set gun */
            if (command[2].kind == IDENTIFIER &&
                strncmp(command[2].tok, BALLISTIC_CMD, sizeof(BALLISTIC_CMD)) == 0) {
              /* BEGIN: set gun ballistic */
              set_gun(BALLISTIC);
              /* END: set gun ballistic */
            } else if (command[2].kind == IDENTIFIER &&
                       strncmp(command[2].tok, LASER_CMD, sizeof(LASER_CMD)) == 0) {
              /* BEGIN: set gun laser */
              set_gun(LASER);
              /* END: set gun laser */
            } else if (command[2].kind == IDENTIFIER &&
                       strncmp(command[2].tok, PLASMA_CMD, sizeof(PLASMA_CMD)) == 0) {
              /* BEGIN: set gun plasma */
              set_gun(PLASMA);
              /* END: set gun plasma */
            } else {
              command_not_found();
            }
          /* END: set gun */
        } else if (strncmp(command[1].tok, PLAYER, sizeof(PLAYER)) == 0) {
          /* BEGIN: set player */
          if (command[2].kind == IDENTIFIER) {
            if (strncmp(command[2].tok, STATION_CMD, sizeof(STATION_CMD)) == 0) {
              /* BEGIN: set player station */
              if (command[3].kind == IDENTIFIER) {
                if (strncmp(command[3].tok, SPEED, sizeof(SPEED)) == 0) {
                  /* BEGIN: set player station speed */
                  if (command[4].kind == NUMBER && command[5].kind == DOT &&
                      command[6].kind == NUMBER) {
                    /* BEGIN: set player station speed [float] */
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                      return;
                    }
                    set_player_station_speed(input);
                    /* END: set player station speed [float] */
                  }
                  /* END: set player station speed */
                } else if (strncmp(command[3].tok, HEALTH, sizeof(HEALTH)) == 0) {
                  /* BEGIN: set player station health */
                  if (command[4].kind == NUMBER) {
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                    }
                    set_player_health(input, STATION);
                    return;
                  }
                  /* END: set player station health */
                } else if (strncmp(command[3].tok, SHIELD, sizeof(SHIELD)) == 0) {
                  /* BEGIN: set player station shield */
                  if (command[4].kind == NUMBER) {
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                    }
                    set_player_shield(input, STATION);
                    return;
                  }
                  /* END: set player station shield */
                } else if (strncmp(command[3].tok, XP, sizeof(XP)) == 0) {
                  /* BEGIN: set player station xp */
                  if (command[4].kind == NUMBER) {
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                    }
                    set_player_xp(input);
                    return;
                  }
                  /*END: set player station xp*/
                } else {
                  command_not_found();
                }
              } else {
                command_not_found();
              }
              /* END: set player station */
            } else if (strncmp(command[2].tok, SPACE_CMD, sizeof(SPACE_CMD)) == 0 ) {
              /* START: set player space */
              if (command[3].kind == IDENTIFIER) {
                if (strncmp(command[3].tok, HEALTH, sizeof(HEALTH)) == 0) {
                  /* START: set player space health */
                  if (command[4].kind == NUMBER) {
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                    }
                    set_player_health(input, SPACE);
                    return;
                  }
                  /* END: set player space health */
                } else if (strncmp(command[3].tok, SHIELD, sizeof(SHIELD)) == 0 ){
                  /* START: set player space shield */
                  if (command[4].kind == NUMBER) {
                    float input = create_float(4);
                    if (input == FLT_MAX) {
                      command_not_found();
                    }
                    set_player_shield(input, SPACE);
                    return;
                  }
                  /* END: set player space shield */
                } else {
                  command_not_found();
                }
              } else {
                command_not_found();
              }
              /* END: set player space */
            } else {
              command_not_found();
            }
          } else {
            command_not_found();
          }
          /* END: set player */
        } else if (strncmp(command[1].tok, GAMELEVEL, sizeof(GAMELEVEL)) == 0) {
          /* BEGIN: set gamelevel */
          if (command[2].kind == NUMBER) {
            set_gamelevel(atoi(command[2].tok));
            return;
          }
          /*END: set gamelevel*/
        } else if (strncmp(command[1].tok, SKILL, sizeof(SKILL)) == 0) {
          /* BEGIN: set skill */
          if (strncmp(command[2].tok, POINTS, sizeof(POINTS)) == 0) {
            /* BEGIN: set skill points */
            if (command[3].kind == NUMBER) {
              /* BEGIN: set skill points # */
              st_player.skill_points = atoi(command[3].tok);
              /* END: set skill points # */
            } else {
              command_not_found();
            }
            /* END: set skill points */
          } else {
            command_not_found();
          }
          /* END: set skill */
        } else if (strncmp(command[1].tok, RESOLUTION,
                           sizeof(RESOLUTION)) == 0) {
          /* BEGIN: set resolution */
          if (command[2].kind == NUMBER && command[3].kind == NUMBER) {
            set_resolution(atoi(command[2].tok), atoi(command[3].tok), 1);
          } else {
            command_not_found();
          }
          /* END: set resolution */
        } else {
          command_not_found();
        }
      } else {
        command_not_found();
      }
      /* END: set */
    } else if (strncmp(command[0].tok, SPAWN, sizeof(SPAWN)) == 0) {
      /* BEGIN: spawn */
      int type = -1;
      int rarity = -1;
      if (strncmp(command[1].tok, BALLISTIC_CMD, sizeof(BALLISTIC_CMD)) == 0) {
        type = TYPE_WEAPON_BALLISTIC;
      } else if (strncmp(command[1].tok, LASER_CMD, sizeof(LASER_CMD)) == 0) {
        type = TYPE_WEAPON_LASER;
      } else if (strncmp(command[1].tok, PLASMA_CMD, sizeof(PLASMA_CMD)) == 0) {
        type = TYPE_WEAPON_PLASMA;
      } else if (strncmp(command[1].tok, HULL_CMD, sizeof(HULL_CMD)) == 0) {
        type = TYPE_HULL;
      } else if (strncmp(command[1].tok, SHIELD_CMD, sizeof(SHIELD_CMD)) == 0) {
        type = TYPE_SHIELD;
      } else if (strncmp(command[1].tok, REACTOR_CMD, sizeof(REACTOR_CMD)) == 0) {
        type = TYPE_REACTOR;
      } else if (strncmp(command[1].tok, WING_CMD, sizeof(WING_CMD)) == 0) {
        type = TYPE_WING;
      } else if (strncmp(command[1].tok, THRUSTER_CMD, sizeof(THRUSTER_CMD)) == 0) {
        type = TYPE_THRUSTER;
      } else {
        command_not_found();
      }
      if (strncmp(command[2].tok, WHITE_CMD, sizeof(WHITE_CMD)) == 0) {
        rarity = WHITE_RARITY;
      } else if (strncmp(command[2].tok, BLUE_CMD, sizeof(BLUE_CMD)) == 0) {
        rarity = BLUE_RARITY;
      } else if (strncmp(command[2].tok, GREEN_CMD, sizeof(GREEN_CMD)) == 0) {
        rarity = GREEN_RARITY;
      } else if (strncmp(command[2].tok, PURPLE_CMD, sizeof(PURPLE_CMD)) == 0) {
        rarity = PURPLE_RARITY;
      } else if (strncmp(command[2].tok, GOLD_CMD, sizeof(GOLD_CMD)) == 0) {
        rarity = GOLD_RARITY;
      } else {
        command_not_found();
      }
      if (type == -1 || rarity == -1) {
        command_not_found();
      } else {
        spawn_ship_part_cmd(st_player.ent->translation, type, rarity);
      }
      /* END: spawn  */
    } else if (strncmp(command[0].tok, COORDS, sizeof(COORDS)) == 0) {
      /* BEGIN: coords */
      if (command[1].kind == IDENTIFIER) {
        if (strncmp(command[1].tok, ON, sizeof(ON)) == 0) {
          /* BEGIN: coords on */
          enable_coordinates();
          /* END: coords on */
        } else if (strncmp(command[1].tok, OFF, sizeof(OFF)) == 0) {
          /* BEGIN: coords off */
          disable_coordinates();
          /* END: coords off */
        } else {
          command_not_found();
        }
      } else {
        command_not_found();
      }
      /* END: coords*/
    } else if (strncmp(command[0].tok, RESPAWN, sizeof(RESPAWN)) == 0) {
      /* BEGIN: respawn */
      command_not_found();
      /* END: respawn*/
    } else if (strncmp(command[0].tok, WIRE, sizeof(WIRE)) == 0) {
      /* BEGIN: wire */
      toggle_wire_frame();
      /* END: wire */
    } else if (strncmp(command[0].tok, HIT_BOXES, sizeof(HIT_BOXES)) == 0) {
      /* BEGIN: hb */
      toggle_hit_boxes();
      /* END: hb */
    } else if (strncmp(command[0].tok, RENDER_ARENA,
                       sizeof(RENDER_ARENA)) == 0) {
      /* BEGIN: ra */
      toggle_render_arena();
      /* END: ra */
    } else if (strncmp(command[0].tok, RENDER_BOUNDS,
                       sizeof(RENDER_BOUNDS)) == 0) {
      /* BEGIN: rb */
      toggle_render_bounds();
      /* END: rb */
    } else if (strncmp(command[0].tok, QUIT, sizeof(QUIT)) == 0) {
      /* BEGIN: quit */
      quit();
      /* END: quit */
    } else if (strncmp(command[0].tok, GAMEOVER, sizeof(GAMEOVER)) == 0) {
      /* BEGIN: gameover */
      game_over();
      /* END: gameover */
    } else if (strncmp(command[0].tok, SET_SIM_DIST,
                       sizeof(SET_SIM_DIST)) == 0) {
      /* BEGIN: ssd */
      float val = create_float(1);
      if (val != FLT_MAX) {
        set_sim_dist(val);
      } else {
        command_not_found();
      }
      /* END: ssd */
    } else if (strncmp(command[0].tok, SET_RENDER_DIST,
                       sizeof(SET_RENDER_DIST)) == 0) {
      /* BEGIN: srd */
      float val = create_float(1);
      if (val != FLT_MAX) {
        set_render_dist(val);
      } else {
        command_not_found();
      }
      /* END: srd */
    } else if (strncmp(command[0].tok, RESET, sizeof(RESET)) == 0) {
      /* BEGIN: reset */
      if (command[1].kind == IDENTIFIER) {
        if (strncmp(command[1].tok, STATION_CMD, sizeof(STATION_CMD)) == 0) {
          /* BEGIN: reset station */
          reset_station();
          /* END: reset station */
        } else if (strncmp(command[1].tok, SPACE_CMD, sizeof(SPACE_CMD)) == 0) {
          /* BEGIN: reset space */
          reset_space();
          /* END: reset space */
        } else {
          command_not_found();
        }
      } else {
        command_not_found();
      }
      /* END: reset */
    } else if (strncmp(command[0].tok, FPS, sizeof(FPS)) == 0) {
      /* BEGIN: fps */
      fps_toggle();
      /* END: fps */
    } else if (strncmp(command[0].tok, ITEM, sizeof(ITEM)) == 0) {
      /* BEGIN: item */
      if (strncmp(command[1].tok, GLOW, sizeof(GLOW)) == 0) {
        /* BEGIN: item glow */
        toggle_item_glow();
        /* END: item glow */
      } else {
        command_not_found();
      }
      /* END: item */

    } else if (strncmp(command[0].tok, GIVE, sizeof(GIVE)) == 0) {
      /* BEGIN: give */
      int type = -1;
      int rarity = -1;
      if (strncmp(command[1].tok, BALLISTIC_CMD, sizeof(BALLISTIC_CMD)) == 0) {
        type = TYPE_WEAPON_BALLISTIC;
      } else if (strncmp(command[1].tok, LASER_CMD, sizeof(LASER_CMD)) == 0) {
        type = TYPE_WEAPON_LASER;
      } else if (strncmp(command[1].tok, PLASMA_CMD, sizeof(PLASMA_CMD)) == 0) {
        type = TYPE_WEAPON_PLASMA;
      } else if (strncmp(command[1].tok, HULL_CMD, sizeof(HULL_CMD)) == 0) {
        type = TYPE_HULL;
      } else if (strncmp(command[1].tok, SHIELD_CMD, sizeof(SHIELD_CMD)) == 0) {
        type = TYPE_SHIELD;
      } else if (strncmp(command[1].tok, REACTOR_CMD, sizeof(REACTOR_CMD)) == 0) {
        type = TYPE_REACTOR;
      } else if (strncmp(command[1].tok, WING_CMD, sizeof(WING_CMD)) == 0) {
        type = TYPE_WING;
      } else if (strncmp(command[1].tok, THRUSTER_CMD, sizeof(THRUSTER_CMD)) == 0) {
        type = TYPE_THRUSTER;
      } else {
        command_not_found();
      }
      if (strncmp(command[2].tok, WHITE_CMD, sizeof(WHITE_CMD)) == 0) {
        rarity = WHITE_RARITY;
      } else if (strncmp(command[2].tok, BLUE_CMD, sizeof(BLUE_CMD)) == 0) {
        rarity = BLUE_RARITY;
      } else if (strncmp(command[2].tok, GREEN_CMD, sizeof(GREEN_CMD)) == 0) {
        rarity = GREEN_RARITY;
      } else if (strncmp(command[2].tok, PURPLE_CMD, sizeof(PURPLE_CMD)) == 0) {
        rarity = PURPLE_RARITY;
      } else if (strncmp(command[2].tok, GOLD_CMD, sizeof(GOLD_CMD)) == 0) {
        rarity = GOLD_RARITY;
      } else {
        command_not_found();
      }
      if (type == -1 || rarity == -1) {
        command_not_found();
      } else {
        give_item(type, rarity);
      }

      /* END: give */
    } else {
      /* NON-RECOGNIZED IDENTIFIER */
      command_not_found();
    }
  } else {
    /* BOGUS COMMAND */
    command_not_found();
  }
}

/* ============== HELPERS =============== */

/* Gets the next token off the stack */
TOKEN get_token() {
  if (current.line == lexer.num_lines) {
    fprintf(stderr, "NO MORE TOKENS TO GET FROM LEXER\n");
    exit(1);
  }
  if (current.token + 1 == lexer.lines[current.line].num_tokens) {
    TOKEN ret = lexer.lines[current.line++].tokens[current.token];
    current.token = 0;
    return ret;
  }
  return lexer.lines[current.line].tokens[current.token++];
}

/* Peeks the kind of token off the stack */
enum KIND peek_token() {
  if (current.line == lexer.num_lines) {
    fprintf(stderr, "NO MORE TOKENS LEFT TO PEEK FROM LEXER\n");
    exit(1);
  }
  return lexer.lines[current.line].tokens[current.token].kind;
}

/* Creates and returns a float from three tokens on the stack */
/* Note: Pass in the index to the number before the decimal   */
/* in the float from the console                              */
float create_float(int start) {
  char fl[6];
  int index = command[start].num_chars;
  /* snprintf will fail if not accounting for null byte  */
  /* therefore need to add one to size to copy to work   */
  /* properly                                            */
  if (command[start].kind != NUMBER) {
    return FLT_MAX;
  }
  snprintf(fl, index + 1, "%s", command[start].tok);
  start++;
  fl[index++] = '.';
  start++;
  if (command[start].kind != NUMBER) {
    fl[index] = '0';
  } else {
    /* Only take the first and second decimal places and discard the rest */
    if (command[start].num_chars == 1) {
      fl[index++] = command[start].tok[0];
    } else {
      fl[index++] = command[start].tok[0];
      fl[index++] = command[start].tok[1];
    }
    while (index < 6) {
      fl[index++] = '0';
    }
  }
  return atof(fl);
}

void print_parse_table() {
  TOKEN cur;
  printf("\n");
  for (int i = 0; i < MAX_TOKS; i++) {
    cur = command[i];
    printf("TOKEN: %d\t(", i);
      switch (cur.kind) {
        case NUMBER:
          printf("NUMBER      |");
          break;
        case IDENTIFIER:
          printf("IDENTIFIER  |");
          break;
        case LEFTPAREN:
          printf("LEFTPAREN   |");
          break;
        case RIGHTPAREN:
          printf("RIGHTPAREN  |");
          break;
        case LEFTSQUARE:
          printf("LEFTSQUARE  |");
          break;
        case RIGHTSQUARE:
          printf("RIGHTSQUARE |");
          break;
        case LEFTCURLY:
          printf("LEFTCURLY   |");
          break;
        case RIGHTCURLY:
          printf("RIGHTCURLY  |");
          break;
        case LESSTHAN:
          printf("LESSTHAN    |");
          break;
        case GREATERTHAN:
          printf("GREATERTHAN |");
          break;
        case EQUAL:
          printf("EQUAL       |");
          break;
        case PLUS:
          printf("PLUS        |");
          break;
        case MINUS:
          printf("MINUS       |");
          break;
        case ASTERISK:
          printf("ASTERISK    |");
          break;
        case SLASH:
          printf("SLASH       |");
          break;
        case HASH:
          printf("HASH        |");
          break;
        case DOT:
          printf("DOT         |");
          break;
        case COMMA:
          printf("COMMA       |");
          break;
        case COLON:
          printf("COLON       |");
          break;
        case SEMICOLON:
          printf("SEMICOLON   |");
          break;
        case SINGLEQUOTE:
          printf("SINGLEQUOTE |");
          break;
        case DOUBLEQUOTE:
          printf("DOUBLEQUOTE |");
          break;
        case COMMENT:
          printf("COMMENT     |");
          break;
        case PIPE:
          printf("PIPE        |");
          break;
        case END:
          printf("END         |");
          break;
        case UNEXPECTED:
          printf("UNEXPECTED  |");
          break;
      }
    for (int j = 0; j < cur.num_chars; j++) {
      if (cur.tok[j] == '\0') {
        printf(" ");
        continue;
      }
      printf("%c", cur.tok[j]);
    }
    printf("|)\n");
  }
}

/* Sets the parse table with dummy inserts */
void init_parse_table() {
  TOKEN dummy = {
    UNEXPECTED,
    "",
    0,
  };
  for (int i = 0; i < MAX_TOKS; i++) {
    command[i] = dummy;
  }
}
