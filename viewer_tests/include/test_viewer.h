#ifndef __TEST_VIEWER_H__
#define __TEST_VIEWER_H__

#include <check.h>

#include "vw_scene.h"
#include "vw_affine.h"
#include "vw_model.h"

Suite *test_vw_scene(void);
Suite *test_vw_model(void);
Suite *test_vw_get_line(void);
Suite *test_vw_parse_vertex(void);
Suite *test_vw_parse_face(void);
Suite *test_vw_parse_objfile_to_model(void);
Suite *test_vw_parse_config(void);
Suite *test_affine(void);

#endif
