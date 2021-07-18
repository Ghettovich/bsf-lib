#ifndef BSF_MAINWINDOW_H
#define BSF_MAINWINDOW_H

#include <memory>

#include <QtWidgets>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QTabWidget>

#include <appservice.prepare.recipe/PrepareRecipeAppService.h>
#include <appservice.mix.recipe/MixRecipeAppService.h>
#include <appservice.broker/BrokerAppService.h>


namespace Ui {
class MainWindow;
}

class QAction;
class QMenu;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService
                      , std::shared_ptr<appservice::MixRecipeAppService> &mixRecipeAppService
                      , std::shared_ptr<appservice::BrokerAppService> &brokerAppService
                      , QWidget *parent = nullptr);
  virtual ~MainWindow();
  void showSidebar();
  void showStart();

 public slots:
  void onCreateMqttClientSubscriptions();

 private:
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;
  std::shared_ptr<appservice::MixRecipeAppService> mixRecipeAppService;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;

  Ui::MainWindow *ui;
  QTabWidget *getApplicationTabWidget();

  void createRelayTreeView();
  void createProximityTreeView();
  void createArduinoTreeView();
  void createClientsTreeView();
  void createClientDescriptions();
  void createGroupBoxBinLift();
  void createGroupBoxBinLoadDrop();
  void createGroupBoxFeedersAndBelt();
  void createGroupBoxRecipeConfiguration();
  void createGroupBoxBinRecipeStatus();
  void createMqttClientWindow();

};

#endif //BSF_MAINWINDOW_H
