#ifndef BSF_MAINWINDOW_H
#define BSF_MAINWINDOW_H

#include <memory>

#include <QtWidgets>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>

#include <appservice.prepare.recipe/preparerecipeappservice.h>
#include <appservice.mix.recipe/mixrecipeappservice.h>
#include <appservice.broker/broker.appservice.h>

namespace Ui {
class MainWindow;
}

class QAction;
class QMenu;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService,
                      std::shared_ptr<appservice::MixRecipeAppService> &mixRecipeAppService,
                      std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                      QWidget *parent = nullptr);
  virtual ~MainWindow();
  void showSidebar();
  void showStart();

 private:
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;
  std::shared_ptr<appservice::MixRecipeAppService> mixRecipeAppService;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;

  Ui::MainWindow *ui;

  void createRelayTreeView();
  void createProximityTreeView();
  void createStateWidget();
  void createGroupBoxBinLift();
  void createGroupBoxBinLoadDrop();
  void createGroupBoxFeedersAndBelt();
  void createGroupBoxRecipeConfiguration();
  void createGroupBoxBinRecipeStatus();

};

#endif //BSF_MAINWINDOW_H
