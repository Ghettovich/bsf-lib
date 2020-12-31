#include "tst_logrepo.h"
#include <bafalog.h>
#include <logrepo.h>
#include <QtTest/QtTest>

void LogRepoTest::initTestCase() {
}

/*
 * Check if log list is not empty.
 * */
void LogRepoTest::isLogListEmpty() {
  // ARRANGE
  QDir dir(".");
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
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
  dir.cdUp();
  const QString testConnection = dir.absoluteFilePath("resource/database/bsf.db");
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
