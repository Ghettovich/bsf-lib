#ifndef BSF_LIB_TEST_DOMAIN_TST_ARDUINO_H_
#define BSF_LIB_TEST_DOMAIN_TST_ARDUINO_H_

#include <QtTest/QTest>
#include <QtCore/QObject>

class ArduinoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void init();
  void onUpdateArduinoProximity();
  void onUpdateArduinoRelay();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_DOMAIN_TST_ARDUINO_H_
