#ifndef PAVEMENT_APP_MAINWINDOW_H_
#define PAVEMENT_APP_MAINWINDOW_H_

#include "pavement.controller.h"

#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.broker/broker.appservice.h>
#include <appservice.ui/ui.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

#include <ui/fonts/MaterialRegular.h>

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow();

 public slots:
  void onShowStart();
  void onShowExperimental();
  void onShowRecipes();
  void onShowLogs();
  void onUpdateRelayListWidget(int deviceId, bool on);
  void onUpdateProximityListWidget(int deviceId, bool on);

 private:
  Ui::MainWindow *ui;
  std::unique_ptr<PavementController> controller;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> recipeAppService;
  std::shared_ptr<appservice::UiAppService> uiAppService;

  MaterialRegular materialRegular;

  void initRelayListWidget();
  void initProximitiesWidget();
};

#endif //PAVEMENT_APP_MAINWINDOW_H_
