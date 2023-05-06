#ifndef __VIEWER_MODEL_H__
#define __VIEWER_MODEL_H__

#include <stddef.h>

#define VW_POINT_NUMBER_OF_COORDINATES 4

#define VW_OPEN_FILE_ERROR 1
#define VW_READ_FILE_ERROR 2
#define VW_WRITE_FILE_ERROR 2
#define VW_CLOSE_FILE_ERROR 4
#define VW_ALLOC_ERROR 5
#define VW_INCORRECT_LINE 6

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
	float v_color[3];
	float f_color[3];
	unsigned int v_size;
	unsigned int f_size;
} vw_model_t;

typedef struct vw_scene {
	vw_model_t model;
	float bg_color[4];
} vw_scene_t;

int vw_parse_objfile_to_model(const char *pathname, vw_model_t *model);

int vw_save_model_to_objfile(const char *pathname, vw_model_t *model);

void vw_clear_model(vw_model_t *model);

#endif
