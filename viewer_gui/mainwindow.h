#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gifLib/qgifimage.h"
#include "oglwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_action_triggered();

  void on_action_2_triggered();

  void chooseColorLine();

  void initializeCustomization();

  void chooseColorVertex();

  void chooseColorBackground();

  void positiveScale();

  void negativeScale();

  void positiveTranslateForX();

  void negativeTranslateForX();

  void positiveTranslateForY();

  void negativeTranslateForY();

  void positiveTranslateForZ();

  void negativeTranslateForZ();

  void negativeRotateForX();

  void positiveRotateForX();

  void positiveRotateForY();

  void positiveRotateForZ();

  void negativeRotateForY();

  void negativeRotateForZ();

  void setLineType();

  void setProjectionType();

  void initializeTransmitions();

  void on_XvalueForTranslate_valueChanged(double arg1);

  void on_YvalueForTranslate_valueChanged(double arg1);

  void on_ZvalueForTranslate_valueChanged(double arg1);

  void on_XvalueForRotate_valueChanged(double arg1);

  void on_YvalueForRotate_valueChanged(double arg1);

  void on_ZvalueForRotate_valueChanged(double arg1);

  void on_Scalevalue_valueChanged(double arg1);

  void on_lineTypeBox_currentTextChanged(const QString &arg1);

  void on_vertexTypeBox_currentTextChanged(const QString &arg1);

  void on_projectionTypeBox_currentTextChanged(const QString &arg1);

  void on_LineSlider_valueChanged(int value);

  void on_VertexSlider_valueChanged(int value);

  void on_makeGifButton_clicked();

  void on_setFrameButton_clicked();

  void on_cancelGifButton_clicked();

  void updateScene();

 private:
  Ui::MainWindow *ui;
  QGifImage *movie;
};
#endif  // MAINWINDOW_H
