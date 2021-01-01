#ifndef BSF_LIB_TEST_UI_WIDGETS_TST_SCALE_H_
#define BSF_LIB_TEST_UI_WIDGETS_TST_SCALE_H_

#include <QtTest/QTest>
#include <QtCore/QObject>
#include <MqttClient.h>

class ScaleTest : public QObject {
 Q_OBJECT

 private:
  const QString host = "192.168.178.5";
  MqttClient *m_client = new MqttClient(this, host);

 private slots:
  void init();
  void isActiveComponentEmitted();
  void isComponentSelectionChanged();
  void cleanupTestCase();

};

#endif //BSF_LIB_TEST_UI_WIDGETS_TST_SCALE_H_
