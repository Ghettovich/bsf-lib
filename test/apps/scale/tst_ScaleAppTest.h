#ifndef BSF_LIB_TEST_APPS_SCALE_TST_SCALEAPPTEST_H_
#define BSF_LIB_TEST_APPS_SCALE_TST_SCALEAPPTEST_H_

#include <QtTest/QTest>
#include <QtCore/QObject>
#include <MqttClient.h>

class ScaleAppTest : public QObject {
 Q_OBJECT

 private:
  const QString host = "192.168.178.5";
  MqttClient *m_client;

 private
  slots:
  void init();
  void configureScaleWithPayload();
  void updateWidgetComponentSelectionChanged();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_APPS_SCALE_TST_SCALEAPPTEST_H_
