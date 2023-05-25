#ifndef __VIEWER_MODEL_H__
#define __VIEWER_MODEL_H__

#include <stddef.h>

#define VW_POINT_NUMBER_OF_COORDINATES 4

/*
  Viewer model's structure.
  field vertices:
    An array sequentially containing vertices.
    Each vertex is represented by four floating point numbers: x, y, z and w.
    To get a vertex with the idx index, need to shift from the beginning of
    the array by 4 * (idx - 1) elements.
  field number_of_vertices:
    Total number of vertices in the vertices array.
*/

typedef float vw_point_t[VW_POINT_NUMBER_OF_COORDINATES];

typedef struct vw_face {
    unsigned int *idx;
    size_t number_of_idx;
} vw_face_t;

typedef struct vw_model {
    vw_point_t *vertices;
    size_t number_of_vertices;
    vw_face_t *faces;
    size_t number_of_faces;
    vw_point_t centre;
    float dim;
} vw_model_t;

void vw_model_calculate_dimension(vw_model_t *model);

int vw_parse_objfile_to_model(const char *pathname, vw_model_t *model);

int vw_save_model_to_objfile(const char *pathname, vw_model_t *model);

void vw_model_clear(vw_model_t *model);

#endif
