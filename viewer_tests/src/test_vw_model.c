#include <check.h>
#include <stdlib.h>

#include "vw_scene.h"

START_TEST(test_model) {
	int err_status;
	vw_scene_create();
	err_status = vw_scene_set_model("../misc/objects/woman.obj");
	ck_assert_int_eq(err_status, 0);
	err_status = vw_save_model_to_objfile("../misc/objects/woman_save.obj",
                                          vw_scene_get_model());
	ck_assert_int_eq(err_status, 0);
	vw_scene_clear();
}
END_TEST

Suite *test_vw_model(void) {
	Suite *s;
	TCase *tc;

	s = suite_create("vw_model");
	if (s != NULL) {
		tc = tcase_create("vw_model");
		if (tc != NULL) {
			tcase_add_test(tc, test_model);
			suite_add_tcase(s, tc);
		} else {
			free(s);
			s = NULL;
		}
	}

	return (s);
}
