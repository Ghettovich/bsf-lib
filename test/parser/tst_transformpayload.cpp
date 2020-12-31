#include "tst_transformpayload.h"
#include <QFile>
#include <QVector>
#include <iodevice.h>
#include <transformpayload.h>

//DECLARE_TEST_TRANSFORMPAYLOAD(TransformPayloadTest)

void TransformPayloadTest::initTestCase() {
}

/*
 * Load up the full payload state from a JSON file and check if it succesfully parsed.
 * */
void TransformPayloadTest::parseRelayStates() {
    // ARRANGE
    TransformPayload transformPayload;
    QVector<IODevice *> ioDeviceList;
    QFile jsonFile(":/payload/relayStates.json");

    // ACT
    if(!jsonFile.exists()) {
        QVERIFY2(false, "Json payload file does not exists.\n");
    } else {
        jsonFile.open(QIODevice::ReadOnly);
        ioDeviceList = transformPayload.parseIODevices(jsonFile.readAll());

        // ASSERT
        QVERIFY(!ioDeviceList.isEmpty());
    }
}

void TransformPayloadTest::parseProximity()
{
    // ARRANGE
    TransformPayload transformPayload;
    QVector<IODevice *> ioDeviceList;
    QFile jsonFile(":/payload/proximityStates.json");

    // ACT
    if(!jsonFile.exists()) {
        QVERIFY2(false, "Json payload file does not exists.\n");
    } else {
        jsonFile.open(QIODevice::ReadOnly);
        ioDeviceList = transformPayload.parseIODevices(jsonFile.readAll());

        // ASSERT
        QVERIFY(!ioDeviceList.isEmpty());
    }
}
void TransformPayloadTest::cleanupTestCase() {
}

QTEST_APPLESS_MAIN(TransformPayloadTest)