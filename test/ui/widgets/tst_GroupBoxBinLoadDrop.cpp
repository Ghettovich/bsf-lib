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
  qRegisterMetaType<QVector<IODevice *>>();
  auto object = new MqttClient(this);

  QSignalSpy spy(object, SIGNAL(newIODeviceStates(const QVector<IODevice *>)));
  QMqttTopicName topic("/relay/states");

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  object->onMessageReceived(jsonFile.readAll(), topic);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void GroupBoxBinLoadDropTest::cleanupTestCase() {

}
