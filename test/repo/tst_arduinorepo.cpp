#include "tst_arduinorepo.h"
#include <QtTest/QtTest>
#include <repo/arduinorepo.h>

void ArduinoRepoTest::initTestCase() {
}

/*
 * Checks if the default value was applied when arduino is NOT found.
 * */
void ArduinoRepoTest::isActiveArduinoIdNotZero() {
  // ARRANGE
  int arduinoId = 1;
  QDir dir(".");
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
  ArduinoRepository arduinoRepository(testConnection);

  // ACT
  Arduino arduino = arduinoRepository.getActiveArduinoWithIODevices(arduinoId);

  // ASSERT
  QVERIFY(arduino.getId() != 0);
}

/*
 * Checks if the received list is not empty.
 * */
void ArduinoRepoTest::isActiveArduinoListGreaterThenZero() {
  // ARRANGE
  int size = 0;
  QDir dir(".");
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
  ArduinoRepository arduinoRepository(testConnection);

  // ACT
  QVector<Arduino> arduinoList = arduinoRepository.getAllActiveArduino();

  // ASSERT
  QVERIFY(arduinoList.size() > size);
}

/*
 * Checks if the arduino id is as expected.
 * */
void ArduinoRepoTest::isArduinoFoundWithId() {
  // ARRANGE
  int arduinoId = 2;
  QDir dir(".");
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
  ArduinoRepository arduinoRepository(testConnection);

  // ACT
  Arduino arduino = arduinoRepository.getArduino(arduinoId);

  // ASSERT
  QVERIFY(arduino.getId() == arduinoId);
}

void ArduinoRepoTest::cleanupTestCase() {
}
