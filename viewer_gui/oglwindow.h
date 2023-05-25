#ifndef OGLWINDOW_H
#define OGLWINDOW_H

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../viewer/include/3Dviewer.h"
#include "gifLib/qgifimage.h"

class OGLWindow : public QOpenGLWidget  //, protected QOpenGLFunctions
{
  Q_OBJECT
 public:
  float xRot, yRot;
  QPoint mPos;

 public:
  explicit OGLWindow(QWidget *parent = nullptr);
  void mousePressEvent(QMouseEvent *m);
  void mouseMoveEvent(QMouseEvent *m);

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 public:
  void pupdate();

 signals:
};

#endif  // OGLWINDOW_H
