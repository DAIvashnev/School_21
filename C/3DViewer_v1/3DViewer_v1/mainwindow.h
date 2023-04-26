#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMoveEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QtOpenGL>
#include <QtWidgets/QWidget>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../gif.h"

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
  QString filename = NULL;
  QTimer *timer;
  QVector<QImage> img_array;
  GifWriter g;

 private slots:
  void on_OpenFile_clicked();

  void clean_param();
  void on_Clean_clicked();

  void on_Lines_R_clicked();
  void on_Lines_G_clicked();
  void on_Lines_B_clicked();
  void on_Lines_C_clicked();

  void on_Point_R_clicked();
  void on_Point_G_clicked();
  void on_Point_B_clicked();
  void on_Point_C_clicked();

  void on_Background_R_clicked();
  void on_Background_G_clicked();
  void on_Background_B_clicked();
  void on_Background_C_clicked();

  void on_Spin_L_valueChanged(int arg1);
  void on_Spin_P_valueChanged(int arg1);

  void on_Line_Box_activated(int index);
  void on_Point_Box_activated(int index);

  void on_SizeSlider_valueChanged(int value);
  void on_SizeSlider_sliderMoved(int position);

  void on_MOVE_clicked();
  void on_ROTATE_clicked();
  void on_Move_C_clicked();
  void on_Rotate_C_clicked();

  void on_RadProjection_clicked();
  void on_Screenshot_clicked();
  void on_StartGif_clicked();
  void on_SaveGif_clicked();
  void on_SaveSettings_clicked();
  void on_LoadSettings_clicked();

 private:
  Ui::MainWindow *ui;
  int size_slider_state = 50;
  int spin = 1;
  int Line_Box = 0;
  int Point_Box = 0;
 public slots:
  void timer_tick();
  void kill_timer();
};
#endif  // MAINWINDOW_H
