#include "tst_arduinorepo.h"
#include <QtTest/QtTest>
#include <repo/arduinorepo.h>

void ArduinoRepoTest::initTestCase() {
  QDir dir(".");
  testConnection = dir.absoluteFilePath("bsf.db");
}

/*
 * Checks if the default value was applied when arduino is NOT found.
 * */
void ArduinoRepoTest::isActiveArduinoIdNotZero() {
  // ARRANGE
  int arduinoId = 1;
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
  ArduinoRepository arduinoRepository(testConnection);

  // ACT
  Arduino arduino = arduinoRepository.getArduino(arduinoId);

  // ASSERT
  QVERIFY(arduino.getId() == arduinoId);
}

void ArduinoRepoTest::cleanupTestCase() {
}
