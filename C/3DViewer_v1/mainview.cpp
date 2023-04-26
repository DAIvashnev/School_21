#include "mainview.h"

#include "ui_mainview.h"

mainview::mainview(QWidget *parent) : QWidget(parent), ui(new Ui::mainview) {
  ui->setupUi(this);
}

mainview::~mainview() { delete ui; }
