#include <stdio.h>

#include "vw_affine.h"

int vw_scene_check(void) {
    int answer = SUCCESS;
    //  vw_scene_t *scene = vw_scene_get();
    //  if (!scene)
    //    answer = FAILURE;
    vw_model_t *model = vw_scene_get_model();
    if (answer == SUCCESS && !model) answer = FAILURE;
    if (answer == SUCCESS && !model->vertices) answer = FAILURE;
    return answer;
}

vw_model_t *vw_get_model(int *answer) {
    vw_model_t *model = NULL;
    *answer = vw_scene_check();
    if (*answer == SUCCESS) model = vw_scene_get_model();
    return model;
}

/*
int vw_centering_vector(vw_point_t *centering_step) {
  int answer = SUCCESS;
  vw_model_t *model = vw_get_model(&answer);
  if (!centering_step)
    answer = FAILURE;
  if (answer == SUCCESS) {
    float xMin = model->vertices[0][0], yMin = model->vertices[0][1], zMin =
model->vertices[0][2]; float xMax = model->vertices[0][0], yMax =
model->vertices[0][1], zMax = model->vertices[0][2]; for (size_t i = 1; i <
(size_t)model->number_of_vertices; i++) { if (model->vertices[i][0] < xMin) xMin
= model->vertices[i][0]; if (model->vertices[i][0] > xMax) xMax =
model->vertices[i][0]; if (model->vertices[i][1] < yMin) yMin =
model->vertices[i][1]; if (model->vertices[i][1] > yMax) yMax =
model->vertices[i][1]; if (model->vertices[i][2] < zMin) zMin =
model->vertices[i][2]; if (model->vertices[i][2] > zMax) zMax =
model->vertices[i][2];
    }
    (*centering_step)[0] = (xMax + xMin) / 2.;
    (*centering_step)[1] = (yMax + yMin) / 2.;
    (*centering_step)[2] = (zMax + zMin) / 2.;
  }
  return answer;
}
*/

int vw_move(MOVE move, float a, float b, float c) {
    int answer = SUCCESS;
    float dim_new = 0.;
    matrix_t spin = {0, 0, NULL};
    matrix_t vector = {0, 0, NULL};
    matrix_t result = {0, 0, NULL};
    // vw_point_t center = {0, 0, 0, 0};
    vw_model_t *model = NULL;
    answer = create_matrix(VW_POINT_NUMBER_OF_COORDINATES,
                           VW_POINT_NUMBER_OF_COORDINATES, &spin);
    if (answer == SUCCESS) {
        answer = create_matrix(VW_POINT_NUMBER_OF_COORDINATES, 1, &vector);
    } else {
        remove_matrix(&spin);
        answer = FAILURE;
    }
    if (answer == SUCCESS)
        answer = create_matrix(VW_POINT_NUMBER_OF_COORDINATES, 1, &result);
    if (answer == SUCCESS)
        answer = vw_create_matrix_from_move(&spin, move, a, b, c);
    if (answer == SUCCESS) model = vw_get_model(&answer);
    if (answer == SUCCESS) {
        for (size_t i = 0; i < model->number_of_vertices; i++) {
            answer = vw_create_matrix_from_vertice(&vector, model->vertices[i]);
            if (answer == SUCCESS) {
                if (move != MOVE_XYZ) {
                    for (int j = 0; j < VW_POINT_NUMBER_OF_COORDINATES - 1; j++)
                        vector.matrix[j][0] -= model->centre[j];
                }
                answer = mult_matrix(&spin, &vector, &result);
                vw_dim_calc(move, &dim_new, result);
            }
            if (answer == SUCCESS) {
                if (move != MOVE_XYZ) {
                    for (int j = 0; j < VW_POINT_NUMBER_OF_COORDINATES - 1; j++)
                        result.matrix[j][0] += model->centre[j];
                }
                answer = vw_copy_vertices_data(&result, &model->vertices[i]);
            }
            if (answer == FAILURE) break;
        }
        if (move == MOVE_XYZ) {
            answer = vw_create_matrix_from_vertice(&vector, model->centre);
            if (answer == SUCCESS)
                answer = mult_matrix(&spin, &vector, &result);
            if (answer == SUCCESS)
                answer = vw_copy_vertices_data(&result, &model->centre);
        }
        if (move == SCALE_XYZ) model->dim = dim_new;
    }
    remove_matrix(&vector);
    remove_matrix(&spin);
    remove_matrix(&result);
    return answer;
}

void vw_dim_calc(MOVE move, float *dim_ptr, matrix_t src) {
    if (move == SCALE_XYZ) {
        float temp = 0.;
        for (int j = 0; j < VW_POINT_NUMBER_OF_COORDINATES - 1; j++)
            temp += powl(src.matrix[j][0], 2.);
        if (*dim_ptr < sqrtl(temp)) *dim_ptr = sqrtl(temp);
    }
}

