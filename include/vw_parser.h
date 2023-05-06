#ifndef __VIEWER_PARSER_H__
#define __VIEWER_PARSER_H__

#include "vw_model.h"

int vw_parse_vertex(char *str, vw_model_t *model);

int vw_reduce_vertex_array(float **vertex_array, size_t n);

int vw_parse_face(char *str, vw_model_t *model);

int vw_reduce_face_array(float **face_array, size_t n);

#endif

