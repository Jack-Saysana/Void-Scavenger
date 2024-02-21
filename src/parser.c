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
        } else if (strncmp(command[1].tok, GAMEMODE, sizeof(GAMEMODE)) == 0) {
          /* BEGIN: set gamemode */
          if (command[2].kind == IDENTIFIER) {
            if (strncmp(command[2].tok, STATION, sizeof(STATION)) == 0) {
              /* BEGIN: set gamemode station */
              set_gamemode_station();
              /* END: set gamemode station */
            } else if (strncmp(command[2].tok, SPACE, sizeof(SPACE)) == 0) {
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
        } else if (strncmp(command[1].tok, PLAYER, sizeof(PLAYER)) == 0) {
          /* BEGIN: set player */
          if (command[2].kind == IDENTIFIER) {
            if (strncmp(command[2].tok, STATION, sizeof(STATION)) == 0) {
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
                } else {
                  command_not_found();
                }
              } else {
                command_not_found();
              }
              /* END: set player station */
            } else {
              command_not_found();
            }
          } else {
            command_not_found();
          }
          /* END: set player */
        }  else {
          command_not_found();
        }
      } else {
        command_not_found();
      }
      /* END: set */
    } else if (strncmp(command[0].tok, GIVE, sizeof(GIVE)) == 0) {
      /* BEGIN: give */
      command_not_found();
      /* END: give */
    } else if (strncmp(command[0].tok, SPAWN, sizeof(SPAWN)) == 0) {
      /* BEGIN: spawn */
      command_not_found();
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
        if (strncmp(command[1].tok, STATION, sizeof(STATION)) == 0) {
          /* BEGIN: reset station */
          reset_station();
          /* END: reset station */
        } else if (strncmp(command[1].tok, SPACE, sizeof(SPACE)) == 0) {
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