int vw_spin_xy(float grad) { return vw_move(SPIN_XY, grad, 0, 0); }

int vw_spin_xz(float grad) { return vw_move(SPIN_XZ, grad, 0, 0); }

int vw_spin_yz(float grad) { return vw_move(SPIN_YZ, grad, 0, 0); }

int vw_move_xyz(float x1, float y1, float z1) {
    return vw_move(MOVE_XYZ, x1, y1, z1);
}

int vw_scale_xyz(float x1, float y1, float z1) {
    return vw_move(SCALE_XYZ, x1, y1, z1);
}

int vw_create_matrix_from_vertice(matrix_t *result, vw_point_t source) {
    int answer = SUCCESS;
    if (!result) answer = FAILURE;
    if (answer == SUCCESS &&
        (result->columns != 1 || result->rows != 4 || !result->matrix))
        answer = FAILURE;
    if (answer == SUCCESS) {
        for (int i = 0; i < VW_POINT_NUMBER_OF_COORDINATES; i++)
            result->matrix[i][0] = source[i];
    }
    return answer;
}

int vw_create_matrix_from_move(matrix_t *result, MOVE move, float a, float b,
                               float c) {
    int answer = SUCCESS;
    if (!result) answer = FAILURE;
    if (answer == SUCCESS &&
        (result->columns != 4 || result->rows != 4 || !result->matrix))
        answer = SUCCESS;
    if (answer == SUCCESS) {
        initialize_zero(result);
        if (move == SPIN_XY) {
            vw_spin_xy_matrix_init(result, a);
        } else if (move == SPIN_YZ) {
            vw_spin_yz_matrix_init(result, a);
        } else if (move == SPIN_XZ) {
            vw_spin_xz_matrix_init(result, a);
        } else if (move == MOVE_XYZ) {
            vw_move_xyz_matrix_init(result, a, b, c);
        } else if (move == SCALE_XYZ) {
            vw_scale_xyz_matrix_init(result, a, b, c);
        } else {
            answer = FAILURE;
        }
    }
    return answer;
}

int vw_copy_vertices_data(matrix_t *source, vw_point_t *dst) {
    int answer = SUCCESS;
    if (!source || !dst) answer = FAILURE;
    if (answer == SUCCESS &&
        (source->columns != 1 ||
         source->rows != VW_POINT_NUMBER_OF_COORDINATES || !source->matrix)) {
        answer = FAILURE;
    }
    if (answer == SUCCESS) {
        for (int i = 0; i < VW_POINT_NUMBER_OF_COORDINATES; i++) {
            (*dst)[i] = source->matrix[i][0];
        }
    }
    return answer;
}

void vw_spin_xy_matrix_init(matrix_t *A, float grad) {
    float rad = grad * PI / 180.;
    A->matrix[0][0] = cosl(rad);
    A->matrix[0][1] = sinl(rad);
    A->matrix[1][0] = -sinl(rad);
    A->matrix[1][1] = cosl(rad);
    A->matrix[2][2] = 1;
    A->matrix[3][3] = 1;
}

void vw_spin_xz_matrix_init(matrix_t *A, float grad) {
    float rad = grad * PI / 180.;
    A->matrix[0][0] = cosl(rad);
    A->matrix[0][2] = sinl(rad);
    A->matrix[2][0] = -sinl(rad);
    A->matrix[2][2] = cosl(rad);
    A->matrix[1][1] = 1;
    A->matrix[3][3] = 1;
}

void vw_spin_yz_matrix_init(matrix_t *A, float grad) {
    float rad = grad * PI / 180.;
    A->matrix[1][1] = cosl(rad);
    A->matrix[1][2] = sinl(rad);
    A->matrix[2][1] = -sinl(rad);
    A->matrix[2][2] = cosl(rad);
    A->matrix[0][0] = 1;
    A->matrix[3][3] = 1;
}

void vw_move_xyz_matrix_init(matrix_t *A, float x1, float y1, float z1) {
    A->matrix[0][0] = 1;
    A->matrix[0][3] = x1;
    A->matrix[1][1] = 1;
    A->matrix[1][3] = y1;
    A->matrix[2][2] = 1;
    A->matrix[2][3] = z1;
    A->matrix[3][3] = 1;
}

void vw_scale_xyz_matrix_init(matrix_t *A, float x1, float y1, float z1) {
    if (x1 == 0.) x1 = 1.;
    if (y1 == 0.) y1 = 1.;
    if (z1 == 0.) z1 = 1.;
    A->matrix[0][0] = x1;
    A->matrix[1][1] = y1;
    A->matrix[2][2] = z1;
    A->matrix[3][3] = 1;
}
