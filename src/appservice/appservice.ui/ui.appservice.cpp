#include "ui.appservice.h"

using namespace appservice;
using namespace service;

UiAppService::UiAppService(std::shared_ptr<service::UiService> &_uiService, QObject *parent) :
 uiService(_uiService), QObject(parent) {

  connect(uiService.get(), &UiService::toggleRelay, [=](int relayId){
    emit toggleRelay(relayId);
  });
}

void UiAppService::addWidget(const QList<QWidget *> &widgets) {
  uiService->addWidget(widgets);
}

void UiAppService::onUpdateWidget(int deviceId, bool on) {
  uiService->onUpdateWidgetState(deviceId, on);
}
