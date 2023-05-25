#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vw_model.h"
#include "vw_parser.h"
#include "vw_utils.h"

static int vw_parse_line_to_model(char *line, vw_model_t *model);

int vw_parse_objfile_to_model(const char *pathname, vw_model_t *model) {
    const char *old_locale;
    FILE *stream;
    int line_length = 0;
    char *line = NULL;
    int err_status = 0;

    old_locale = setlocale(LC_ALL, "C");

    memset((void *)model, 0, sizeof(vw_model_t));

    stream = fopen(pathname, "r");
    if (stream == NULL) {
        err_status = VW_OPEN_FILE_ERROR;
    } else {
        line_length = vw_get_line(stream, &line);
        while (line_length > 0 && !err_status) {
            if (*line != '\n' && *line != '#') {
                err_status = vw_parse_line_to_model(line, model);
            }
            line_length = vw_get_line(stream, &line);
        }
    }

    if (stream != NULL) {
        if (fclose(stream) != 0) {
            err_status = VW_CLOSE_FILE_ERROR;
        }
    }
    if (line_length == -1) {
        err_status = VW_READ_FILE_ERROR;
    }

    free(line);
    if (!err_status) {
        err_status = vw_reduce_vertex_array(model);
    }
    if (!err_status) {
        err_status = vw_reduce_face_array(model);
    }
    if (err_status) {
        vw_model_clear(model);
    }

    setlocale(LC_ALL, old_locale);

    return (err_status);
}

static int vw_parse_line_to_model(char *line, vw_model_t *model) {
    char *token;
    int err_status = 0;

    token = strtok(line, " \t");
    line = strtok(NULL, "");

    if (line == NULL) {
        err_status = VW_INCORRECT_LINE;
    } else {
        if (strcmp(token, "v") == 0) {
            err_status = vw_parse_vertex(line, model);
        } else if (strcmp(token, "f") == 0) {
            err_status = vw_parse_face(line, model);
        } else if (strcmp(token, "vt") && strcmp(token, "vn") &&
                   strcmp(token, "vp") && strcmp(token, "l") &&
                   strcmp(token, "g") && strcmp(token, "o") &&
                   strcmp(token, "s") && strcmp(token, "mtllib") &&
                   strcmp(token, "usemtl")) {
            err_status = VW_INCORRECT_LINE;
        }
    }

    return (err_status);
}
