#include <stdlib.h>
#include "vw_model.h"

void vw_model_clear(vw_model_t *model) {
	size_t i;

	free(model->vertices);
	for (i = 0; i < model->number_of_faces; ++i) {
		free(model->faces[i].idx);
	}
	free(model->faces);

	model->vertices = NULL;
	model->number_of_vertices = 0;
	model->faces = NULL;
	model->number_of_faces = 0;
}
