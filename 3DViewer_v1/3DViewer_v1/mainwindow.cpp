#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Background_R, SIGNAL(clicked()), this,
          SLOT(on_Background_R_clicked()));
  connect(ui->Background_G, SIGNAL(clicked()), this,
          SLOT(on_Background_G_clicked()));
  connect(ui->Background_B, SIGNAL(clicked()), this,
          SLOT(on_Background_B_clicked()));
  connect(ui->Background_C, SIGNAL(clicked()), this,
          SLOT(on_Background_C_clicked()));

  connect(ui->Point_R, SIGNAL(clicked()), this, SLOT(on_Point_R_clicked()));
  connect(ui->Point_G, SIGNAL(clicked()), this, SLOT(on_Point_G_clicked()));
  connect(ui->Point_B, SIGNAL(clicked()), this, SLOT(on_Point_B_clicked()));
  connect(ui->Point_C, SIGNAL(clicked()), this, SLOT(on_Point_C_clicked()));

  connect(ui->Lines_R, SIGNAL(clicked()), this, SLOT(on_Lines_R_clicked()));
  connect(ui->Lines_G, SIGNAL(clicked()), this, SLOT(on_Lines_G_clicked()));
  connect(ui->Lines_B, SIGNAL(clicked()), this, SLOT(on_Lines_B_clicked()));
  connect(ui->Lines_C, SIGNAL(clicked()), this, SLOT(on_Lines_C_clicked()));

  connect(ui->Move_C, SIGNAL(clicked()), this, SLOT(on_Move_C_clicked()));
  connect(ui->Rotate_C, SIGNAL(clicked()), this, SLOT(on_Rotate_C_clicked()));
}

MainWindow::~MainWindow() {
  ui->widget->free_object();
  delete ui;
}

void MainWindow::on_OpenFile_clicked() {
  ui->FileName->clear();
  filename = QFileDialog::getOpenFileName(
      this, tr("Load Object"), "/home/enedinae/Рабочий стол/obj", tr("*.obj"));
  ui->FileName->setText(filename);
  ui->widget->init_obj(filename);
  ui->Vertexes_Num->setText(QString::number(ui->widget->obj.vertexes_num));
  ui->Facets_Num->setText(QString::number(ui->widget->obj.facets_num / 2));
  clean_param();
  ui->widget->update();
}

void MainWindow::clean_param() {
  ui->widget->Lines_R = 1;
  ui->widget->Lines_G = 1;
  ui->widget->Lines_B = 1;

  ui->widget->Point_R = 1;
  ui->widget->Point_G = 1;
  ui->widget->Point_B = 1;

  ui->widget->Background_R = 0;
  ui->widget->Background_G = 0;
  ui->widget->Background_B = 0;

  ui->SizeSlider->setSliderPosition(50);
  size_slider_state = 50;

  ui->moveX->setText("0");
  ui->moveY->setText("0");
  ui->moveZ->setText("0");

  ui->rotX->setText("0");
  ui->rotY->setText("0");
  ui->rotZ->setText("0");

  ui->widget->Line_Box_Value = 0;
  ui->widget->Point_Box_Value = 0;

  ui->Spin_P->setValue(1);
  ui->Spin_L->setValue(1);
  spin = 1;

  ui->SizeSlider->setSliderPosition(50);
  ui->Line_Box->setCurrentIndex(0);

  size_slider_state = 50;
  ui->RadProjection->setChecked(false);

  ui->widget->update();
}

void MainWindow::on_Clean_clicked() {
  if (!(ui->widget->obj.vertexes_num == 0)) {
    clean_param();

    ui->Vertexes_Num->clear();
    ui->Facets_Num->clear();
    ui->FileName->clear();
    ui->widget->checkCollor = 0;
    ui->widget->free_object();
    ui->widget->update();
  }
  if (ui->widget->checkCollor == 1) {
    ui->widget->checkCollor = 0;
    clean_param();
    ui->widget->update();
  }
}

