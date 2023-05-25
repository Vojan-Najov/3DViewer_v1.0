#include <check.h>
#include <stdlib.h>

#include "vw_scene.h"

START_TEST(test_create_clear) {
    vw_point_t camera;

    vw_scene_create();
    vw_scene_get_camera(&camera[0], &camera[1], &camera[2]);
    vw_scene_clear();
}
END_TEST

START_TEST(test_projection) {
    int proj, ret_proj;

    vw_scene_create();
    proj = VW_PARALLEL_PROJECTION;
    vw_scene_set_projection_type(proj);
    ret_proj = vw_scene_get_projection_type();
    ck_assert_int_eq(proj, ret_proj);
    proj = VW_CENTRAL_PROJECTION;
    vw_scene_set_projection_type(proj);
    ret_proj = vw_scene_get_projection_type();
    ck_assert_int_eq(proj, ret_proj);
    vw_scene_clear();
}
END_TEST

START_TEST(test_line_type) {
    int line_type, ret_line_type;

    vw_scene_create();
    line_type = VW_SOLID_LINE;
    vw_scene_set_line_type(line_type);
    ret_line_type = vw_scene_get_line_type();
    ck_assert_int_eq(line_type, ret_line_type);
    line_type = VW_DASHED_LINE;
    vw_scene_set_line_type(line_type);
    ret_line_type = vw_scene_get_line_type();
    ck_assert_int_eq(line_type, ret_line_type);
    vw_scene_clear();
}
END_TEST

START_TEST(test_vertex_type) {
    int vertex_type, ret_vertex_type;

    vw_scene_create();
    vertex_type = VW_NONE_VERTEX;
    vw_scene_set_vertex_type(vertex_type);
    ret_vertex_type = vw_scene_get_vertex_type();
    ck_assert_int_eq(vertex_type, ret_vertex_type);
    vertex_type = VW_CIRCLE_VERTEX;
    vw_scene_set_vertex_type(vertex_type);
    ret_vertex_type = vw_scene_get_vertex_type();
    ck_assert_int_eq(vertex_type, ret_vertex_type);
    vertex_type = VW_SQUARE_VERTEX;
    vw_scene_set_vertex_type(vertex_type);
    ret_vertex_type = vw_scene_get_vertex_type();
    ck_assert_int_eq(vertex_type, ret_vertex_type);
    vw_scene_clear();
}
END_TEST

START_TEST(test_line_size) {
    int line_size, ret_line_size;

    vw_scene_create();
    line_size = 10.0;
    vw_scene_set_line_size(line_size);
    ret_line_size = vw_scene_get_line_size();
    ck_assert_float_eq(line_size, ret_line_size);
    line_size = 1.0;
    vw_scene_set_line_size(line_size);
    ret_line_size = vw_scene_get_line_size();
    ck_assert_float_eq(line_size, ret_line_size);
    vw_scene_clear();
}
END_TEST

START_TEST(test_vertex_size) {
    int vertex_size, ret_vertex_size;

    vw_scene_create();
    vertex_size = 10.3;
    vw_scene_set_vertex_size(vertex_size);
    ret_vertex_size = vw_scene_get_vertex_size();
    ck_assert_float_eq(vertex_size, ret_vertex_size);
    vertex_size = 1.0;
    vw_scene_set_vertex_size(vertex_size);
    ret_vertex_size = vw_scene_get_vertex_size();
    ck_assert_float_eq(vertex_size, ret_vertex_size);
    vw_scene_clear();
}
END_TEST

START_TEST(test_line_color) {
    float red, green, blue;
    float ret_red, ret_green, ret_blue;

    vw_scene_create();
    red = 0.1;
    green = 0.2;
    blue = 0.3;
    vw_scene_set_line_color(red, green, blue);
    vw_scene_get_line_color(&ret_red, &ret_green, &ret_blue);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
    red = 0.86;
    green = 0.1234;
    blue = 0.93731;
    vw_scene_set_line_color(red, green, blue);
    vw_scene_get_line_color(&ret_red, &ret_green, &ret_blue);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
    vw_scene_clear();
}
END_TEST

START_TEST(test_vertex_color) {
    float red, green, blue;
    float ret_red, ret_green, ret_blue;

    vw_scene_create();
    red = 0.1;
    green = 0.2;
    blue = 0.3;
    vw_scene_set_vertex_color(red, green, blue);
    vw_scene_get_vertex_color(&ret_red, &ret_green, &ret_blue);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
    red = 0.86;
    green = 0.1234;
    blue = 0.93731;
    vw_scene_set_vertex_color(red, green, blue);
    vw_scene_get_vertex_color(&ret_red, &ret_green, &ret_blue);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
}
END_TEST

START_TEST(test_background_color) {
    float red, green, blue, alpha;
    float ret_red, ret_green, ret_blue, ret_alpha;

    vw_scene_create();
    red = 0.1;
    green = 0.2;
    blue = 0.3, alpha = 1.0;
    vw_scene_set_background_color(red, green, blue, alpha);
    vw_scene_get_background_color(&ret_red, &ret_green, &ret_blue, &ret_alpha);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
    ck_assert_double_eq(alpha, ret_alpha);
    red = 0.86;
    green = 0.1234;
    blue = 0.93731, alpha = 0.5;
    vw_scene_set_background_color(red, green, blue, alpha);
    vw_scene_get_background_color(&ret_red, &ret_green, &ret_blue, &ret_alpha);
    ck_assert_double_eq(red, ret_red);
    ck_assert_double_eq(green, ret_green);
    ck_assert_double_eq(blue, ret_blue);
    ck_assert_double_eq(alpha, ret_alpha);
    vw_scene_clear();
}
END_TEST

START_TEST(test_model) {
    int err_status;
    vw_model_t *model;

    vw_scene_create();
    err_status = vw_scene_set_model("noexist.obj");
    ck_assert_int_ne(err_status, 0);
    model = vw_scene_get_model();
    ck_assert_ptr_null(model);
    err_status = vw_scene_set_model("../misc/objects/woman.obj");
    ck_assert_int_eq(err_status, 0);
    model = vw_scene_get_model();
    ck_assert_ptr_nonnull(model);
    err_status = vw_scene_set_model("../misc/objects/woman.obj");
    ck_assert_int_eq(err_status, 0);
    model = vw_scene_get_model();
    ck_assert_ptr_nonnull(model);

    vw_scene_clear();
}
END_TEST

Suite *test_vw_scene(void) {
    Suite *s;
    TCase *tc;

    s = suite_create("vw_scene");
    if (s != NULL) {
        tc = tcase_create("vw_scene");
        if (tc != NULL) {
            tcase_add_test(tc, test_create_clear);
            tcase_add_test(tc, test_projection);
            tcase_add_test(tc, test_line_type);
            tcase_add_test(tc, test_vertex_type);
            tcase_add_test(tc, test_line_size);
            tcase_add_test(tc, test_vertex_size);
            tcase_add_test(tc, test_line_color);
            tcase_add_test(tc, test_vertex_color);
            tcase_add_test(tc, test_background_color);
            tcase_add_test(tc, test_model);
            suite_add_tcase(s, tc);
        } else {
            free(s);
            s = NULL;
        }
    }

    return (s);
}
