#include "viewer.h"

viewer::viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3DViewer 1.0");
  setGeometry(400, 200, 800, 600);
}

void viewer::make_c_str(QString q_str, char *c_str) {
  std::string current_locale_text = q_str.toLocal8Bit().constData();
  const char *const_c_str = current_locale_text.c_str();
  int i = 0;
  for (; i < (int)strlen(const_c_str); i++) {
    c_str[i] = (char)const_c_str[i];
  }
  c_str[i] = '\0';
}

void viewer::init_obj(QString filename) {
  if (!(filename.isEmpty())) {
    free_object();
    char c_filename[filename.length()];
    make_c_str(filename, c_filename);
    load_model(c_filename, &obj);
    xRot = 0;
    yRot = 0;
  }
}

void viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void viewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void viewer::paintGL() {
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glClearColor(Background_R, Background_G, Background_B, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (usePerspective) {
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 100.0);
    glTranslatef(0, 0, -3);
  } else {
    glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, 100.0);
    glTranslatef(0, 0, -3);
  }

  glLineWidth(s_l);
  glRotated(xRot, 1, 0, 0);
  glRotated(yRot, 0, 1, 0);
  glPointSize(s_p);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.vertexes_num * 3,
               obj.vert_array, GL_STREAM_DRAW);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  draw();
}

void viewer::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }
void viewer::mouseMoveEvent(QMouseEvent *mo) {
  yRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  xRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void viewer::draw() {
  glEnable(GL_POINT_SMOOTH);

  if (Line_Box_Value == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  } else if (Line_Box_Value == 0) {
    glDisable(GL_LINE_STIPPLE);
  }

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);

  // glVertexPointer(3, GL_FLOAT, 0, obj.vert_array);
  // glEnableClientState(GL_VERTEX_ARRAY);

  if (Point_Box_Value == 0) {
    glPointSize(0);
  } else if (Point_Box_Value == 1) {
    glColor3d(Point_R, Point_G, Point_B);
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.vertexes_num);
  } else if (Point_Box_Value == 2) {
    glColor3d(Point_R, Point_G, Point_B);
    glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.vertexes_num);
  }

  glColor3d(Lines_R, Lines_G, Lines_B);
  glDrawElements(GL_LINES, (obj.facets_num * 2), GL_UNSIGNED_INT,
                 obj.poly_array);

  glDisableVertexAttribArray(0);
  // glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void viewer::free_object() {
  if (obj.vert_array && obj.poly_array && obj.vertexes_num != 0) {
    free_model(&obj);
  }
}
