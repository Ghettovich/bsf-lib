#include "tst_actionarduinorepo.h"
#include <QtTest/QtTest>
#include <QDir>
#include <repo/actionarduinorepo.h>
#include <domain/action.h>

void ActionArduinoRepoTest::initTestCase() {
}

/*
 * Checks if the received list is not empty.
 * */
void ActionArduinoRepoTest::isSizeOfActionListOfArduinoGreaterThanZero() {
  // ARRANGE
  int arduinoId = 1;

  QDir dir(".");
  dir.cdUp();

  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
  ActionArduinoRepository actionArduinoRepository(testConnection);

  // ACT
  QVector<Action> actionList = actionArduinoRepository.getArduinoAction(arduinoId);

  // ASSERT
  QVERIFY(!actionList.empty());
}

void ActionArduinoRepoTest::cleanupTestCase() {
}
