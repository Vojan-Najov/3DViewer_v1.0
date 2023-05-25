#include "vw_scene.h"

#include <stdio.h>
#include <stdlib.h>

#include "vw_parser.h"

static int vw_scene_save_settings(void);

static vw_scene_t *vw_scene_ptr(void) {
    static vw_scene_t sc;

    return (&sc);
}

void vw_scene_set_default_settings(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();

    scene->projection_type = VW_PARALLEL_PROJECTION;
    scene->line_type = VW_SOLID_LINE;
    scene->vertex_type = VW_NONE_VERTEX;
    scene->line_size = 1.0f;
    scene->vertex_size = 1.0f;
    scene->line_color[0] = 0.0f;
    scene->line_color[1] = 0.0f;
    scene->line_color[2] = 0.0f;
    scene->vertex_color[0] = 0.0f;
    scene->vertex_color[1] = 0.0f;
    scene->vertex_color[2] = 0.0f;
    scene->bg_color[0] = 1.0f;
    scene->bg_color[1] = 1.0f;
    scene->bg_color[2] = 1.0f;
    scene->bg_color[3] = 1.0f;
    scene->camera[0] = 0.0f;
    scene->camera[1] = 0.0f;
    scene->camera[2] = 0.0f;
    scene->camera[3] = 0.0f;
    scene->model = NULL;
}

/*
  if there is a settings file,
  then the initial settings are taken from there.
  otherwise default settings.
*/
int vw_scene_create(void) {
    int err_status;
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    vw_scene_set_default_settings();
    err_status = vw_parse_config(VW_CONF_FILE, scene);
    if (err_status) {
        vw_scene_set_default_settings();
    }

    return (err_status ? VW_DEFAULT_SETTINGS : VW_CONFIG_SETTINGS);
}

void vw_scene_clear(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();

    if (scene->model != NULL) {
        vw_model_clear(scene->model);
        free(scene->model);
    }
    vw_scene_save_settings();
    vw_scene_set_default_settings();
}

int vw_scene_get_projection_type(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->projection_type);
}

void vw_scene_set_projection_type(int projection_type) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->projection_type = projection_type;
}

int vw_scene_get_line_type(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->line_type);
}

void vw_scene_set_line_type(int line_type) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->line_type = line_type;
}

int vw_scene_get_vertex_type(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->vertex_type);
}

void vw_scene_set_vertex_type(int vertex_type) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->vertex_type = vertex_type;
}

float vw_scene_get_line_size(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->line_size);
}

void vw_scene_set_line_size(float size) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->line_size = size;
}

float vw_scene_get_vertex_size(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->vertex_size);
}

void vw_scene_set_vertex_size(float size) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->vertex_size = size;
}

void vw_scene_get_line_color(float *red, float *green, float *blue) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    *red = scene->line_color[0];
    *green = scene->line_color[1];
    *blue = scene->line_color[2];
}

void vw_scene_set_line_color(float red, float green, float blue) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->line_color[0] = red;
    scene->line_color[1] = green;
    scene->line_color[2] = blue;
}

void vw_scene_get_vertex_color(float *red, float *green, float *blue) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    *red = scene->vertex_color[0];
    *green = scene->vertex_color[1];
    *blue = scene->vertex_color[2];
}

void vw_scene_set_vertex_color(float red, float green, float blue) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->vertex_color[0] = red;
    scene->vertex_color[1] = green;
    scene->vertex_color[2] = blue;
}

void vw_scene_get_background_color(float *red, float *green, float *blue,
                                   float *alpha) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    *red = scene->bg_color[0];
    *green = scene->bg_color[1];
    *blue = scene->bg_color[2];
    *alpha = scene->bg_color[3];
}

void vw_scene_set_background_color(float red, float green, float blue,
                                   float alpha) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    scene->bg_color[0] = red;
    scene->bg_color[1] = green;
    scene->bg_color[2] = blue;
    scene->bg_color[3] = alpha;
}

void vw_scene_get_camera(float *x, float *y, float *z) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    *x = scene->camera[0];
    *y = scene->camera[1];
    *z = scene->camera[2];
}

float vw_scene_get_focal_distance(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->focal);
}

vw_model_t *vw_scene_get_model(void) {
    vw_scene_t *scene;

    scene = vw_scene_ptr();
    return (scene->model);
}

int vw_scene_set_model(const char *pathname) {
    vw_scene_t *scene;
    vw_model_t *model;
    int err_status = 0;

    scene = vw_scene_ptr();
    model = scene->model;

    if (model != NULL) {
        vw_model_clear(model);
    } else {
        model = (vw_model_t *)malloc(sizeof(vw_model_t));
    }

    if (model != NULL) {
        err_status = vw_parse_objfile_to_model(pathname, model);
        if (!err_status) {
            scene->model = model;
            vw_model_calculate_dimension(model);
            scene->camera[0] = model->centre[0];
            scene->camera[1] = model->centre[1];
            scene->camera[2] = model->centre[2] + 2.0f * model->dim;
            scene->focal = model->dim > 1.0e-6f ? model->dim / 10.0f : 1.0;
        } else {
            free(model);
            scene->model = NULL;
        }
    } else {
        err_status = VW_ALLOC_ERROR;
    }

    return (err_status);
}

static int vw_scene_save_settings(void) {
    vw_scene_t *scene;
    FILE *stream;
    int err_status = 0;

    scene = vw_scene_ptr();
    stream = fopen(VW_CONF_FILE, "w");
    if (stream != NULL) {
        fprintf(stream, "projection %d\n", scene->projection_type);
        fprintf(stream, "line_type %d\n", scene->line_type);
        fprintf(stream, "vertex_type %d\n", scene->vertex_type);
        fprintf(stream, "line_size %f\n", scene->line_size);
        fprintf(stream, "vertex_size %f\n", scene->vertex_size);
        fprintf(stream, "line_color %f %f %f\n", scene->line_color[0],
                scene->line_color[1], scene->line_color[2]);
        fprintf(stream, "vertex_color %f %f %f\n", scene->vertex_color[0],
                scene->vertex_color[1], scene->vertex_color[2]);
        fprintf(stream, "background_color %f %f %f %f\n", scene->bg_color[0],
                scene->bg_color[1], scene->bg_color[2], scene->bg_color[3]);
        if (ferror(stream)) {
            err_status = VW_WRITE_FILE_ERROR;
        }
        if (fclose(stream) != 0) {
            err_status = VW_CLOSE_FILE_ERROR;
        }
    } else {
        err_status = VW_OPEN_FILE_ERROR;
    }

    return (err_status);
}
