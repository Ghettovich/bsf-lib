#include <MqttClient.h>
#include <widgets/interfaces/IOWidgetStatusInterface.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include <QFile>
#include <QSignalSpy>
#include "tst_GroupBoxBinLoadDrop.h"

DECLARE_TEST_GROUPBOX_BINLOADDROP(GroupBoxBinLoadDropTest)

void GroupBoxBinLoadDropTest::initTestCase() {
}

void GroupBoxBinLoadDropTest::testCustomSignal() {
  auto parent = new QObject;
  MqttClient object(parent);
  auto mo = object.metaObject();

  qRegisterMetaType<QVector<IODevice *>>();
  auto signalIndex = mo->indexOfSignal("newIODeviceStates(QVector<IODevice*>)");
  auto signal = mo->method(signalIndex);

  QSignalSpy spy(&object, signal);
  QMqttTopicName topic("/relay/states");

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  object.onMessageReceived(jsonFile.readAll(), topic);
  QCOMPARE(spy.count(), 1);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void GroupBoxBinLoadDropTest::cleanupTestCase() {

}
