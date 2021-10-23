#include "ui.service.h"
#include <ui/label/proximity.label.h>
#include <ui/button/relay.button.h>
#include <ui/scale/scale.lcdnumber.h>
#include <QtWidgets/QtWidgets>

using namespace service;

UiService::UiService(QObject *parent) : QObject(parent) {

}

void UiService::addDeviceWidget(int id, QWidget *widget) {
  QString sensor = widget->property("sensor").toString();

  if (QString::compare(sensor, "proximity") == 0) {
    auto w = new ProximityLabel(widget, widget->parentWidget());
    widgetMap.insert(id, w);
  } else if (QString::compare(sensor, "relay") == 0) {
    auto w = new RelayButton(widget, widget->parentWidget());

    connections << connect(w, &RelayButton::toggleRelay, this, &UiService::onToggleRelay);

    widgetMap.insert(id, w);
  } else if (QString::compare(sensor, "scale") == 0) {
    auto w = new ScaleLcdNumber(widget, widget->parentWidget());
    widgetMap.insert(id, w);
  } else {
    qWarning() << "Failed to insert SensorWidget, missing sensor property on QWidget";
  }
}

void UiService::addWidget(const QList<QWidget *> &widgets) {
  for (const auto &widget: widgets) {
    bool valid = false;
    int id = widget->property("deviceId").toInt(&valid);

    if (valid) {
      addDeviceWidget(id, widget);
    } else {
      qWarning() << "Failed to convert deviceId property from QWidget to int";
    }
  }
}

void UiService::onUpdateWidgetState(int deviceId, bool on) {
  if (!widgetMap.contains(deviceId)) {
    qWarning() << "Unable to find widget in device widget map.";
  } else {
    widgetMap.value(deviceId)->updateWidgetState(on);
  }
}
void UiService::onToggleRelay(int relayId) {
  emit toggleRelay(relayId);
}

void UiService::onUpdateScale(int deviceId, int weight) {
  if (!widgetMap.contains(deviceId)) {
    qWarning() << "Unable to find scale widget in device widget map.";
  } else {
    auto w = dynamic_cast<ScaleLcdNumber*>(widgetMap.value(deviceId));
    w->setScaleWeight(weight);
    w->updateWidgetState(true);
  }
}
