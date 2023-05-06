#include <stdio.h>

#include "vw_model.h"

int main () {
	vw_model_t model;
	int err_status = 0;

	err_status = vw_parse_objfile_to_model("./woman.obj", &model);

	if (!err_status) {

		for (size_t i = 0; i < model.number_of_vertices; ++i) {
			printf("x=%f  y=%f  z=%f  w=%f\n", 
				model.vertices[i][0],
				model.vertices[i][1],
				model.vertices[i][2],
				model.vertices[i][3]);
		}
		for (size_t i = 0; i < model.number_of_faces; ++i) {
			printf("f ");
			for (size_t j = 0; j < model.faces[i].number_of_idx; ++j) {
				printf("%d ", model.faces[i].idx[j]);
			}
			printf("\n");
		}

		vw_save_model_to_objfile("./out.obj", &model);
		vw_clear_model(&model);
	}	

	return (0);
}
