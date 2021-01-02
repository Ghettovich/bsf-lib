#ifndef BSF_TST_STATECODEREPO_H
#define BSF_TST_STATECODEREPO_H

#include <QtCore/QObject>

class StateCodeRepoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void init();
  void isStateCodeFound();
  void cleanupTestCase();
};

#endif //BSF_TST_STATECODEREPO_H
