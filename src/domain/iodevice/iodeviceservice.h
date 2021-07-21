#ifndef BSF_IODEVICESERVICE_H_
#define BSF_IODEVICESERVICE_H_

#include "iodevice.h"
#include "iodevicetype.h"
#include "iodevicerepo.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <database/DatabaseService.h>
#include <broker/BrokerService.h>


class IODeviceService : public QObject {
 Q_OBJECT

 public:
  explicit IODeviceService(std::shared_ptr<service::DatabaseService> databaseService,
                           std::shared_ptr<service::BrokerService> &brokerService,
                           QObject *parent = nullptr);
  QVector<IODevice *> findAllDevices();
  QVector<IODevice *> findAllDevices(IODeviceType::IO_DEVICE_TYPE deviceType);

  void createDeviceStateSubscriptions();

 public slots:
  void onNewIODeviceStates(const QByteArray &message, const QString &topic);

 private:
  const QString proximityLiftTopic = "/proximity/lift";
  const QString relayStatesTopic = "/relay/states";
  const QString recipeDataTopic = "/recipe/data";

  QVector<IODevice *> devices;
  std::shared_ptr<IODeviceRepository> deviceRepository;
  std::shared_ptr<service::BrokerService> brokerService;

  void updateDevices(IODevice *iodevice);
  void updateDevices(const QVector<IODevice *>& devices);
  void parseRelayStates(const QByteArray &message);
  void parseProximityStates(const QByteArray &message);
  void parseRecipeData(const QByteArray &message);

  QVector<IODevice *> parseIODevices(const QByteArray &payload);
  static bool validateJsonDocument(QJsonDocument &);
  QVector<IODevice *> addProximitiesToArray(const QJsonArray &jsonArray);
  QVector<IODevice *> addRelaysToArray(const QJsonArray &jsonArray);

 signals:
  void updateRelayDevices(const QVector<IODevice *> &devices);
  void updateProximityDevices(const QVector<IODevice *> &devices);
  void updateScale(IODevice *device);
};

#endif //BSF_IODEVICESERVICE_H_