void MainWindow::on_SizeSlider_valueChanged(int value) {
  MainWindow::on_SizeSlider_sliderMoved(value);
}

void MainWindow::on_SizeSlider_sliderMoved(int position) {
  float f = position - size_slider_state;
  scale_obj(&ui->widget->obj.vert_array, 1.0 + (f / 10),
            ui->widget->obj.vertexes_num);
  ui->widget->update();
  size_slider_state = position;
}

void MainWindow::on_Lines_R_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Lines_R = 1;
  ui->widget->Lines_G = 0;
  ui->widget->Lines_B = 0;
  ui->widget->update();
}
void MainWindow::on_Lines_G_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Lines_R = 0;
  ui->widget->Lines_G = 1;
  ui->widget->Lines_B = 0;
  ui->widget->update();
}
void MainWindow::on_Lines_B_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Lines_R = 0;
  ui->widget->Lines_G = 0;
  ui->widget->Lines_B = 1;
  ui->widget->update();
}
void MainWindow::on_Lines_C_clicked() {
  ui->widget->Lines_R = 1;
  ui->widget->Lines_G = 1;
  ui->widget->Lines_B = 1;
  ui->widget->s_l = 1;
  ui->widget->Line_Box_Value = 0;
  ui->Line_Box->setCurrentIndex(0);
  ui->Spin_L->setValue(1);
  ui->widget->update();
}

void MainWindow::on_Point_R_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Point_R = 1;
  ui->widget->Point_G = 0;
  ui->widget->Point_B = 0;
  ui->widget->update();
}
void MainWindow::on_Point_G_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Point_R = 0;
  ui->widget->Point_G = 1;
  ui->widget->Point_B = 0;
  ui->widget->update();
}
void MainWindow::on_Point_B_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Point_R = 0;
  ui->widget->Point_G = 0;
  ui->widget->Point_B = 1;
  ui->widget->update();
}
void MainWindow::on_Point_C_clicked() {
  ui->widget->Point_R = 1;
  ui->widget->Point_G = 1;
  ui->widget->Point_B = 1;
  ui->widget->s_p = 1;
  ui->widget->Point_Box_Value = 0;
  ui->Point_Box->setCurrentIndex(0);
  ui->Spin_P->setValue(1);
  ui->widget->update();
}

void MainWindow::on_Background_R_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Background_R = 1;
  ui->widget->Background_G = 0;
  ui->widget->Background_B = 0;
  ui->widget->update();
}
void MainWindow::on_Background_G_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Background_R = 0;
  ui->widget->Background_G = 1;
  ui->widget->Background_B = 0;
  ui->widget->update();
}
void MainWindow::on_Background_B_clicked() {
  ui->widget->checkCollor = 1;
  ui->widget->Background_R = 0;
  ui->widget->Background_G = 0;
  ui->widget->Background_B = 1;
  ui->widget->update();
}
void MainWindow::on_Background_C_clicked() {
  ui->widget->Background_R = 0;
  ui->widget->Background_G = 0;
  ui->widget->Background_B = 0;
  ui->widget->update();
}

