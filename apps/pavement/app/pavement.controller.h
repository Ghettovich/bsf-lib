#ifndef CONTROLLER_PAVEMENTCONTROLLER_H_
#define CONTROLLER_PAVEMENTCONTROLLER_H_

#include <QObject>
#include <QtWidgets/QLayout>
#include <QtWidgets/QStackedWidget>

class PavementController : public QObject {
 Q_OBJECT

 public:
  explicit PavementController(QObject *parent = nullptr);
  void createStackedWidget(QLayout *layout);
  void updateCurrentWidget(int widgetNr);

 private:
  QStackedWidget *stackedWidget = nullptr;

};

#endif //CONTROLLER_PAVEMENTCONTROLLER_H_
