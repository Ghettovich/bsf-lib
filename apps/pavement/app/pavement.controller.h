#ifndef CONTROLLER_PAVEMENTCONTROLLER_H_
#define CONTROLLER_PAVEMENTCONTROLLER_H_

#include <QObject>
#include <QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QStackedWidget>

#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.ui/ui.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

#include <widgets/tabwidget/TabwidgetCreateBatch.h>

class PavementController : public QObject {
 Q_OBJECT

 public:
  explicit PavementController(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                              std::shared_ptr<appservice::PrepareRecipeAppService> &recipeAppService,
                              std::shared_ptr<appservice::UiAppService> &uiAppService,
                              QObject *parent = nullptr);
  void createStackedWidget(QLayout *layout);
  void updateCurrentWidget(int widgetNr);

 private:
  QStackedWidget *stackedWidget = nullptr;
  TabWidgetCreateBatch *tabWidgetCreateBatch = nullptr;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> recipeAppService;
  std::shared_ptr<appservice::UiAppService> uiAppService;
};

#endif //CONTROLLER_PAVEMENTCONTROLLER_H_
