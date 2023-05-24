#ifndef __VIEWER_SCENE_H__
#define __VIEWER_SCENE_H__

#include "vw_model.h"
#include "vw_errors.h"

#ifndef VW_CONF_FILE 
  #define VW_CONF_FILE "./.3DViewer_v1.0_conf"
#endif

#define VW_DEFAULT_SETTINGS 1
#define VW_CONFIG_SETTINGS 2

#define VW_PARALLEL_PROJECTION 1
#define VW_CENTRAL_PROJECTION 2

#define VW_SOLID_LINE 1
#define VW_DASHED_LINE 2

#define VW_NONE_VERTEX 1
#define VW_CIRCLE_VERTEX 2
#define VW_SQUARE_VERTEX 3

typedef struct vw_scene {
	int projection_type;
	int line_type;
	int vertex_type;
	float line_size;
	float vertex_size;
	float line_color[3];
	float vertex_color[3];
	float bg_color[4];
	vw_point_t camera;
	float focal;
	vw_model_t *model;
} vw_scene_t;

int vw_scene_create(void);

void vw_scene_set_default_settings(void);

void vw_scene_clear(void);

int vw_scene_get_projection_type(void);

void vw_scene_set_projection_type(int projection_type);

int vw_scene_get_line_type(void);

void vw_scene_set_line_type(int line_type);

int vw_scene_get_vertex_type(void);

void vw_scene_set_vertex_type(int vertex_type);

float vw_scene_get_line_size(void);

void vw_scene_set_line_size(float size);

float vw_scene_get_vertex_size(void);

void vw_scene_set_vertex_size(float size);

void vw_scene_get_line_color(float *red, float *green, float *blue);

void vw_scene_set_line_color(float red, float green, float blue);

void vw_scene_get_vertex_color(float *red, float *green, float *blue);

void vw_scene_set_vertex_color(float red, float green, float blue);

void vw_scene_get_background_color(float *red, float *green,
                                   float *blue, float *alpha);

void vw_scene_set_background_color(float red, float green, 
                                   float blue, float alpha);

void vw_scene_get_camera(float *x, float *y, float *z);

float vw_scene_get_focal_distance(void);

vw_model_t *vw_scene_get_model(void);

int vw_scene_set_model(const char *pathname);

#endif

