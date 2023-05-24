#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "vw_model.h"
#include "vw_parser.h"

static vw_model_t *init_model(void) {
	int err_status = 0;
	vw_model_t *model;

	model = (vw_model_t *) calloc(1, sizeof(vw_model_t));
	if (model != NULL) {
		for (int i = 0; !err_status && i < 10; ++i) {
			err_status = vw_parse_vertex("1 2 3", model);
		}
		if (err_status) {
			vw_model_clear(model);
			free(model);
			model = NULL;
		}
	}

	return (model);
}

START_TEST(test_01) {
	char str[] = "";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_02) {
	char str[] = "       ";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_03) {
	char str[] = "   asad    ";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_04) {
	char str[] = " 1 2 3  123.5     ";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_05) {
	char str[] = " 11 ";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_06) {
	char str[] = " 11 1 ";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_07) {
	char str[] = " 11 1 -12 1r";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_08) {
	char str[] = " 11 1 -12 1    r";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));

	err_status = vw_parse_face(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_09) {
	char str[] = " 1 2 3 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_10) {
	char str[] = " 1 2 3 4 5 6 7 8 9 10 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(10, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		ck_assert_int_eq(3, (int)model->faces[0].idx[3]);
		ck_assert_int_eq(4, (int)model->faces[0].idx[4]);
		ck_assert_int_eq(5, (int)model->faces[0].idx[5]);
		ck_assert_int_eq(6, (int)model->faces[0].idx[6]);
		ck_assert_int_eq(7, (int)model->faces[0].idx[7]);
		ck_assert_int_eq(8, (int)model->faces[0].idx[8]);
		ck_assert_int_eq(9, (int)model->faces[0].idx[9]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_11) {
	char str[] = " -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(10, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(9, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(8, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(7, (int)model->faces[0].idx[2]);
		ck_assert_int_eq(6, (int)model->faces[0].idx[3]);
		ck_assert_int_eq(5, (int)model->faces[0].idx[4]);
		ck_assert_int_eq(4, (int)model->faces[0].idx[5]);
		ck_assert_int_eq(3, (int)model->faces[0].idx[6]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[7]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[8]);
		ck_assert_int_eq(0, (int)model->faces[0].idx[9]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_12) {
	char str1[] = " 1 2 3 ";
	char str2[] = " -1 -2 -3 ";
	char str3[] = " 4 -5 -6 7 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str1, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		err_status = vw_parse_face(str2, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(2, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[1].number_of_idx);
		ck_assert_int_eq(10 - 1, (int)model->faces[1].idx[0]);
		ck_assert_int_eq(9 - 1, (int)model->faces[1].idx[1]);
		ck_assert_int_eq(8 - 1, (int)model->faces[1].idx[2]);
		err_status = vw_parse_face(str3, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(3, (int)model->number_of_faces);
		ck_assert_int_eq(4, (int)model->faces[2].number_of_idx);
		ck_assert_int_eq(4 - 1, (int)model->faces[2].idx[0]);
		ck_assert_int_eq(6 - 1, (int)model->faces[2].idx[1]);
		ck_assert_int_eq(5 - 1, (int)model->faces[2].idx[2]);
		ck_assert_int_eq(7 - 1, (int)model->faces[2].idx[3]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_13) {
	char str[] = " 1// 2// 3// ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_14) {
	char str[] = " 1/-1/2 2//-2 3/3/ ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_15) {
	char str[] = " 1 11 3 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(VW_INCORRECT_LINE, err_status);
		ck_assert_int_eq(0, (int)model->number_of_faces);
		ck_assert_ptr_null(model->faces);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_16) {
	char str1[] = " 1 -3 3 ";
	char str2[] = " 1 -12 3 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str1, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		err_status = vw_parse_face(str2, model);
		ck_assert_int_eq(VW_INCORRECT_LINE, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_17) {
	char str[] = " 1 0 3 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(VW_INCORRECT_LINE, err_status);
		ck_assert_int_eq(0, (int)model->number_of_faces);
		ck_assert_ptr_null(model->faces);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_18) {
	char str[] = " 1/2 2/1 3/1 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(3, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_19) {
	char str[] = " 1 2/1 3//1 4/2/2 5// 6//-1 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		err_status = vw_parse_face(str, model);
		ck_assert_int_eq(0, err_status);
		ck_assert_int_eq(1, (int)model->number_of_faces);
		ck_assert_int_eq(6, (int)model->faces[0].number_of_idx);
		ck_assert_int_eq(0, (int)model->faces[0].idx[0]);
		ck_assert_int_eq(1, (int)model->faces[0].idx[1]);
		ck_assert_int_eq(2, (int)model->faces[0].idx[2]);
		ck_assert_int_eq(3, (int)model->faces[0].idx[3]);
		ck_assert_int_eq(4, (int)model->faces[0].idx[4]);
		ck_assert_int_eq(5, (int)model->faces[0].idx[5]);
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

START_TEST(test_20) {
	char str[] = " 1 2/1 3//1 -4/2/2 -5// -6//-1 ";
	vw_model_t *model;
	int err_status;

	model = init_model();
	if (model != NULL) {
		for (int i = 0; i < 129; ++i) {
			err_status = vw_parse_face(str, model);
			ck_assert_int_eq(0, err_status);
		}
		ck_assert_int_eq(129, (int)model->number_of_faces);
		for (int i = 0; i < 129; ++i) {
			ck_assert_int_eq(6, (int)model->faces[i].number_of_idx);
			ck_assert_int_eq(0, (int)model->faces[i].idx[0]);
			ck_assert_int_eq(1, (int)model->faces[i].idx[1]);
			ck_assert_int_eq(2, (int)model->faces[i].idx[2]);
			ck_assert_int_eq(7 - 1, (int)model->faces[i].idx[3]);
			ck_assert_int_eq(6 - 1, (int)model->faces[i].idx[4]);
			ck_assert_int_eq(5 - 1, (int)model->faces[i].idx[5]);
		}
		vw_model_clear(model);
		free(model);
	}
}
END_TEST

Suite *test_vw_parse_face(void) {
	Suite *s;
	TCase *tc;

	s = suite_create("vw_parse_face");
	if (s != NULL) {
		tc = tcase_create("vw_parse_face");
		if (tc != NULL) {
			tcase_add_test(tc, test_01);
			tcase_add_test(tc, test_02);
			tcase_add_test(tc, test_03);
			tcase_add_test(tc, test_04);
			tcase_add_test(tc, test_05);
			tcase_add_test(tc, test_06);
			tcase_add_test(tc, test_07);
			tcase_add_test(tc, test_08);
			tcase_add_test(tc, test_09);
			tcase_add_test(tc, test_10);
			tcase_add_test(tc, test_11);
			tcase_add_test(tc, test_12);
			tcase_add_test(tc, test_13);
			tcase_add_test(tc, test_14);
			tcase_add_test(tc, test_15);
			tcase_add_test(tc, test_16);
			tcase_add_test(tc, test_17);
			tcase_add_test(tc, test_18);
			tcase_add_test(tc, test_19);
			tcase_add_test(tc, test_20);
			suite_add_tcase(s, tc);
		} else {
			free(s);
			s = NULL;
		}
	}

	return (s);
}
