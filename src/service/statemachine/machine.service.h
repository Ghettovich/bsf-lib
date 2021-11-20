#ifndef BSF_LIB_SRC_SERVICE_STATEMACHINE_MACHINE_SERVICE_H_
#define BSF_LIB_SRC_SERVICE_STATEMACHINE_MACHINE_SERVICE_H_

#include <memory>
#include <QObject>
#include <QSettings>

namespace service {
class MachineService;
}

class service::MachineService : public QObject {
 Q_OBJECT

 public:
  explicit MachineService(QObject *parent = nullptr);

 public slots:
  void onIODeviceChange(int deviceId, bool status);

  void proximityStatusChange(int deviceId, bool status);
  void relayStatusChange(int deviceId, bool status);

 signals:
  void proximityLoadChanged(bool status);
  void proximityDropChanged(bool status);
  void proximityLiftTopChanged(bool status);
  void proximityLiftBottomChanged(bool status);
  void relayLiftDownChanged(bool status);
  void relayLiftUpChanged(bool status);
  void relayBinLoadChanged(bool status);
  void relayBinDropChanged(bool status);
  void hydraulicChanged(bool status);
};

#endif //BSF_LIB_SRC_SERVICE_STATEMACHINE_MACHINE_SERVICE_H_
