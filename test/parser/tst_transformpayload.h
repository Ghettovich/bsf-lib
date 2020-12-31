#ifndef BSF_TST_TRANSFORMPAYLOAD_H
#define BSF_TST_TRANSFORMPAYLOAD_H

//#include "../autotest/AutoTest.h"
#include <QTest>
#include <QtCore/QObject>

class TransformPayloadTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void parseRelayStates();
    void parseProximity();
    void cleanupTestCase();

};


#endif //BSF_TST_TRANSFORMPAYLOAD_H