void MainWindow::on_MOVE_clicked() {
  double x_val = ui->moveX->toPlainText().toDouble();
  double y_val = ui->moveY->toPlainText().toDouble();
  double z_val = ui->moveZ->toPlainText().toDouble();

  qDebug() << x_val;

  if (fabs(x_val) > 1E-07) {
    move_x(&ui->widget->obj.vert_array, x_val / 100,
           ui->widget->obj.vertexes_num);
    ui->widget->update();
  }
  if (fabs(y_val) > 1E-07) {
    move_y(&ui->widget->obj.vert_array, y_val / 100,
           ui->widget->obj.vertexes_num);
    ui->widget->update();
  }
  if (fabs(z_val) > 1E-07) {
    move_z(&ui->widget->obj.vert_array, z_val / 100,
           ui->widget->obj.vertexes_num);
    ui->widget->update();
  }
}
void MainWindow::on_ROTATE_clicked() {
  double x_val = ui->rotX->toPlainText().toDouble();
  double y_val = ui->rotY->toPlainText().toDouble();
  double z_val = ui->rotZ->toPlainText().toDouble();

  rotate_x(&ui->widget->obj.vert_array, x_val, ui->widget->obj.vertexes_num);
  rotate_y(&ui->widget->obj.vert_array, y_val, ui->widget->obj.vertexes_num);
  rotate_z(&ui->widget->obj.vert_array, z_val, ui->widget->obj.vertexes_num);
  ui->widget->update();
}
void MainWindow::on_Move_C_clicked() {
  ui->moveX->setText("0");
  ui->moveY->setText("0");
  ui->moveZ->setText("0");
  ui->widget->init_obj(filename);
  ui->widget->update();
}
void MainWindow::on_Rotate_C_clicked() {
  ui->rotX->setText("0");
  ui->rotY->setText("0");
  ui->rotZ->setText("0");
  ui->widget->init_obj(filename);
  ui->widget->update();
}

void MainWindow::on_Spin_L_valueChanged(int arg1) {
  ui->widget->s_l = arg1;
  ui->widget->update();
}
void MainWindow::on_Spin_P_valueChanged(int arg2) {
  ui->widget->s_p = arg2;
  ui->widget->update();
}

void MainWindow::on_Line_Box_activated(int index) {
  ui->widget->Line_Box_Value = index;
  ui->widget->update();
}
void MainWindow::on_Point_Box_activated(int index) {
  ui->widget->Point_Box_Value = index;
  ui->widget->update();
}

void MainWindow::on_RadProjection_clicked() {
  if (ui->RadProjection->isChecked()) {
    ui->widget->usePerspective = 1;
    ui->widget->update();
  } else {
    ui->widget->usePerspective = 0;
    ui->widget->update();
  }
}

void MainWindow::on_Screenshot_clicked() {
  QString file =
      QFileDialog::getSaveFileName(this, tr("Save File"), "Screenshot",
                                   tr("PNG (*.png);; JPEG (*.jpg *.jpeg)"));
  ui->widget->grabFramebuffer().save(file);
}

