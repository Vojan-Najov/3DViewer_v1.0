#ifndef __AFFINE_TRANSFORMATION_H__
#define __AFFINE_TRANSFORMATION_H__

#include <math.h>

#include "matrix.h"
#include "vw_model.h"
#include "vw_scene.h"

#define PI 3.1415926

typedef enum {
    SPIN_XY = 0,
    SPIN_YZ = 1,
    SPIN_XZ = 2,
    MOVE_XYZ = 3,
    SCALE_XYZ = 4
} MOVE;

// int vw_centering_vector(vw_point_t *centering_step);
int vw_move(MOVE move, float a, float b, float c);
int vw_spin_xy(float grad);
int vw_spin_xz(float grad);
int vw_spin_yz(float grad);
int vw_move_xyz(float x1, float y1, float z1);
int vw_scale_xyz(float x1, float y1, float z1);
int vw_create_matrix_from_vertice(matrix_t *result, vw_point_t source);
int vw_create_matrix_from_move(matrix_t *result, MOVE move, float a, float b,
                               float c);
int vw_copy_vertices_data(matrix_t *source, vw_point_t *dst);

void vw_dim_calc(MOVE move, float *dim_ptr, matrix_t src);

void vw_spin_xy_matrix_init(matrix_t *A, float grad);
void vw_spin_xz_matrix_init(matrix_t *A, float grad);
void vw_spin_yz_matrix_init(matrix_t *A, float grad);
void vw_move_xyz_matrix_init(matrix_t *A, float x1, float y1, float z1);
void vw_scale_xyz_matrix_init(matrix_t *A, float x1, float y1, float z1);

int vw_scene_check(void);
vw_model_t *vw_get_model(int *answer);

#endif  // __AFFINE_TRANSFORMATION_H__