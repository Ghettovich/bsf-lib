#include "tst_statecoderepo.h"
#include <repo/statecoderepo.h>

DECLARE_TEST_STATECODE_REPO(StateCodeRepoTest)

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
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    StateCodeRepository stateCodeRepository(testConnection);

    // ACT
    StateCode stateCode = stateCodeRepository.getStateCode(stateCodeId);

    // ASSERT
    QVERIFY(stateCode.getMessage().toUpper() == message);
}

void StateCodeRepoTest::cleanupTestCase() {
}


