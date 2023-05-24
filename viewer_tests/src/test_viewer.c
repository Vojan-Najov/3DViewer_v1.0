#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "test_viewer.h"

static int run_test_suite(Suite *test_suite) {
	int number_failed = 0;
	SRunner *sr;

	sr = srunner_create(test_suite);
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed);
}

int main(void) {
	size_t i;
	int number_failed = 0;
	Suite *suite_array[] = {
		test_vw_scene(),
		test_vw_model(),
		test_vw_get_line(),
		test_vw_parse_vertex(),
		test_vw_parse_face(),
		test_vw_parse_objfile_to_model(),
		test_vw_parse_config(),
		test_affine(),
		NULL
	};

	if (number_failed != 1) {
		for (i = 0; suite_array[i] != NULL; ++i) {
			number_failed += run_test_suite(suite_array[i]);
		}
	}

	return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
