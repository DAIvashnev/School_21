#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class mainview;
}

class mainview : public QWidget {
  Q_OBJECT

 public:
  explicit mainview(QWidget *parent = nullptr);
  ~mainview();

 private:
  Ui::mainview *ui;
};

#endif  // MAINVIEW_H
