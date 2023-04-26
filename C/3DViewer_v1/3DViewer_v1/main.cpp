#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_ALL, "C");
  MainWindow w;
  w.setWindowTitle("3DViewer 1.0");
  w.show();
  return a.exec();
}
