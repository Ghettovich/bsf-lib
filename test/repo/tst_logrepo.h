#ifndef BSF_TST_LOGREPO_H
#define BSF_TST_LOGREPO_H

#include <QtCore/QObject>

class LogRepoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void initTestCase();
  void isLogListEmpty();
  void isLogListSizeIncreased();
  void cleanupTestCase();
};

#endif //BSF_TST_LOGREPO_H
