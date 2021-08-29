#ifndef BSF_LIB_SRC_SERVICE_UI_UI_SERVICE_H_
#define BSF_LIB_SRC_SERVICE_UI_UI_SERVICE_H_

#include <memory>
#include <QObject>
#include <QMap>
#include <ui/interfaces/sensor.widget.h>

namespace service {
class UiService;
}

class service::UiService : public QObject {
 Q_OBJECT

 public:
  explicit UiService(QObject *parent = nullptr);
  void addWidget(const QList<QWidget *> &widgets);

 public slots:
  void onUpdateWidgetState(int deviceId, bool on);
  void onToggleRelay(int relayId);

 private:
  QMap<int, SensorWidget *> widgetMap;
  QList<QMetaObject::Connection> connections;

  void addDeviceWidget(int id, QWidget *widget);

 signals:
  void toggleRelay(int relayId);
};

#endif //BSF_LIB_SRC_SERVICE_UI_UI_SERVICE_H_
