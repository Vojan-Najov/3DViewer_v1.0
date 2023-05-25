#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "ui_mainwindow.h"

#define UI_VW_SOLID_LINE (VW_SOLID_LINE - 1)
#define UI_VW_DASHED_LINE (VW_DASHED_LINE - 1)
#define UI_VW_PARALLEL_PROJECTION (VW_PARALLEL_PROJECTION - 1)
#define UI_VW_CENTRAL_PROJECTION (VW_CENTRAL_PROJECTION - 1)

#define DIMENSION 2

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  vw_scene_create();
  ui->setupUi(this);
  movie = nullptr;
  ui->XvalueForRotate->setMinimum(-999999.99);
  ui->YvalueForRotate->setMinimum(-999999.99);
  ui->ZvalueForRotate->setMinimum(-999999.99);
  ui->XvalueForRotate->setMaximum(999999.99);
  ui->YvalueForRotate->setMaximum(999999.99);
  ui->ZvalueForRotate->setMaximum(999999.99);
  ui->XvalueForTranslate->setMinimum(-999999.99);
  ui->YvalueForTranslate->setMinimum(-999999.99);
  ui->ZvalueForTranslate->setMinimum(-999999.99);
  ui->XvalueForTranslate->setMaximum(999999.99);
  ui->YvalueForTranslate->setMaximum(999999.99);
  ui->ZvalueForTranslate->setMaximum(999999.99);
  ui->Scalevalue->setMinimum(0.01);
  ui->Scalevalue->setMaximum(999999.99);
  ui->LineSlider->setMaximum(14);
  connect(ui->plusButtonScale, &QPushButton::clicked, this,
          &MainWindow::positiveScale);
  connect(ui->minusButtonScale, &QPushButton::clicked, this,
          &MainWindow::negativeScale);
  connect(ui->plusButtonXTranslate, &QPushButton::clicked, this,
          &MainWindow::positiveTranslateForX);
  connect(ui->minusButtonXTranslate, &QPushButton::clicked, this,
          &MainWindow::negativeTranslateForX);
  connect(ui->plusButtonYTranslate, &QPushButton::clicked, this,
          &MainWindow::positiveTranslateForY);
  connect(ui->minusButtonYTranslate, &QPushButton::clicked, this,
          &MainWindow::negativeTranslateForY);
  connect(ui->plusButtonZTranslate, &QPushButton::clicked, this,
          &MainWindow::positiveTranslateForZ);
  connect(ui->minusButtonZTranslate, &QPushButton::clicked, this,
          &MainWindow::negativeTranslateForZ);
  connect(ui->plusButtonXRotate, &QPushButton::clicked, this,
          &MainWindow::positiveRotateForX);
  connect(ui->minusButtonXRotate, &QPushButton::clicked, this,
          &MainWindow::negativeRotateForX);
  connect(ui->plusButtonYRotate, &QPushButton::clicked, this,
          &MainWindow::positiveRotateForY);
  connect(ui->minusButtonYRotate, &QPushButton::clicked, this,
          &MainWindow::negativeRotateForY);
  connect(ui->plusButtonZRotate, &QPushButton::clicked, this,
          &MainWindow::positiveRotateForZ);
  connect(ui->minusButtonZRotate, &QPushButton::clicked, this,
          &MainWindow::negativeRotateForZ);
  connect(ui->colorBackgroundButton, &QPushButton::clicked, this,
          &MainWindow::chooseColorBackground);
  connect(ui->colorFaceButton, &QPushButton::clicked, this,
          &MainWindow::chooseColorLine);
  connect(ui->colorVertexButton, &QPushButton::clicked, this,
          &MainWindow::chooseColorVertex);
}

void MainWindow::initializeCustomization() {
  ui->projectionTypeBox->setCurrentIndex(vw_scene_get_projection_type() - 1);
  ui->lineTypeBox->setCurrentIndex(vw_scene_get_line_type() - 1);
  ui->vertexTypeBox->setCurrentIndex(vw_scene_get_vertex_type() - 1);
  ui->LineSlider->setValue(vw_scene_get_line_size());
  ui->VertexSlider->setValue(vw_scene_get_vertex_size());
}

void MainWindow::initializeTransmitions() {
  ui->XvalueForRotate->setValue(0);
  ui->YvalueForRotate->setValue(0);
  ui->ZvalueForRotate->setValue(0);
  ui->XvalueForTranslate->setValue(0);
  ui->YvalueForTranslate->setValue(0);
  ui->ZvalueForTranslate->setValue(0);
  ui->Scalevalue->setValue(1.0);
}

