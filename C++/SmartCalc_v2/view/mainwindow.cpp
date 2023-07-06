#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_ob, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));
  connect(ui->pushButton_cb, SIGNAL(clicked()), this,
          SLOT(getValFromButtonOther()));

  connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(getValueFromButtonFunc()));

  ui->pushButton_div->setCheckable(true);
  ui->pushButton_mult->setCheckable(true);
  ui->pushButton_sub->setCheckable(true);
  ui->pushButton_sum->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::getValFromButtonOther() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_show->setText(ui->result_show->text() + button->text());
}

void MainWindow::getValueFromButtonFunc() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_show->setText(ui->result_show->text() + button->text() + "(");
}

void MainWindow::operations() {
  double all_numbers;
  QString new_label;

  all_numbers = (ui->result_show->text()).toDouble();
  all_numbers = all_numbers * 0.01;
  new_label = QString::number(all_numbers, 'g', 10);
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_bcsp_clicked() {
  QString str = ui->result_show->text();
  if (str.length() > 0) {
    ui->result_show->setText(str.remove(str.length() - 1, str.length()));
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->pushButton_div->setChecked(false);
  ui->pushButton_mult->setChecked(false);
  ui->pushButton_sub->setChecked(false);
  ui->pushButton_sum->setChecked(false);

  ui->result_show->setText("");
  ui->widget->clearGraphs();
  ui->widget->replot();
}

void MainWindow::on_pushButton_equally_clicked() {
  std::string expression = ui->result_show->text().toStdString();
  QString str = QString::fromStdString(expression);
  const char *exp = expression.c_str();
  s21::Controller controller;
  if (controller.InputNewExpression(exp)) {
    if (strchr(exp, 'x') != NULL) {
      printGraph(exp);
    } else {
      double result = controller.GetResult(exp, 0);
      ui->result_show->setText(QString::number(result, 'g', 10));
    }
  } else {
    ui->result_show->setText("Incorrect expression");
  }
}

void MainWindow::printGraph(const char *exp) {
  s21::Controller controller;
  ui->widget->clearGraphs();
  double h = 0.01;
  double result = 0;
  int N;
  int x_max = ui->spinBox_Xmax->value();
  int x_min = ui->spinBox_Xmin->value();
  int y_max = ui->spinBox_Ymax->value();
  int y_min = ui->spinBox_Ymin->value();

  ui->widget->xAxis->setRange(x_max, x_min);
  ui->widget->yAxis->setRange(y_max, y_min);
  N = (x_max - x_min) / h;
  QVector<double> x(N), y(N);

  double val = x_min;
  for (int i = 0; i < N; i++) {
    result = controller.GetResult(exp, val);
    if (result <= y_min || result >= y_max) {
      val += h;
      x[i] = val;
      y[i] = NAN;
    } else {
      x[i] = val;
      y[i] = result;
      val += h;
    }
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}
