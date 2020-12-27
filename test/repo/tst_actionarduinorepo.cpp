#include "tst_actionarduinorepo.h"
#include <QtTest/QtTest>
#include <QDir>
#include <repo/actionarduinorepo.h>
#include <domain/action.h>

DECLARE_TEST_ACTION_ARDUINO_REPO(ActionArduinoRepoTest)

void ActionArduinoRepoTest::initTestCase() {
    //db.createTestDatabase();
    //db.insertData();
}

/*
 * Checks if the received list is not empty.
 * */
void ActionArduinoRepoTest::isSizeOfActionListOfArduinoGreaterThanZero() {
    // ARRANGE
    int arduinoId = 1;

    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    ActionArduinoRepository actionArduinoRepository(testConnection);

    // ACT
    QVector<Action> actionList = actionArduinoRepository.getArduinoAction(arduinoId);

    // ASSERT
    QVERIFY(!actionList.empty());
}

void ActionArduinoRepoTest::cleanupTestCase() {
}