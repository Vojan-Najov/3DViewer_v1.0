#ifndef __VIEWER_PARSER_H__
#define __VIEWER_PARSER_H__

#include "vw_model.h"
#include "vw_scene.h"
#include "vw_errors.h"

int vw_parse_config(const char *pathname, vw_scene_t *scene);

int vw_parse_vertex(char *str, vw_model_t *model);

int vw_reduce_vertex_array(vw_model_t *model);

int vw_parse_face(char *str, vw_model_t *model);

int vw_reduce_face_array(vw_model_t *model);

#endif

