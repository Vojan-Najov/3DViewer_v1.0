#include "oglwindow.h"

#include <math.h>

OGLWindow::OGLWindow(QWidget *parent) : QOpenGLWidget{parent} {
  xRot = 0.0f;
  yRot = 0.0f;
}

void OGLWindow::mousePressEvent(QMouseEvent *m) { mPos = m->pos(); }

void OGLWindow::mouseMoveEvent(QMouseEvent *m) {
  // xRot += 1 / M_PI * (m->pos().y() - mPos.y());
  // yRot += 1 / M_PI * (m->pos().x() - mPos.x());
  // vw_move(SPIN_XZ, yRot, 0, 0);
  // vw_move(SPIN_YZ, xRot, 0, 0);
  xRot += (m->pos().y() - mPos.y()) / M_PI;
  yRot += (m->pos().x() - mPos.x()) / M_PI;
  xRot = fmodf(xRot, 360.0f);
  yRot = fmodf(yRot, 360.0f);
  mPos = m->pos();

  update();
}

void OGLWindow::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
}

static void set_view_matrix(float xRot, float yRot) {
  vw_model_t *model;
  vw_point_t camera;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  vw_scene_get_camera(&camera[0], &camera[1], &camera[2]);
  model = vw_scene_get_model();
  if (model != NULL) {
    glTranslatef(-camera[0], -camera[1], -camera[2]);
    glTranslatef(model->centre[0], model->centre[1], model->centre[2]);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(-model->centre[0], -model->centre[1], -model->centre[2]);
  }
}

static void set_projection_matrix(int width, int height) {
  vw_model_t *model;
  vw_point_t camera;
  int projection_type;
  float focal_ro, ro, near, far;
  float x_aspect, y_aspect;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  x_aspect = width > height ? (float)width / (float)height : 1.0;
  y_aspect = height > width ? (float)height / (float)width : 1.0;

  vw_scene_get_camera(&camera[0], &camera[1], &camera[2]);
  model = vw_scene_get_model();
  if (model != NULL) {
    ro = model->centre[2] - camera[2];
    projection_type = vw_scene_get_projection_type();
    focal_ro = vw_scene_get_focal_distance();
    if (projection_type == VW_PARALLEL_PROJECTION) {
      near = focal_ro;
      far = -ro + model->dim > near ? -ro + model->dim : 2.0f * near;
      ro = ro < 0.0f ? -ro : focal_ro;

      glOrtho(-ro * x_aspect, ro * x_aspect, -ro * y_aspect, ro * y_aspect,
              near, 10000000);
    } else if (projection_type == VW_CENTRAL_PROJECTION) {
      near = focal_ro;
      far = ro < 0.0f ? -ro + model->dim : model->dim;
      glFrustum(-focal_ro * x_aspect, focal_ro * x_aspect, -focal_ro * y_aspect,
                focal_ro * y_aspect, near, far);
    }
  }
}

static void draw_faces(vw_model_t *model) {
  float size, ro;
  vw_point_t centre;
  float color[4];

  vw_scene_get_line_color(&color[0], &color[1], &color[2]);
  glColor3f(color[0], color[1], color[2]);
  size = vw_scene_get_line_size();
  vw_scene_get_camera(&centre[0], &centre[1], &centre[2]);
  ro = sqrtf(powf(model->centre[0] - centre[0], 2.0) +
             powf(model->centre[1] - centre[1], 2.0) +
             powf(model->centre[2] - centre[2], 2.0));
  ro = ro < 2.0f * model->dim ? 2.0f * model->dim : ro;
  glLineWidth(1.0f + size * 2.0f * model->dim / ro);
  glEnable(GL_LINE_SMOOTH);
  if (vw_scene_get_line_type() == VW_DASHED_LINE) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  for (size_t i = 0; i < model->number_of_faces; ++i) {
    glDrawElements(GL_LINE_LOOP, model->faces[i].number_of_idx, GL_UNSIGNED_INT,
                   model->faces[i].idx);
  }
}

static void draw_vertices(vw_model_t *model) {
  float size, ro;
  vw_point_t centre;
  float color[4];
  int vertex_type;

  vertex_type = vw_scene_get_vertex_type();
  if (vertex_type != VW_NONE_VERTEX) {
    vw_scene_get_vertex_color(&color[0], &color[1], &color[2]);
    glColor3f(color[0], color[1], color[2]);
    vw_scene_get_camera(&centre[0], &centre[1], &centre[2]);
    ro = sqrtf(powf(model->centre[0] - centre[0], 2.0) +
               powf(model->centre[1] - centre[1], 2.0) +
               powf(model->centre[2] - centre[2], 2.0));
    ro = ro < 2.0f * model->dim ? 2.0f * model->dim : ro;
    size = vw_scene_get_vertex_size();
    glPointSize(1.0f + size * model->dim / ro);
    if (vertex_type == VW_CIRCLE_VERTEX) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, (GLint)0, (GLsizei)model->number_of_vertices);
  }
}

void OGLWindow::paintGL() {
  float color[4];
  vw_model_t *model;

  vw_scene_get_background_color(&color[0], &color[1], &color[2], &color[3]);

  glClearColor((GLfloat)color[0], (GLfloat)color[1], (GLfloat)color[2],
               (GLfloat)color[3]);
  glClearDepth((GLdouble)1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  model = vw_scene_get_model();
  if (model != NULL) {
    glLoadIdentity();
    glVertexPointer(4, GL_FLOAT, 0, model->vertices);
    set_view_matrix(xRot, yRot);
    set_projection_matrix(width(), height());
    draw_faces(model);
    draw_vertices(model);
  }
  glFlush();
}

void OGLWindow::resizeGL(int w, int h) {
  // setFixedWidth(h-100);
  glViewport(0, 0, w, h);
  update();
}

void OGLWindow::pupdate() { update(); }
