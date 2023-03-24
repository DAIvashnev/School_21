#ifndef VIEWER_H
#define VIEWER_H

#define GL_GLEXT_PROTOTYPES

//#include <qopenglext.h>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtWidgets/QWidget>
#include <cmath>

#include "mainwindow.h"

extern "C" {
#include "../affine.h"
#include "../parser.h"
}

class viewer : public QOpenGLWidget {
  Q_OBJECT
 private:
  QPoint mPos;
  QTimer tmr;
  void draw();
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void make_c_str(QString q_str, char *c_str);

  GLuint VBO;
  GLuint VAO;

 public:
  float xRot, yRot, zRot;
  viewer(QWidget *parent = Q_NULLPTR);
  int DrawFlag = 0;
  model obj = {0, 0, {0, 0, 0, 0, 0, 0}, 0, 0};

  void init_obj(QString filename);
  void transform(float size);
  void free_object();

  int usePerspective = 0;

  int checkCollor = 0;
  int checkGif = 0;

  int Background_R = 0;
  int Background_G = 0;
  int Background_B = 0;

  int Point_R = 1;
  int Point_G = 1;
  int Point_B = 1;

  int Lines_R = 1;
  int Lines_G = 1;
  int Lines_B = 1;

  int s_l = 1;
  int s_p = 1;

  int Line_Box_Value = 0;
  int Point_Box_Value = 0;
};

#endif  // VIEWER_H
