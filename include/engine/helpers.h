#ifndef __ENGINE_HELPERS_H__
#define __ENGINE_HELPERS_H__

int double_buffer(void **buffer, size_t *buff_size, size_t unit_size);

int max_dot(vec3 *, unsigned int, vec3);
void vec3_remove_noise(vec3, float);
float remove_noise(float, float);

void set_mat4(char *, mat4, unsigned int);
void set_mat3(char *, mat3, unsigned int);
void set_vec4(char *, vec4, unsigned int);
void set_vec3(char *, vec3, unsigned int);
void set_vec2(char *, vec2, unsigned int);
void set_float(char *, float, unsigned int);
void set_int(char *, int, unsigned int);
void set_uint(char *, unsigned int, unsigned int);
void set_iarr(char *, int *, size_t, unsigned int);

#endif
