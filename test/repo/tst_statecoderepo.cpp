#include "tst_statecoderepo.h"
#include <repo/statecoderepo.h>
#include <QDir>
#include <QTest>

void StateCodeRepoTest::init() {
  QDir dir(".");
  QString path = dir.relativeFilePath("../data/bsf.db");
  testConnection = dir.absoluteFilePath(path);
}

/*
 * Check if the statecode is found with id.
 * */
void StateCodeRepoTest::isStateCodeFound() {
  // ARRANGE
  int stateCodeId = 0;
  const QString message = "READY";
  StateCodeRepository stateCodeRepository(testConnection);

  // ACT
  StateCode stateCode = stateCodeRepository.getStateCode(stateCodeId);

  // ASSERT
  QVERIFY(stateCode.getMessage().toUpper() == message);
}

void StateCodeRepoTest::cleanupTestCase() {
}


