#include "ui_experimental.h"
#include "experimental.h"

Experimental::Experimental(QWidget *parent) :
  ui(new Ui::Experimental), QWidget(parent) {
  ui->setupUi(this);
}
Experimental::~Experimental() {
  delete ui;
}
