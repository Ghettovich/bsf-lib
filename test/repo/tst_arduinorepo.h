#ifndef BSF_TST_ARDUINOREPO_H
#define BSF_TST_ARDUINOREPO_H


#include "../autotest/AutoTest.h"
#include <QtCore/QObject>

class ArduinoRepoTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isActiveArduinoListGreaterThenZero();
    void isActiveArduinoIdNotZero();
    void isArduinoFoundWithId();
    void isArduinoUpdated();

    void cleanupTestCase();

};


#endif //BSF_TST_ARDUINOREPO_H
