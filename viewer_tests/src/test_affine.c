#include <check.h>
#include <stdlib.h>

#include "test_viewer.h"

START_TEST(test_affine_01) {
	vw_scene_create();
	int answer = vw_scene_set_model("../misc/objects/test_affine.obj");
    ck_assert_int_eq(answer, SUCCESS);
    answer = vw_spin_xy(90);
    ck_assert_int_eq(answer, SUCCESS);
    vw_model_t *model = vw_get_model(&answer);
    ck_assert_int_eq(answer, SUCCESS);
    if (!model)
        answer = FAILURE;
    ck_assert_int_eq(answer, SUCCESS);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][0], 0.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][2], 1.0, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][0], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][2], 1.0, 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->centre[0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[2], 1., 1e-06);
	vw_scene_clear();
}
END_TEST

START_TEST(test_affine_02) {
	vw_scene_create();
	int answer = vw_scene_set_model("../misc/objects/test_affine.obj");
    ck_assert_int_eq(answer, SUCCESS);
    answer = vw_spin_xz(90);
    ck_assert_int_eq(answer, SUCCESS);
    vw_model_t *model = vw_get_model(&answer);
    ck_assert_int_eq(answer, SUCCESS);
    if (!model)
        answer = FAILURE;
    ck_assert_int_eq(answer, SUCCESS);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][1], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][2], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][1], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][2], 1., 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->centre[0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[2], 1., 1e-06);
	vw_scene_clear();
}
END_TEST

START_TEST(test_affine_03) {
	vw_scene_create();
	int answer = vw_scene_set_model("../misc/objects/test_affine.obj");
    ck_assert_int_eq(answer, SUCCESS);
    answer = vw_spin_yz(90);
    ck_assert_int_eq(answer, SUCCESS);
    vw_model_t *model = vw_get_model(&answer);
    ck_assert_int_eq(answer, SUCCESS);
    if (!model)
        answer = FAILURE;
    ck_assert_int_eq(answer, SUCCESS);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][2], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][2], 0.5, 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->centre[0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[2], 1., 1e-06);
	vw_scene_clear();
}
END_TEST

START_TEST(test_affine_04) {
	vw_scene_create();
	int answer = vw_scene_set_model("../misc/objects/test_affine.obj");
    ck_assert_int_eq(answer, SUCCESS);
    answer = vw_move_xyz(1., 1., 1.);
    ck_assert_int_eq(answer, SUCCESS);
    vw_model_t *model = vw_get_model(&answer);
    ck_assert_int_eq(answer, SUCCESS);
    if (!model)
        answer = FAILURE;
    ck_assert_int_eq(answer, SUCCESS);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][0], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][1], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][2], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][0], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][1], 3., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][2], 2., 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->centre[0], 2., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[1], 2.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[2], 2., 1e-06);
	vw_scene_clear();
}
END_TEST

START_TEST(test_affine_05) {
	vw_scene_create();
	int answer = vw_scene_set_model("../misc/objects/test_affine.obj");
    ck_assert_int_eq(answer, SUCCESS);
    answer = vw_scale_xyz(2., 2., 2.);
    ck_assert_int_eq(answer, SUCCESS);
    vw_model_t *model = vw_get_model(&answer);
    ck_assert_int_eq(answer, SUCCESS);
    if (!model)
        answer = FAILURE;
    ck_assert_int_eq(answer, SUCCESS);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][1], 0.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[0][2], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][1], 2.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->vertices[1][2], 1., 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->centre[0], 1., 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[1], 1.5, 1e-06);
    ck_assert_float_eq_tol(vw_scene_get_model()->centre[2], 1., 1e-06);

    ck_assert_float_eq_tol(vw_scene_get_model()->dim, 1., 1e-06);
	vw_scene_clear();
}
END_TEST

Suite *test_affine(void) {
	Suite *s;
	TCase *tc;

	s = suite_create("affine transformation");
	if (s != NULL) {
		tc = tcase_create("affine transformation");
		if (tc != NULL) {
			tcase_add_test(tc, test_affine_01);
            tcase_add_test(tc, test_affine_02);
            tcase_add_test(tc, test_affine_03);
            tcase_add_test(tc, test_affine_04);
            tcase_add_test(tc, test_affine_05);
			suite_add_tcase(s, tc);
		} else {
			free(s);
			s = NULL;
		}
	}

	return (s);
}
