#ifndef BSF_LIB_SRC_APPSERVICE_UI_APPSERVICE_H_
#define BSF_LIB_SRC_APPSERVICE_UI_APPSERVICE_H_

#include <memory>
#include <QObject>

#include <ui/ui.service.h>

namespace appservice {
class UiAppService;
}

class appservice::UiAppService : public QObject {
 Q_OBJECT

 public:
  explicit UiAppService(std::shared_ptr<service::UiService> &uiService,
                        QObject *parent = nullptr);
  void addWidget(const QList<QWidget *> &widgets);

 public slots:
  void onUpdateWidget(int deviceId, bool on);
  void onUpdateScaleWidget(int deviceId, int weight);

 private:
  std::shared_ptr<service::UiService> uiService;

 signals:
  void toggleRelay(int relayId);
};

#endif //BSF_LIB_SRC_APPSERVICE_UI_APPSERVICE_H_
