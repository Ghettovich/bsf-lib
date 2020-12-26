#ifndef BSF_ARDUINOREPO_H
#define BSF_ARDUINOREPO_H

#include <bsfdatabaseconfig.h>
#include <arduino.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>
#include <QtWidgets/QTreeWidgetItem>

class ArduinoRepository {

 public:
  explicit ArduinoRepository(const QString &connection = "");
  Arduino getArduino(int id);
  Arduino getActiveArduinoWithIODevices(int arduinoId);
  QVector<Arduino> getAllActiveArduino();
  QList<QTreeWidgetItem *> getArduinoTreeWidgets();
  void updateArduino(const Arduino &arduinoDevice);

 private:
  BsfDbconfig bsfDbConfig;
  IODevice *createIODeviceFromResult(const QSqlQuery &);

};
#endif //BSF_ARDUINOREPO_H
