#ifndef BSF_LIB_TEST_UI_WIDGETS_TST_GROUPBOXBINLOADDROP_H_
#define BSF_LIB_TEST_UI_WIDGETS_TST_GROUPBOXBINLOADDROP_H_

#include <QtTest/QTest>
#include <QtCore/QObject>

class IOWidgetStatusInterfaceTest : public QObject {
 Q_OBJECT

 private
  slots:
  void initTestCase();
  void isProximityUpdatedForWidget();
  void isRelayToggledForWidget();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_UI_WIDGETS_TST_GROUPBOXBINLOADDROP_H_
