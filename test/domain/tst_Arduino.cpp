#include <arduino.h>
#include <arduinorepo.h>
#include <QFile>
#include <transformpayload.h>
#include "tst_Arduino.h"

void ArduinoTest::init() {
  QDir dir(".");
  printf("\n\n *** PATH IN TEST = %s\n", qUtf8Printable(dir.absolutePath()));
  QString path = dir.relativeFilePath("bsf.db");
  testConnection = path;
}

void ArduinoTest::onUpdateArduinoProximity() {
  // ARRANGE
  int arduinoId = 1;
  ArduinoRepository arduinoRepository(testConnection);

  Arduino arduino = arduinoRepository.getActiveArduinoWithIODevices(arduinoId);
  QFile jsonFile(":/payload/proximityStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  TransformPayload parser;

  // ACT
  QVector<IODevice *> iodeviceList = parser.parseIODevices(jsonFile.readAll());
  arduino.updateIODeviceList(iodeviceList);

  // ASSERT
  QVERIFY(!iodeviceList.empty());
}

void ArduinoTest::onUpdateArduinoRelay() {
  // ARRANGE
  int arduinoId = 1;
  ArduinoRepository arduinoRepository(testConnection);

  Arduino arduino = arduinoRepository.getActiveArduinoWithIODevices(arduinoId);
  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  TransformPayload parser;

  // ACT
  QVector<IODevice *> iodeviceList = parser.parseIODevices(jsonFile.readAll());
  arduino.updateIODeviceList(iodeviceList);

  // ASSERT
  QVERIFY(!iodeviceList.empty());
}

void ArduinoTest::cleanupTestCase() {

}
