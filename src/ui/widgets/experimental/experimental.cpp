#include "ui_experimental.h"
#include "experimental.h"

#include <QSettings>

Experimental::Experimental(QWidget *parent) :
  ui(new Ui::Experimental), QWidget(parent) {
  ui->setupUi(this);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  ui->pushButtonLiftDown->setDeviceId(settings->value("liftdown").toInt());
  ui->pushButtonLiftUp->setDeviceId(settings->value("liftup").toInt());

  settings->endGroup();

  settings->beginGroup("detectionsensor");
  ui->labelBinLoadDetected->setProperty("binload", settings->value("binload").toInt()); // PULL UP (HIGH = OFF!)

  settings->endGroup();

}
Experimental::~Experimental() {
  delete ui;
}
void Experimental::onUpdateLiftDown(bool off) {

}
void Experimental::onUpdateLiftUp(bool off) {

}
