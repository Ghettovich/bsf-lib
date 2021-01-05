#include "tst_actionarduinorepo.h"
#include <QtTest/QtTest>
#include <QDir>
#include <repo/actionarduinorepo.h>
#include <domain/action.h>

void ActionArduinoRepoTest::init() {
  QDir dir(".");
  QString path = dir.relativeFilePath("../data/bsf.db");
  testConnection = path;
}

/*
 * Checks if the received list is not empty.
 * */
void ActionArduinoRepoTest::isSizeOfActionListOfArduinoGreaterThanZero() {
  // ARRANGE
  int arduinoId = 1;
  ActionArduinoRepository actionArduinoRepository(testConnection);

  // ACT
  QVector<Action> actionList = actionArduinoRepository.getArduinoAction(arduinoId);

  // ASSERT
  QVERIFY(!actionList.empty());
}

void ActionArduinoRepoTest::cleanupTestCase() {
}
