#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "vw_parser.h"


static size_t *vw_get_vertex_array_size(void);
static int vw_insert_vertex(vw_model_t *model, vw_point_t *v);

int vw_parse_vertex(char *str, vw_model_t *model) {
	vw_point_t v;
	int err_status = 0;

	v[0] = strtof(str, &str); // try to convert x coordinate
	if (!isspace(*str)) {
		err_status = VW_INCORRECT_LINE; // x conversion error
	}
	if (!err_status) {  // try to convert y coordinate
		v[1] = strtof(str, &str);
		if (!isspace(*str)) {
			err_status = VW_INCORRECT_LINE; // y conversion error
		}
	}
	if (!err_status) { // try to convert z coordinate
		while (isspace(*str)) {
			++str;
		}
		if (!*str) {
			err_status = VW_INCORRECT_LINE; // z conversion error
		} else {
			v[2] = strtof(str, &str);
			if (*str && !isspace(*str)) {
				err_status = VW_INCORRECT_LINE; // z conversion error
			}
		}
	}
	if (!err_status) { // try to convert w coordinate
		v[3] = strtof(str, &str);
		if (v[3] > -1.0e-6 && v[3] < 1.0e-6) {
			v[3] = 1.0;
		}
		while (isspace(*str)) {
			++str;
		}
		if (*str) {
			err_status = VW_INCORRECT_LINE; // w conversion error
		}
	}
	
	if (!err_status) {
		err_status = vw_insert_vertex(model, &v);
	}

	return (err_status);
}

static int vw_insert_vertex(vw_model_t *model, vw_point_t *v) {
	size_t *size_ptr;
	size_t start_number_of_vertices = 1;
	int err_status = 0;

	size_ptr = vw_get_vertex_array_size();

	if (model->vertices == NULL) {
		// create array of vertices
		*size_ptr = start_number_of_vertices;
		model->vertices =
			(vw_point_t *)malloc(sizeof(vw_point_t) * (*size_ptr));
	} else if (model->number_of_vertices >= (*size_ptr)) {
		*size_ptr *= 2;
		model->vertices = 
			(vw_point_t *) realloc(model->vertices, 
                                   *size_ptr * sizeof(vw_point_t));
	}

	if (model->vertices == NULL) {
		err_status = VW_ALLOC_ERROR;
	} else {
		// insert a vertex at the end of the array
		model->vertices[model->number_of_vertices][0] = (*v)[0];
		model->vertices[model->number_of_vertices][1] = (*v)[1];
		model->vertices[model->number_of_vertices][2] = (*v)[2];
		model->vertices[model->number_of_vertices][3] = (*v)[3];
		++model->number_of_vertices;
	}

	return (err_status);
}

static size_t *vw_get_vertex_array_size(void) {
	static size_t n;

	return (&n);
}

int vw_reduce_vertex_array(vw_model_t *model) {
	size_t n;
	size_t *size_ptr;
	int err_status = 0;

	size_ptr = vw_get_vertex_array_size();

	if (model->vertices != NULL && model->number_of_vertices < *size_ptr) {
		n = model->number_of_vertices * sizeof(vw_point_t);
		model->vertices = (vw_point_t *) realloc(model->vertices, n);
		*size_ptr = model->number_of_vertices;
		if (model->vertices == NULL) {
			err_status = VW_ALLOC_ERROR;
		}
	}

	return (err_status);
}

