#include "tst_logrepo.h"
#include <bafalog.h>
#include <logrepo.h>
#include <QtTest/QtTest>

void LogRepoTest::initTestCase() {
  QDir dir(".");
  QString path = dir.relativeFilePath("../data/bsf.db");
  testConnection = path;
}

/*
 * Check if log list is not empty.
 * */
void LogRepoTest::isLogListEmpty() {
  // ARRANGE
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
  LogRepository logRepository(testConnection);

  // ACT
  QVector<BafaLog> logList = logRepository.createBsfLogList();
  logRepository.addLog("Hoi", BafaLog::INFO);

  QThread::msleep(5);
  QVector<BafaLog> secondLogList = logRepository.createBsfLogList();

  // ASSERT
  QVERIFY(secondLogList.size() > logList.size());
}

void LogRepoTest::cleanupTestCase() {
}
