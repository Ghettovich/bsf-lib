#ifndef APPSERVICE_IODEVICES_H_
#define APPSERVICE_IODEVICES_H_

#include <memory>
#include <QObject>
#include <iodevice/iodeviceservice.h>
#include <broker/BrokerService.h>
#include <state/stateservice.h>

namespace appservice {
class IODeviceAppService;
}

class appservice::IODeviceAppService : public QObject {
 Q_OBJECT

 public:
  explicit IODeviceAppService(std::shared_ptr<service::BrokerService> &brokerService,
                              std::shared_ptr<IODeviceService> &deviceService,
                              std::shared_ptr<StateService> &stateService,
                              QObject *parent = nullptr);
  std::shared_ptr<IODevice> findOne(int id);

  QList<std::shared_ptr<IODevice>> findAll();
  QList<std::shared_ptr<IODevice>> findAll(IODeviceType::IO_DEVICE_TYPE type);

 public slots:
  void onToggleRelay(int id);

 private:
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<StateService> stateService;

 signals:
  void updateIODeviceState(int deviceId, bool on);
  void updateScale(int deviceId, bool on, int recipeId, int componentId, int weight);
};

#endif //APPSERVICE_IODEVICES_H_
