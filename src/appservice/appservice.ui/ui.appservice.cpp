#include "ui.appservice.h"

using namespace appservice;

UiAppService::UiAppService(std::shared_ptr<service::UiService> &_uiService, QObject *parent) :
 uiService(_uiService), QObject(parent) {
}

void UiAppService::addWidget(const QList<QWidget *> &widgets) {
  uiService->addWidget(widgets);
}

void UiAppService::onUpdateWidget(int deviceId, bool on) {
  uiService->onUpdateWidgetState(deviceId, on);
}
