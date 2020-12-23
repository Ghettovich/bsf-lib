#include "tst_arduinorepo.h"
#include <QtTest/QtTest>
#include <repo/arduinorepo.h>

DECLARE_TEST_ARDUINO_REPO(ArduinoRepoTest)

void ArduinoRepoTest::initTestCase() {
}

/*
 * Checks if the default value was applied when arduino is NOT found.
 * */
void ArduinoRepoTest::isActiveArduinoIdNotZero() {
    // ARRANGE
    int arduinoId = 1;
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
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
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
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
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    ArduinoRepository arduinoRepository(testConnection);

    // ACT
    Arduino arduino = arduinoRepository.getArduino(arduinoId);

    // ASSERT
    QVERIFY(arduino.getId() == arduinoId);
}

/*
 * Checks wether the arduino is updated. Not really usefull since it will be the same next time the test runs.
 * Will be fixed once DML script can be deployed on the fly.
 * */
void ArduinoRepoTest::isArduinoUpdated() {
    // ARRANGE
    int arduinoId = 1;
    QString newValue = "Durp";
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    ArduinoRepository arduinoRepository(testConnection);

    // ACT
    Arduino arduino = arduinoRepository.getArduino(arduinoId);
    arduino.setName(newValue);
    arduinoRepository.updateArduino(arduino);
    arduino = arduinoRepository.getArduino(arduinoId);

    // ASSERT
    QVERIFY(arduino.getName() == newValue);
}

void ArduinoRepoTest::cleanupTestCase() {
}
