#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "vw_model.h"
#include "vw_parser.h"

START_TEST(test_01) {
    vw_scene_t scene;
    int err_status;

    err_status = vw_parse_config("../misc/tmp_config", &scene);
    ck_assert_int_eq(err_status, 0);
    ck_assert_int_eq(scene.projection_type, 2);
    ck_assert_int_eq(scene.line_type, 2);
    ck_assert_int_eq(scene.vertex_type, 3);
    ck_assert_float_eq(scene.line_size, 1.4000f);
    ck_assert_float_eq(scene.vertex_size, 1.5000f);
    ck_assert_float_eq(scene.line_color[0], 0.860000f);
    ck_assert_float_eq(scene.line_color[1], 0.1234000f);
    ck_assert_float_eq(scene.line_color[2], 0.9373100f);
    ck_assert_float_eq(scene.vertex_color[0], 0.659297f);
    ck_assert_float_eq(scene.vertex_color[1], 0.513252f);
    ck_assert_float_eq(scene.vertex_color[2], 1.000000f);
    ck_assert_float_eq(scene.bg_color[0], 0.8600000f);
    ck_assert_float_eq(scene.bg_color[1], 0.1234000f);
    ck_assert_float_eq(scene.bg_color[2], 0.937310f);
    ck_assert_float_eq(scene.bg_color[3], 1.00000f);
}
END_TEST

Suite *test_vw_parse_config(void) {
    Suite *s;
    TCase *tc;

    s = suite_create("vw_parse_config");
    if (s != NULL) {
        tc = tcase_create("vw_parse_config");
        if (tc != NULL) {
            tcase_add_test(tc, test_01);
            suite_add_tcase(s, tc);
        } else {
            free(s);
            s = NULL;
        }
    }

    return (s);
}
