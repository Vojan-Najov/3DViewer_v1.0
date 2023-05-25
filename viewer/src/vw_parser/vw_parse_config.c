#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vw_scene.h"
#include "vw_utils.h"

static int vw_parse_config_line(char *line, vw_scene_t *scene);
static int vw_parse_projection(vw_scene_t *scene, char *line);
static int vw_parse_line_type(vw_scene_t *scene, char *line);
static int vw_parse_vertex_type(vw_scene_t *scene, char *line);
static int vw_parse_line_size(vw_scene_t *scene, char *line);
static int vw_parse_vertex_size(vw_scene_t *scene, char *line);
static int vw_parse_line_color(vw_scene_t *scene, char *line);
static int vw_parse_vertex_color(vw_scene_t *scene, char *line);
static int vw_parse_background_color(vw_scene_t *scene, char *line);

int vw_parse_config(const char *pathname, vw_scene_t *scene) {
    const char *old_locale;
    FILE *stream;
    int line_length = 0;
    char *line = NULL;
    int err_status = 0;

    old_locale = setlocale(LC_ALL, "C");

    stream = fopen(pathname, "r");
    if (stream == NULL) {
        err_status = VW_OPEN_FILE_ERROR;
    } else {
        line_length = vw_get_line(stream, &line);
        while (line_length > 0 && !err_status) {
            if (*line != '\n') {
                err_status = vw_parse_config_line(line, scene);
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

    setlocale(LC_ALL, old_locale);

    return (err_status);
}

static int vw_parse_config_line(char *line, vw_scene_t *scene) {
    char *token;
    int err_status = 0;

    token = strtok(line, " \t");
    line = strtok(NULL, "");

    if (line == NULL) {
        err_status = VW_INCORRECT_LINE;
    } else {
        if (strcmp(token, "projection") == 0) {
            vw_parse_projection(scene, line);
        } else if (strcmp(token, "line_type") == 0) {
            vw_parse_line_type(scene, line);
        } else if (strcmp(token, "vertex_type") == 0) {
            vw_parse_vertex_type(scene, line);
        } else if (strcmp(token, "line_size") == 0) {
            vw_parse_line_size(scene, line);
        } else if (strcmp(token, "vertex_size") == 0) {
            vw_parse_vertex_size(scene, line);
        } else if (strcmp(token, "line_color") == 0) {
            vw_parse_line_color(scene, line);
        } else if (strcmp(token, "vertex_color") == 0) {
            vw_parse_vertex_color(scene, line);
        } else if (strcmp(token, "background_color") == 0) {
            vw_parse_background_color(scene, line);
        } else {
            err_status = VW_INCORRECT_LINE;
        }
    }

    return (err_status);
}

static int vw_parse_projection(vw_scene_t *scene, char *line) {
    int type;
    int err_status = 0;

    type = atoi(line);
    if (type != VW_PARALLEL_PROJECTION && type != VW_CENTRAL_PROJECTION) {
        type = VW_PARALLEL_PROJECTION;
    }
    scene->projection_type = type;

    return (err_status);
}

static int vw_parse_line_type(vw_scene_t *scene, char *line) {
    int type;
    int err_status = 0;

    type = atoi(line);
    if (type != VW_SOLID_LINE && type != VW_DASHED_LINE) {
        type = VW_SOLID_LINE;
    }
    scene->line_type = type;

    return (err_status);
}

static int vw_parse_vertex_type(vw_scene_t *scene, char *line) {
    int type;
    int err_status = 0;

    type = atoi(line);
    if (type != VW_NONE_VERTEX && type != VW_CIRCLE_VERTEX &&
        type != VW_SQUARE_VERTEX) {
        type = VW_NONE_VERTEX;
    }
    scene->vertex_type = type;

    return (err_status);
}

static int vw_parse_line_size(vw_scene_t *scene, char *line) {
    float fnum;
    int err_status = 0;

    fnum = strtof(line, NULL);
    if (fnum <= 0.0f) {
        fnum = 1.0f;
    }
    scene->line_size = fnum;

    return (err_status);
}

static int vw_parse_vertex_size(vw_scene_t *scene, char *line) {
    float fnum;
    int err_status = 0;

    fnum = strtof(line, NULL);
    if (fnum <= 0) {
        fnum = 1;
    }
    scene->vertex_size = fnum;

    return (err_status);
}

static int vw_parse_line_color(vw_scene_t *scene, char *line) {
    float color[3];
    int err_status = 0;

    color[0] = strtof(line, &line);
    color[1] = strtof(line, &line);
    color[2] = strtof(line, &line);
    if (color[0] < 0.0f || color[0] > 1.0f || color[1] < 0.0f ||
        color[1] > 1.0f || color[2] < 0.0f || color[2] > 1.0f) {
        color[0] = color[1] = color[2] = 0.0f;
    }
    memcpy(scene->line_color, color, 3 * sizeof(float));

    return (err_status);
}

static int vw_parse_vertex_color(vw_scene_t *scene, char *line) {
    float color[3];
    int err_status = 0;

    color[0] = strtof(line, &line);
    color[1] = strtof(line, &line);
    color[2] = strtof(line, &line);
    if (color[0] < 0.0f || color[0] > 1.0f || color[1] < 0.0f ||
        color[1] > 1.0f || color[2] < 0.0f || color[2] > 1.0f) {
        color[0] = color[1] = color[2] = 0.0f;
    }
    memcpy(scene->vertex_color, color, 3 * sizeof(float));

    return (err_status);
}

static int vw_parse_background_color(vw_scene_t *scene, char *line) {
    float color[4];
    int err_status = 0;

    color[0] = strtof(line, &line);
    color[1] = strtof(line, &line);
    color[2] = strtof(line, &line);
    color[3] = strtof(line, &line);
    if (color[0] < 0.0f || color[0] > 1.0f || color[1] < 0.0f ||
        color[1] > 1.0f || color[2] < 0.0f || color[2] > 1.0f ||
        color[3] < 0.0f || color[3] > 1.0f) {
        color[0] = color[1] = color[2] = color[3] = 1.0f;
    }
    memcpy(scene->bg_color, color, 4 * sizeof(float));

    return (err_status);
}
