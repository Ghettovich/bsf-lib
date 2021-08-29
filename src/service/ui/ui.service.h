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

 private:
  //QMap<int, QWidget *> widgetMap;
  QMap<int, SensorWidget *> widgetMap;

  void addDeviceWidget(int id, QWidget *widget);
};

#endif //BSF_LIB_SRC_SERVICE_UI_UI_SERVICE_H_
