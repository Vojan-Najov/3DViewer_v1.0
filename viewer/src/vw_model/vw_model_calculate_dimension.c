#include "vw_model.h"
#include <math.h>

void vw_model_calculate_dimension(vw_model_t *model) {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	size_t n = model->number_of_vertices;
	vw_point_t *v = model->vertices;
	float d = 0.0f;
	float tmp;
	size_t i;

	for (i = 0; i < n; ++i) {
		x += v[i][0];
		y += v[i][1];
		z += v[i][2];
	}
	x /= (float) n;
	y /= (float) n;
	z /= (float) n;
	model->centre[0] = x;
	model->centre[1] = y;
	model->centre[2] = z;
	model->centre[3] = 1.0f;

	for (i = 0; i < n; ++i) {
		tmp = sqrtf(powf(v[i][0] - x, 2.0f) +
                    powf(v[i][1] - y, 2.0f) +
                    powf(v[i][2] - z, 2.0f));
		if (tmp > d) {
			d = tmp;
		}
	}
	if (d < 1.0e-6f) {
		d = 1.0f;
	}
	model->dim = d;
}

