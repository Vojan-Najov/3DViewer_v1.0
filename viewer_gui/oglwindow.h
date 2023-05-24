#ifndef OGLWINDOW_H
#define OGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>

#include "../viewer/include/3Dviewer.h"


class OGLWindow : public QOpenGLWidget//, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    float xRot = 0.0f, yRot = 0.0f;
    QPoint mPos;
public:
    explicit OGLWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent * m);
    void mouseMoveEvent(QMouseEvent * m);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
private:
    int status;

public:
    void pupdate();

signals:

};

#endif // OGLWINDOW_H
