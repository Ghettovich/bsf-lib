#include "ui_home.h"
#include "home.h"

#include <QListWidgetItem>

using namespace appservice;

Home::Home(std::shared_ptr<IODeviceAppService> &_deviceAppService, QWidget *parent) :
    ui(new Ui::Home),
    deviceAppService(_deviceAppService),
    QWidget(parent) {
  ui->setupUi(this);
}
Home::~Home() {
  delete ui;
}
