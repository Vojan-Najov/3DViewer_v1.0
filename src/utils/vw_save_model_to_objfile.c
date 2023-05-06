#include <stdio.h>
#include "vw_model.h"

int vw_save_model_to_objfile(const char *pathname, vw_model_t *model) {
	FILE *stream;
	size_t i, j;
	int nwrite = 0;
	int err_status = 0;

	stream = fopen(pathname, "w");

	if (stream == NULL) {
		err_status = VW_OPEN_FILE_ERROR;
	} else {
		nwrite = fprintf(stream, "#created by 3DViewer-v1.0\n\n");
		for (i = 0; i < model->number_of_vertices && nwrite >= 0; ++i) {
			nwrite = fprintf(stream, "v %f %f %f", 
                             model->vertices[i][0],
                             model->vertices[i][1],
                             model->vertices[i][2]);
			if (model->vertices[i][3] == 1.0) {
				nwrite = fprintf(stream, "\n");
			} else {
				nwrite = fprintf(stream, " %f\n", model->vertices[i][3]);
			}
		}
		nwrite = fprintf(stream, "\n");
		for (i = 0; i < model->number_of_faces && nwrite >= 0; ++i) {
			nwrite = fprintf(stream, "f");
			for (j = 0; j < model->faces[i].number_of_idx; ++j) {
				nwrite = fprintf(stream, " %u", model->faces[i].idx[j] + 1);
			}
			nwrite = fprintf(stream, "\n");
		}
		nwrite = fprintf(stream, "\n");
	}

	if (stream != NULL) {
		if (fclose(stream) != 0) {
			err_status = VW_CLOSE_FILE_ERROR;
		}
	}
	if (nwrite < 0) {
		err_status = VW_WRITE_FILE_ERROR;
	}

	return (err_status);
}
