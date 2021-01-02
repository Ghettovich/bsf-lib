#ifndef BSF_TST_ARDUINOREPO_H
#define BSF_TST_ARDUINOREPO_H

#include <QtCore/QObject>

class ArduinoRepoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void initTestCase();
  void isActiveArduinoListGreaterThenZero();
  void isActiveArduinoIdNotZero();
  void isArduinoFoundWithId();
  void cleanupTestCase();

};

#endif //BSF_TST_ARDUINOREPO_H
