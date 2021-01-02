#ifndef BSF_TST_IODEVICEREPO_H
#define BSF_TST_IODEVICEREPO_H

#include <QtCore/QObject>

class IODeviceRepoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void init();
  void isIODeviceTypeFound();
  void isIODeviceListNotEmpty();
  void isRelayListFromArduinoEmpty();
  void isDetectionSensorListEmpty();
  void isWeightSensorListEmpty();
  void cleanUpTestCase();
};

#endif //BSF_TST_IODEVICEREPO_H