void MainWindow::on_StartGif_clicked() {
  ui->widget->checkGif = 1;
  timer = new QTimer;
  timer->setInterval(1000);

  connect(timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
  timer->start();

  auto fileName = "test.gif";

  // int width = ui->widget->width();
  // int height = ui->widget->height();
  GifBegin(&g, fileName, ui->widget->width(), ui->widget->height(), 0);

  timer->singleShot(50000, this, SLOT(kill_timer()));
}

void MainWindow::timer_tick() {
  // int width = ui->widget->width();
  // int height = ui->widget->height();
  QImage frame = ui->widget->grabFramebuffer();
  GifWriteFrame(&g,
                frame.convertToFormat(QImage::Format_Indexed8)
                    .convertToFormat(QImage::Format_RGBA8888)
                    .constBits(),
                ui->widget->width(), ui->widget->height(), 0);
}
void MainWindow::kill_timer() {
  timer->stop();
  GifEnd(&g);
}
void MainWindow::on_SaveGif_clicked() {
  if (ui->widget->checkGif) {
    emit MainWindow::kill_timer();
  }
}

void MainWindow::on_SaveSettings_clicked() {
  QSettings mySettings("Settings.ini", QSettings::IniFormat);
  mySettings.beginGroup("Widget");

  mySettings.setValue("Lines_R", ui->widget->Lines_R);
  mySettings.setValue("Lines_G", ui->widget->Lines_G);
  mySettings.setValue("Lines_B", ui->widget->Lines_B);

  mySettings.setValue("Point_R", ui->widget->Point_R);
  mySettings.setValue("Point_G", ui->widget->Point_G);
  mySettings.setValue("Point_B", ui->widget->Point_B);

  mySettings.setValue("BackGround_R", ui->widget->Background_R);
  mySettings.setValue("BackGround_G", ui->widget->Background_G);
  mySettings.setValue("BackGround_B", ui->widget->Background_B);

  mySettings.setValue("Spin_L", ui->widget->s_l);
  mySettings.setValue("Spin_P", ui->widget->s_p);

  mySettings.setValue("Line_Box", ui->widget->Line_Box_Value);
  mySettings.setValue("Point_Box", ui->widget->Point_Box_Value);

  mySettings.setValue("moveX", ui->moveX->toPlainText());
  mySettings.setValue("moveY", ui->moveY->toPlainText());
  mySettings.setValue("moveZ", ui->moveZ->toPlainText());

  mySettings.setValue("rotX", ui->rotX->toPlainText());
  mySettings.setValue("rotY", ui->rotY->toPlainText());
  mySettings.setValue("rotZ", ui->rotZ->toPlainText());

  mySettings.setValue("RadProjection", ui->RadProjection->isChecked());

  mySettings.setValue("Figure", filename);
  mySettings.setValue("Name_Figure", ui->FileName->text());
  mySettings.setValue("Vertexes_Num", ui->Vertexes_Num->text());
  mySettings.setValue("Facets_Num", ui->Facets_Num->text());

  mySettings.endGroup();
}

void MainWindow::on_LoadSettings_clicked() {
  QSettings mySettings("Settings.ini", QSettings::IniFormat);
  mySettings.beginGroup("Widget");

  ui->widget->Lines_R = mySettings.value("Lines_R", QByteArray()).toInt();
  ui->widget->Lines_G = mySettings.value("Lines_G", QByteArray()).toInt();
  ui->widget->Lines_B = mySettings.value("Lines_B", QByteArray()).toInt();

  ui->widget->Point_R = mySettings.value("Point_R", QByteArray()).toInt();
  ui->widget->Point_G = mySettings.value("Point_G", QByteArray()).toInt();
  ui->widget->Point_B = mySettings.value("Point_B", QByteArray()).toInt();

  ui->widget->Background_R =
      mySettings.value("BackGround_R", QByteArray()).toInt();
  ui->widget->Background_G =
      mySettings.value("BackGround_G", QByteArray()).toInt();
  ui->widget->Background_B =
      mySettings.value("BackGround_B", QByteArray()).toInt();

  ui->widget->s_l = mySettings.value("Spin_L", QByteArray()).toInt();
  ui->widget->s_p = mySettings.value("Spin_P", QByteArray()).toInt();

  ui->widget->Line_Box_Value =
      mySettings.value("Line_Box", QByteArray()).toInt();
  ui->widget->Point_Box_Value =
      mySettings.value("Point_Box", QByteArray()).toInt();

  ui->Spin_L->setValue(mySettings.value("Spin_L", QByteArray()).toInt());
  ui->Spin_P->setValue(mySettings.value("Spin_P", QByteArray()).toInt());

  ui->moveX->setText(mySettings.value("moveX").toString());
  ui->moveY->setText(mySettings.value("moveY").toString());
  ui->moveZ->setText(mySettings.value("moveZ").toString());

  ui->rotX->setText(mySettings.value("rotX").toString());
  ui->rotY->setText(mySettings.value("rotY").toString());
  ui->rotZ->setText(mySettings.value("rotZ").toString());

  ui->RadProjection->setChecked(
      mySettings.value("RadProjection", QByteArray()).toInt());

  filename = mySettings.value("Figure", QByteArray()).toString();
  ui->FileName->setText(mySettings.value("Name_Figure").toString());
  ui->Vertexes_Num->setText(mySettings.value("Vertexes_Num").toString());
  ui->Facets_Num->setText(mySettings.value("Facets_Num").toString());

  mySettings.endGroup();

  ui->widget->init_obj(filename);

  ui->widget->update();
}
