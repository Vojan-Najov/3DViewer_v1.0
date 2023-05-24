#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "vw_model.h"
#include "vw_parser.h"

START_TEST(test_01) {
	char str[] = "";
	vw_model_t model;
	int err_status;

	memset((void*) &model, 0, sizeof(vw_model_t));
	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_02) {
	char str[] = "13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_03) {
	char str[] = "13 12";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_04) {
	char str[] = "    \t     ";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_05) {
	char str[] = "    1.12da   ";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_06) {
	char str[] = "    1.12da 12.12 12.13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_07) {
	char str[] = "    1.12 da12.12 12.13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_08) {
	char str[] = "    1.12 12.12- 12.13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_09) {
	char str[] = "    1.12 12.12 - 12.13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_10) {
	char str[] = "    1.12 12.12 a12.13";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_11) {
	char str[] = "    1.12 12.12  12.13b";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_12) {
	char str[] = "    1.12 12.12  12.13 \tb1";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_13) {
	char str[] = "    1.12 12.12  12.13 \t1.0b";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_14) {
	char str[] = "    1.12 12.12  12.13 \t1      b";
	vw_model_t model;
	int err_status;

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_15) {
	char str[512] = "";
	vw_model_t model;
	int err_status;
	vw_point_t p = {112.2, -3939.193, 38389.3938, 1.0};

	memset(&model, 0, sizeof(vw_model_t));

	sprintf(str, "   %f   %f    %f", p[0], p[1], p[2]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(1, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[0][0], p[0]);
	ck_assert_float_eq(model.vertices[0][1], p[1]);
	ck_assert_float_eq(model.vertices[0][2], p[2]);
	ck_assert_float_eq(model.vertices[0][3], p[3]);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_16) {
	char str[512] = "";
	vw_model_t model;
	int err_status;
	vw_point_t p = {112.2, -3939.193, 38389.3938, 1.0};

	memset(&model, 0, sizeof(vw_model_t));

	sprintf(str, "   %f   %f    %f      \n", p[0], p[1], p[2]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(1, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[0][0], p[0]);
	ck_assert_float_eq(model.vertices[0][1], p[1]);
	ck_assert_float_eq(model.vertices[0][2], p[2]);
	ck_assert_float_eq(model.vertices[0][3], p[3]);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_17) {
	char str[512] = "";
	vw_model_t model;
	int err_status;
	vw_point_t p = {112.2, -3939.193, 38389.3938, 4.0};

	memset(&model, 0, sizeof(vw_model_t));

	sprintf(str, "   %f   %f    %f %f\n", p[0], p[1], p[2], p[3]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(1, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[0][0], p[0]);
	ck_assert_float_eq(model.vertices[0][1], p[1]);
	ck_assert_float_eq(model.vertices[0][2], p[2]);
	ck_assert_float_eq(model.vertices[0][3], p[3]);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_18) {
	char str[512] = "";
	vw_model_t model;
	int err_status;
	vw_point_t p = {112.2, -3939.193, 38389.3938, 4.0};

	memset(&model, 0, sizeof(vw_model_t));

	sprintf(str, "   %f   %f    %f %f\n", p[0], p[1], p[2], p[3]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(1, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[0][0], p[0]);
	ck_assert_float_eq(model.vertices[0][1], p[1]);
	ck_assert_float_eq(model.vertices[0][2], p[2]);
	ck_assert_float_eq(model.vertices[0][3], p[3]);
	
	p[0] = -4848.484; p[1] = 3939.183; p[2] = 3838.383; p[3] = -338.12;
	sprintf(str, "   %f   %f    %f %f     \n", p[0], p[1], p[2], p[3]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(2, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[1][0], p[0]);
	ck_assert_float_eq(model.vertices[1][1], p[1]);
	ck_assert_float_eq(model.vertices[1][2], p[2]);
	ck_assert_float_eq(model.vertices[1][3], p[3]);
	
	vw_model_clear(&model);
}
END_TEST


START_TEST(test_19) {
	char str[512];
	vw_model_t model;
	int err_status;
	vw_point_t *p;

	memset(&model, 0, sizeof(vw_model_t));
	p = (vw_point_t *) malloc(sizeof(vw_point_t) * 100000);
	if (p == NULL) {
		return;
	}

	for (int i = 0; i < 100000; ++i) {
		p[i][0] = i * 2.12;
		p[i][1] = i * -4.8282;
		p[i][2] = i * 1.3838;
		p[i][3] = (i + 1) * -1.21;
		sprintf(str, "   %f   %f \t   %f %f      \n", \
                p[i][0], p[i][1], p[i][2], p[i][3]);
		err_status = vw_parse_vertex(str, &model);
		ck_assert_int_eq(err_status, 0);
	}
	ck_assert_int_eq(100000, (int)model.number_of_vertices);
	for (int i = 0; i < 100000; ++i) {
		ck_assert_float_eq(p[i][0], model.vertices[i][0]);
		ck_assert_float_eq(p[i][1], model.vertices[i][1]);
		ck_assert_float_eq(p[i][2], model.vertices[i][2]);
		ck_assert_float_eq(p[i][3], model.vertices[i][3]);
	}

	free(p);
	vw_model_clear(&model);
}
END_TEST

START_TEST(test_20) {
	char str[512] = "";
	vw_model_t model;
	int err_status;
	vw_point_t p = {112.2, -3939.193, 38389.3938, 4.0};

	memset(&model, 0, sizeof(vw_model_t));

	sprintf(str, "   %f   %f    %f %f\n", p[0], p[1], p[2], p[3]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(1, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[0][0], p[0]);
	ck_assert_float_eq(model.vertices[0][1], p[1]);
	ck_assert_float_eq(model.vertices[0][2], p[2]);
	ck_assert_float_eq(model.vertices[0][3], p[3]);

	err_status = vw_parse_vertex("123 334e 1332d", &model);
	ck_assert_int_ne(err_status, 0);

	
	p[0] = -4848.484; p[1] = 3939.183; p[2] = 3838.383; p[3] = -338.12;
	sprintf(str, "   %f   %f    %f %f     \n", p[0], p[1], p[2], p[3]);

	err_status = vw_parse_vertex(str, &model);
	ck_assert_int_eq(err_status, 0);
	ck_assert_int_eq(2, model.number_of_vertices);
	ck_assert_float_eq(model.vertices[1][0], p[0]);
	ck_assert_float_eq(model.vertices[1][1], p[1]);
	ck_assert_float_eq(model.vertices[1][2], p[2]);
	ck_assert_float_eq(model.vertices[1][3], p[3]);
	
	vw_model_clear(&model);
}
END_TEST

Suite *test_vw_parse_vertex(void) {
	Suite *s;
	TCase *tc;

	s = suite_create("vw_parse_vertex");
	if (s != NULL) {
		tc = tcase_create("vw_parse_vertex");
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
