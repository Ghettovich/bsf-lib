#ifndef BSF_LIB_TEST_UI_WIDGETS_STATUSRELAYS_TST_RELAYTREEWIDGETSTATUS_H_
#define BSF_LIB_TEST_UI_WIDGETS_STATUSRELAYS_TST_RELAYTREEWIDGETSTATUS_H_

#include <QtTest/QTest>
#include <QtCore/QObject>
#include <MqttClient.h>

class RelayTreeWidgetTest : public QObject {
 Q_OBJECT

 private:
  const QString host = "192.168.178.5";
  MqttClient *m_client;

 private slots:
  void init();
  void isRelayToggledForWidget();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_UI_WIDGETS_STATUSRELAYS_TST_RELAYTREEWIDGETSTATUS_H_
