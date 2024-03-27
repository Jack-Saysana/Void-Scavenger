#ifndef __ENGINE_ENTITY_H__
#define __ENGINE_ENTITY_H__

#include "./model_data_str.h"

unsigned int init_shader_prog(char *vs_path, char *gs_path, char *fs_path);
MODEL_DATA *load_model_data(char *path);
MODEL *gen_model(MODEL_DATA *md);
MODEL *load_model(char *path);
ENTITY *init_entity(MODEL *model);
int gen_cubemap(char **paths, unsigned int *dest);
void draw_entity(unsigned int shader, ENTITY *entity);
void draw_skeleton(unsigned int shader, ENTITY *entity);
void draw_colliders(unsigned int shader, ENTITY *entity, MODEL *sphere);
void draw_model(unsigned int shader, MODEL *model);
void free_model(MODEL *model);
void free_entity(ENTITY *entity);
void free_textures();

#endif
