#include <vw_utils.h>

/*
  The function reads the file character by character up to the newline character and
  returns the current line of the file as a c-string. The newline character is
  contained in the c-string if it has been read. The first time this function is
  called, the pointer to the string must be a NULL. Subsequent calls have as the
  address of the string, the one that the function returned last time. After the file
  is read, the line should be freeded.
  The string length is returned if the reading is successful, 0 if the file is
  finished and -1 if a reading error occurred.
*/

int vw_get_line(FILE *stream, char **line) {
	static size_t size = 256;
	char c = 0;
	int len = 0;

	if (*line == NULL) {
		*line = (char *) malloc(sizeof(char) * size);
	}

	c = fgetc(stream);
	while (*line != NULL && c != EOF && c != '\n') {
		if ((size_t)len >= size - 2) {
			size *= 2;
			*line = realloc(*line, size);
		}
		if (*line != NULL) {
			(*line)[len] = c;
			++len;
		}
		c = fgetc(stream);
	}
	if (c == '\n') {
		(*line)[len] = '\n';
		++len;
	}

	if (*line == NULL || ferror(stream)) {
		len = -1;
	} else {
		(*line)[len] = '\0';
	}

	return (len);
}