MainWindow::~MainWindow() {
  vw_scene_clear();
  delete ui;
}

double calculateMove(double value, double prevValue) {
  double result;
  if (value > prevValue) {
    result = fabs(value - prevValue);
  } else {
    result = -fabs(value - prevValue);
  }
  return result;
}

double caclculateScale(double prevScale, double scale) {
  return scale / prevScale;
}

void MainWindow::setLineType() {
  if (vw_scene_get_line_type() == VW_SOLID_LINE)
    ui->lineTypeBox->setCurrentIndex(UI_VW_SOLID_LINE);
  else
    ui->lineTypeBox->setCurrentIndex(UI_VW_DASHED_LINE);
}

void MainWindow::setProjectionType() {
  if (vw_scene_get_projection_type() == VW_PARALLEL_PROJECTION)
    ui->lineTypeBox->setCurrentIndex(UI_VW_PARALLEL_PROJECTION);
  else
    ui->lineTypeBox->setCurrentIndex(UI_VW_CENTRAL_PROJECTION);
}

void MainWindow::on_action_triggered() {
  QString file_name =
      QFileDialog ::getOpenFileName(NULL, "Title", "../..", "*.obj");
  if (file_name != "") {
    initializeTransmitions();
    initializeCustomization();
    if (!vw_scene_set_model(file_name.toStdString().c_str())) {
      vw_model_t *model = vw_scene_get_model();
      unsigned number_of_faces = 0;
      for (unsigned i = 0; i < model->number_of_faces; i++) {
        number_of_faces += model->faces[i].number_of_idx;
      }
      ui->PolygonsCount->setText(QString::number(model->number_of_faces));
      ui->EdgesCount->setText(QString::number(number_of_faces));
      ui->VertexCount->setText(QString::number(model->number_of_vertices));
      QStringList parts = file_name.split("/");
      QString lastBit = parts.at(parts.size() - 1);
      ui->Filename->setText(lastBit);
      updateScene();
    } else {
      QMessageBox::information(0, "ERROR", "Parse Error");
    }
  } else {
  }
}

void MainWindow::on_action_2_triggered() {
  QString file_name =
      QFileDialog ::getSaveFileName(NULL, "Title", ".", "*.obj *.bmp *.jpeg");
  if (file_name != "") {
    if (file_name.toStdString().substr(
            file_name.toStdString().find_last_of(".") + 1) == "bmp") {
      ui->widget->grab().save(file_name);
    } else if (file_name.toStdString().substr(
                   file_name.toStdString().find_last_of(".") + 1) == "jpeg") {
      ui->widget->grab().save(file_name);
    } else {
      vw_save_model_to_objfile(file_name.toStdString().c_str(),
                               vw_scene_get_model());
    }
  }
}

void MainWindow::chooseColorLine() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    vw_scene_set_line_color(color.redF(), color.greenF(), color.blueF());
    updateScene();
  }
}

void MainWindow::chooseColorVertex() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    vw_scene_set_vertex_color(color.redF(), color.greenF(), color.blueF());
    updateScene();
  }
}

void MainWindow::positiveScale() {
  if (vw_scene_get_model()) {
    ui->Scalevalue->setValue(ui->Scalevalue->value() + 0.15f);
  }
}

void MainWindow::negativeScale() {
  if (vw_scene_get_model()) {
    ui->Scalevalue->setValue(ui->Scalevalue->value() - 0.15f);
  }
}

