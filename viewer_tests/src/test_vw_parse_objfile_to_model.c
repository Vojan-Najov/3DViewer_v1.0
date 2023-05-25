#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "vw_model.h"
#include "vw_parser.h"

START_TEST(test_01) {
    int err_status;
    vw_model_t model;

    err_status = vw_parse_objfile_to_model("../misc/objects/woman.obj", &model);
    ck_assert_int_eq(err_status, 0);
    vw_model_clear(&model);
}
END_TEST

START_TEST(test_02) {
    int err_status;
    vw_model_t model;

    err_status = vw_parse_objfile_to_model("../misc/objects/noexist", &model);
    ck_assert_int_eq(err_status, VW_OPEN_FILE_ERROR);
}
END_TEST

START_TEST(test_03) {
    int err_status;
    vw_model_t model;

    err_status =
        vw_parse_objfile_to_model("../misc/objects/bad_model.obj", &model);
    ck_assert_int_eq(err_status, VW_INCORRECT_LINE);
}
END_TEST

START_TEST(test_04) {
    int err_status;
    vw_model_t model;

    err_status =
        vw_parse_objfile_to_model("../misc/objects/affine.obj", &model);
    ck_assert_int_eq(err_status, 0);
    ck_assert(model.number_of_vertices == 8);
    vw_model_clear(&model);
}
END_TEST

Suite *test_vw_parse_objfile_to_model(void) {
    Suite *s;
    TCase *tc;

    s = suite_create("vw_parse_objfile_to_model");
    if (s != NULL) {
        tc = tcase_create("vw_parse_objfile_to_model");
        if (tc != NULL) {
            tcase_add_test(tc, test_01);
            tcase_add_test(tc, test_02);
            tcase_add_test(tc, test_03);
            tcase_add_test(tc, test_04);
            suite_add_tcase(s, tc);
        } else {
            free(s);
            s = NULL;
        }
    }

    return (s);
}
