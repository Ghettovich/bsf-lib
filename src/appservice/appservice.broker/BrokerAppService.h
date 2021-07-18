#ifndef BSF_BROKERAPPSERVICE_H_
#define BSF_BROKERAPPSERVICE_H_

#include <memory>
#include <QObject>
#include <broker/BrokerService.h>
#include <iodevice/iodeviceservice.h>

namespace appservice {
class BrokerAppService;
}

class appservice::BrokerAppService : public QObject {
 Q_OBJECT

 public:
  explicit BrokerAppService(std::shared_ptr<service::BrokerService> &brokerService,
                            std::shared_ptr<IODeviceService> &deviceService,
                            QObject *parent = nullptr);
 /// Connect to broker. Host is defined in configuration file.
 void connectToHost();
 void createDeviceStateSubscriptions();
 void toggleRelay(int id);
 QVector<IODevice *> findAll(IODeviceType::IO_DEVICE_TYPE type);

 private:
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;

 signals:
  void connectedToHost();
  void updateDevicesWithState(const QVector<IODevice *> &iodeviceList);
};

#endif //BSF_BROKERAPPSERVICE_H_
