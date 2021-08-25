#include "ui_home.h"
#include "home.h"

Home::Home(QWidget *parent) :
  ui(new Ui::Home), QWidget(parent) {
  ui->setupUi(this);
}
Home::~Home() {
  delete ui;
}
