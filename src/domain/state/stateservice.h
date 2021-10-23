#ifndef BSF_STATESERVICE_H_
#define BSF_STATESERVICE_H_

#include <QObject>
#include <QMap>
#include <broker/BrokerService.h>
#include <iodevice/iodeviceservice.h>

class StateService : public QObject {
 Q_OBJECT

 public:
  explicit StateService(std::shared_ptr<service::BrokerService> &brokerService,
                        std::shared_ptr<IODeviceService> &_deviceService,
                        QObject *parent = nullptr);

 /// Subscribe to topics using the locally defined topics.
 void createDeviceStateSubscriptions();

 public slots:
  /// When a new message arrives for a topic it is deserialized and the @deviceStateMap is updated.
  void onNewIODeviceStates(const QByteArray &message, const QString &topic);

 private:
  const QString proximityLiftTopic = "proximity/lift";
  const QString relayStatesTopic = "relay/states";
  const QString scaleDataTopic = "recipe/data";

  QMap<int, IODevice *> deviceStateMap;
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;

  void parseRelayStates(const QByteArray &message);
  void parseProximityStates(const QByteArray &message);
  void parseIODevices(const QByteArray &payload);

  void updateScale(const QByteArray &message);
  void updateIODevices(const QJsonArray &jsonArray);
  static bool validateJsonDocument(QJsonDocument &);

 signals:
  void updateIODeviceState(int deviceId, IODevice::IO_DEVICE_HIGH_LOW state);
  void updateScaleDevice(int deviceId, double weight);
};

#endif //BSF_STATESERVICE_H_
