#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vw_parser.h"

static int vw_count_number_of_idx(const char *str);
static size_t *vw_get_face_array_size(void);
static int vw_insert_face(vw_model_t *model, unsigned int *idx,
                          size_t number_of_idx);

int vw_parse_face(char *str, vw_model_t *model) {
    int number_of_idx;
    unsigned int *idx;
    long num;
    int err_status = 0;

    number_of_idx = vw_count_number_of_idx(str);

    if (number_of_idx > 2) {
        idx = (unsigned int *)malloc(number_of_idx * sizeof(unsigned int));
        if (idx == NULL) {
            err_status = VW_ALLOC_ERROR;
        } else {
            for (int i = 0; i < number_of_idx; ++i) {
                num = strtol(str, &str, 0);
                if (*str == '/') {
                    ++str;
                }
                if (*str && !isspace(*str)) {
                    strtol(str, &str, 0);
                }
                if (*str == '/') {
                    ++str;
                }
                if (*str && !isspace(*str)) {
                    strtol(str, &str, 0);
                }
                if (*str && !isspace(*str)) {
                    err_status = VW_INCORRECT_LINE;
                }
                if (num > 0 && num <= (long)model->number_of_vertices) {
                    idx[i] = (unsigned int)(num - 1);
                } else if (num < 0 && -num <= (long)model->number_of_vertices) {
                    idx[i] = model->number_of_vertices + num;
                } else {
                    err_status = VW_INCORRECT_LINE;
                }
            }
            if (!err_status) {
                err_status = vw_insert_face(model, idx, number_of_idx);
            } else {
                free(idx);
            }
        }
    } else {
        err_status = VW_INCORRECT_LINE;
    }

    return (err_status);
}

static int vw_count_number_of_idx(const char *str) {
    int count = 0;
    const char *tmp = "0123456789+-x/";

    while (*str && count != -1) {
        while (isspace(*str)) {
            ++str;
        }
        if (*str) {
            str += strspn(str, tmp);
            if (isspace(*str) || !*str) {
                ++count;
            } else {
                count = -1;
            }
        }
    }

    return (count);
}

static int vw_insert_face(vw_model_t *model, unsigned int *idx,
                          size_t number_of_idx) {
    size_t *size_ptr;
    size_t start_number_of_faces = 1;
    int err_status = 0;

    size_ptr = vw_get_face_array_size();

    if (model->faces == NULL) {
        *size_ptr = start_number_of_faces;
        model->faces = (vw_face_t *)malloc(sizeof(vw_face_t) * (*size_ptr));
    } else if (model->number_of_faces >= (*size_ptr)) {
        *size_ptr *= 2;
        model->faces =
            (vw_face_t *)realloc(model->faces, *size_ptr * sizeof(vw_face_t));
    }

    if (model->faces == NULL) {
        err_status = VW_ALLOC_ERROR;
    } else {
        // insert a face at the end of the array
        model->faces[model->number_of_faces].idx = idx;
        model->faces[model->number_of_faces].number_of_idx = number_of_idx;
        ++model->number_of_faces;
    }

    return (err_status);
}

static size_t *vw_get_face_array_size(void) {
    static size_t size;

    return (&size);
}

int vw_reduce_face_array(vw_model_t *model) {
    size_t n;
    size_t *size_ptr;
    int err_status = 0;

    size_ptr = vw_get_face_array_size();

    if (model->faces != NULL && model->number_of_faces < *size_ptr) {
        n = model->number_of_faces * sizeof(vw_face_t);
        model->faces = (vw_face_t *)realloc(model->faces, n);
        *size_ptr = model->number_of_faces;
        if (model->faces == NULL) {
            model->faces = 0;
            err_status = VW_ALLOC_ERROR;
        }
    }

    return (err_status);
}
