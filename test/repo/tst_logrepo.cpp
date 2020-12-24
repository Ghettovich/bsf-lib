#include "tst_logrepo.h"
#include <bafalog.h>
#include <logrepo.h>
#include <QtTest/QtTest>


DECLARE_TEST_LOG_REPO(LogRepoTest)

void LogRepoTest::initTestCase() {
}

/*
 * Check if log list is not empty.
 * */
void LogRepoTest::isLogListEmpty() {
    // ARRANGE
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    LogRepository logRepository(testConnection);

    // ACT
    QVector<BafaLog> logs = logRepository.createBsfLogList();

    // ASSERT
    QVERIFY(!logs.empty());
}

/*
 * Checks wether the log list size is increased after adding a new log.
 * */
void LogRepoTest::isLogListSizeIncreased() {
    // ARRANGE
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    LogRepository logRepository(testConnection);

    // ACT
    QVector<BafaLog> logList = logRepository.createBsfLogList();
    logRepository.addLog("Hoi", BafaLog::INFO);
    QVector<BafaLog> secondLogList = logRepository.createBsfLogList();

    printf("\nfirst size = %d\n", logList.size());
    printf("\nsecond size = %d\n", secondLogList.size());

    // ASSERT
    QVERIFY(secondLogList.size() > logList.size());
}

void LogRepoTest::cleanupTestCase() {
}
