#include <check.h>

#include "vw_utils.h"

START_TEST(test_01) {
	FILE *stream;
	char *str1 = "12 3451 12 n\n";
	char *str2 = " sadsask kjasjdksa\n";
	char *str3 = "\n";
	char *str = NULL;
	int str_len;

	stream = fopen("./.tmp.txt", "w");
	if (stream != NULL) {
		fprintf(stream, "%s", str1); 
		fprintf(stream, "%s", str2); 
		fprintf(stream, "%s", str3);
		fclose(stream);
		stream = fopen("./.tmp.txt", "r");
		if (stream != NULL) {
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(str1));
			ck_assert_str_eq(str, str1);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(str2));
			ck_assert_str_eq(str, str2);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(str3));
			ck_assert_str_eq(str, str3);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, 0);
			free(str);
			fclose(stream);
		}
		remove("./.tmp.txt");
	}
}
END_TEST

/*
START_TEST(test_02) {
	FILE *stream;
	char *str1 = "12 3451 12 n\n";
	char *str2 = " sadsask kjasjdksa\n";
	char *str3 = "\n";
	char *str = NULL;
	int str_len;

	stream = fopen("./.tmp.txt", "w");
	if (stream != NULL) {
		fprintf(stream, "%s", str1); 
		fprintf(stream, "%s", str2); 
		fprintf(stream, "%s", str3);
		fclose(stream);
		stream = fopen("./.tmp.txt", "r");
		if (stream != NULL) {
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(str1));
			ck_assert_str_eq(str, str1);
			fclose(stream);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_lt(str_len, 0);
		}
		remove("./.tmp.txt");
	}
}
END_TEST
*/

START_TEST(test_03) {
	FILE *stream;
	int str_len;
	char *str = NULL;
	char buf1[2 * 1024] = "";
	char buf2[2 * 1024] = "";

	stream = fopen("./.tmp.txt", "w");
	if (stream != NULL) {
		for (int i = 0; i < 512; ++i) {
			fputc('a', stream);
			strcat(buf1, "a");
		}
		fputc('\n', stream);
		strcat(buf1, "\n");
		for (int i = 0; i < 1042; ++i) {
			fputc('b', stream);
			strcat(buf2, "b");
		}
		fputc('\n', stream);
		strcat(buf2, "\n");
		fclose(stream);
		stream = fopen("./.tmp.txt", "r");
		if (stream != NULL) {
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(buf1));
			ck_assert_str_eq(str, buf1);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(buf2));
			ck_assert_str_eq(str, buf2);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, 0);
			fclose(stream);
			free(str);
		}
		remove("./.tmp.txt");
	}
}
END_TEST

START_TEST(test_04) {
	FILE *stream;
	int str_len;
	char *str = NULL;
	char buf1[2 * 1024] = "";
	char buf2[2 * 1024] = "";

	stream = fopen("./.tmp.txt", "w");
	if (stream != NULL) {
		for (int i = 0; i < 512; ++i) {
			fputc('a', stream);
			strcat(buf1, "a");
		}
		fputc('\n', stream);
		strcat(buf1, "\n");
		for (int i = 0; i < 1042; ++i) {
			fputc('b', stream);
			strcat(buf2, "b");
		}
		fclose(stream);
		stream = fopen("./.tmp.txt", "r");
		if (stream != NULL) {
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(buf1));
			ck_assert_str_eq(str, buf1);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(buf2));
			ck_assert_str_eq(str, buf2);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, 0);
			fclose(stream);
			free(str);
		}
		remove("./.tmp.txt");
	}
}
END_TEST



START_TEST(test_05) {
	FILE *stream;
	int str_len;
	char *str = NULL;
	char buf[2 * 1024] = "";

	stream = fopen("./.tmp.txt", "w");
	if (stream != NULL) {
		for (int i = 0; i < 512; ++i) {
			fputc('a', stream);
			strcat(buf, "a");
		}
		fclose(stream);
		stream = fopen("./.tmp.txt", "r");
		if (stream != NULL) {
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, (int)strlen(buf));
			ck_assert_str_eq(str, buf);
			str_len = vw_get_line(stream, &str);
			ck_assert_int_eq(str_len, 0);
			fclose(stream);
			free(str);
		}
		remove("./.tmp.txt");
	}
}
END_TEST



Suite *test_vw_get_line(void) {
	Suite *s;
	TCase *tc;

	s = suite_create("vw_get_line");
	if (s != NULL) {
		tc = tcase_create("vw_get_line");
		if (tc != NULL) {
			tcase_add_test(tc, test_01);
			//tcase_add_test(tc, test_02);
			tcase_add_test(tc, test_03);
			tcase_add_test(tc, test_04);
			tcase_add_test(tc, test_05);
			suite_add_tcase(s, tc);
		} else {
			free(s);
			s = NULL;
		}
	}

	return (s);
}

