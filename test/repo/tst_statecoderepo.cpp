#include "tst_statecoderepo.h"
#include <repo/statecoderepo.h>
#include <QDir>
#include <QTest>

void StateCodeRepoTest::initTestCase() {
}

/*
 * Check if the statecode is found with id.
 * */
void StateCodeRepoTest::isStateCodeFound() {
  // ARRANGE
  int stateCodeId = 0;
  const QString message = "READY";
  QDir dir(".");
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
  StateCodeRepository stateCodeRepository(testConnection);

  // ACT
  StateCode stateCode = stateCodeRepository.getStateCode(stateCodeId);

  // ASSERT
  QVERIFY(stateCode.getMessage().toUpper() == message);
}

void StateCodeRepoTest::cleanupTestCase() {
}


