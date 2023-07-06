#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>

#include "../controller/controller.h"
#include "../model/model.h"

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

 private:
  Ui::MainWindow *ui;

 private slots:
  void getValFromButtonOther();
  void getValueFromButtonFunc();
  void operations();
  void on_pushButton_bcsp_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_equally_clicked();
  void printGraph(const char *exp);
};
#endif  // MAINWINDOW_H
