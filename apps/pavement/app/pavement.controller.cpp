#include "pavement.controller.h"
#include <widgets/home/home.h>
#include <widgets/experimental/experimental.h>

PavementController::PavementController(QObject *parent) : QObject(parent) {
}

void PavementController::createStackedWidget(QLayout *layout) {
  stackedWidget = new QStackedWidget;

  stackedWidget->addWidget(new Home(stackedWidget));
  stackedWidget->addWidget(new QWidget); // ToDo: replace with new mixture
  stackedWidget->addWidget(new Experimental(stackedWidget));

  layout->addWidget(stackedWidget);
}
void PavementController::updateCurrentWidget(int widgetNr) {
  stackedWidget->setCurrentIndex(widgetNr);
}