void MainWindow::positiveTranslateForX() {
  if (vw_scene_get_model()) {
    ui->XvalueForTranslate->setValue(ui->XvalueForTranslate->value() +
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeTranslateForX() {
  if (vw_scene_get_model()) {
    ui->XvalueForTranslate->setValue(ui->XvalueForTranslate->value() -
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::positiveTranslateForY() {
  if (vw_scene_get_model()) {
    ui->YvalueForTranslate->setValue(ui->YvalueForTranslate->value() +
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeTranslateForY() {
  if (vw_scene_get_model()) {
    ui->YvalueForTranslate->setValue(ui->YvalueForTranslate->value() -
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::positiveTranslateForZ() {
  if (vw_scene_get_model()) {
    ui->ZvalueForTranslate->setValue(ui->ZvalueForTranslate->value() +
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeTranslateForZ() {
  if (vw_scene_get_model()) {
    ui->ZvalueForTranslate->setValue(ui->ZvalueForTranslate->value() -
                                     vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeRotateForX() {
  if (vw_scene_get_model()) {
    ui->XvalueForRotate->setValue(ui->XvalueForRotate->value() -
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::positiveRotateForX() {
  if (vw_scene_get_model()) {
    ui->XvalueForRotate->setValue(ui->XvalueForRotate->value() +
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeRotateForY() {
  if (vw_scene_get_model()) {
    ui->YvalueForRotate->setValue(ui->YvalueForRotate->value() -
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::positiveRotateForY() {
  if (vw_scene_get_model()) {
    ui->YvalueForRotate->setValue(ui->YvalueForRotate->value() +
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::negativeRotateForZ() {
  if (vw_scene_get_model()) {
    ui->ZvalueForRotate->setValue(ui->ZvalueForRotate->value() -
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::positiveRotateForZ() {
  if (vw_scene_get_model()) {
    ui->ZvalueForRotate->setValue(ui->ZvalueForRotate->value() +
                                  vw_scene_get_model()->dim / DIMENSION);
  }
}

void MainWindow::chooseColorBackground() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    vw_scene_set_background_color(color.redF(), color.greenF(), color.blueF(),
                                  1);
    updateScene();
  }
}

void MainWindow::on_XvalueForTranslate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(MOVE_XYZ, move, 0, 0);
  updateScene();
}

void MainWindow::on_YvalueForTranslate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(MOVE_XYZ, 0, move, 0);
  updateScene();
}

void MainWindow::on_ZvalueForTranslate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(MOVE_XYZ, 0, 0, move);
  updateScene();
}

void MainWindow::on_XvalueForRotate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(SPIN_YZ, move, 0, 0);
  updateScene();
}

void MainWindow::on_YvalueForRotate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(SPIN_XZ, move, 0, 0);
  updateScene();
}

void MainWindow::on_ZvalueForRotate_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  vw_move(SPIN_XY, move, 0, 0);
  updateScene();
}

void MainWindow::on_Scalevalue_valueChanged(double arg1) {
  if (!vw_scene_get_model()) return;
  static double prevValue = 1.0;
  double scale = caclculateScale(prevValue, arg1);
  prevValue = arg1;
  vw_move(SCALE_XYZ, scale, scale, scale);
  updateScene();
}

void MainWindow::on_lineTypeBox_currentTextChanged(const QString &arg1) {
  if (arg1 == "Solid")
    vw_scene_set_line_type(VW_SOLID_LINE);
  else
    vw_scene_set_line_type(VW_DASHED_LINE);
  updateScene();
}

void MainWindow::on_vertexTypeBox_currentTextChanged(const QString &arg1) {
  if (arg1 == "Circle")
    vw_scene_set_vertex_type(VW_CIRCLE_VERTEX);
  else if (arg1 == "Square")
    vw_scene_set_vertex_type(VW_SQUARE_VERTEX);
  else
    vw_scene_set_vertex_type(VW_NONE_VERTEX);
  updateScene();
}

void MainWindow::on_projectionTypeBox_currentTextChanged(const QString &arg1) {
  if (arg1 == "Parallel")
    vw_scene_set_projection_type(VW_PARALLEL_PROJECTION);
  else
    vw_scene_set_projection_type(VW_CENTRAL_PROJECTION);
  updateScene();
}

void MainWindow::on_LineSlider_valueChanged(int value) {
  vw_scene_set_line_size(value);
  updateScene();
}

void MainWindow::on_VertexSlider_valueChanged(int value) {
  vw_scene_set_vertex_size(value);
  updateScene();
}

void MainWindow::on_makeGifButton_clicked() {
  if (movie) {
    QMessageBox::information(0, "ERROR", "Gif is recording");
    return;
  }
  movie = new QGifImage;
  movie->setDefaultDelay(100);
}

void MainWindow::on_setFrameButton_clicked() {
  if (!movie) {
    QMessageBox::information(0, "ERROR", "Gif is not recording");
    return;
  }

  ui->curFrame->setText(QString::number(ui->curFrame->text().toInt() + 1));
  if (movie && ui->curFrame->text().toInt() < 50) {
    movie->addFrame(ui->widget->grab().toImage());
  } else if (movie && ui->curFrame->text().toInt() == 50) {
    movie->addFrame(ui->widget->grab().toImage());
    QString file_name =
        QFileDialog ::getSaveFileName(NULL, "Title", "../..", "*.gif");
    if (file_name != "") movie->save(file_name);
    ui->curFrame->setText(QString::number(0));
    delete movie;
    movie = nullptr;
  }
}

void MainWindow::on_cancelGifButton_clicked() {
  if (movie) delete movie;
  movie = nullptr;
  ui->curFrame->setText(QString::number(0));
}

void MainWindow::updateScene() {
  ui->widget->pupdate();
  if (movie) on_setFrameButton_clicked();
}
