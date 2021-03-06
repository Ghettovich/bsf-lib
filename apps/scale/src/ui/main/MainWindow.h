#ifndef MAINWINDOW_H
#define MAINWINDOW_H

namespace Ui {
class MainWindow;
}

#include "ui_mainwindow.h"
#include <recipe.h>
#include <MqttClient.h>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QtWidgets/QWidget>
#include <QTreeWidgetItem>
#include <fonts/MaterialRegular.h>

class QAction;
class QMenu;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  explicit MainWindow(MqttClient *m_client, QWidget *parent = nullptr);
  virtual ~MainWindow();

 private:
  Ui::MainWindow *ui;
  MaterialRegular materialRegular;
  MqttClient *m_client = nullptr;
  QStatusBar *mainStatusBar = nullptr;
  QWidget *scale = nullptr;
  Recipe selectedRecipe = Recipe(0);
  Recipe configuredRecipe = Recipe(0);
  Component activeComponent = Component(0);
  QTreeWidgetItem *activeCompTreeWidgetItem = nullptr;

  void init();
  void createStatusBar();
  void createScale_1_Widget();
  void createRecipeTreeWidget();
  void createComponentsListWidget(const Recipe &recipe);
  void setChangeRecipeButtonState(bool isRecipeIdEqual);
  void setConfirmComponentButtonState();
  void setActiveComponentTreeWidgetTargetsMet(QTreeWidgetItem *item);
  void selectItemInTreeWidgetWithId(QTreeWidget *treeWidget, int id);
  void selectItemInTreeWidget(QTreeWidget *widget, bool down);
  void updateRecipeComponentsTable(const Component &component);


 public slots:
  void onClickPushButtonRecipeDown();
  void onClickPushButtonRecipeUp();
  void onClickPushButtonChangeRecipe();
  void onClickPushButtonComponentDown();
  void onClickPushButtonComponentUp();
  void onClickPushButtonConfirmComponent();
  void onComponentTreeWidgetSelectionChanged();
  void onCreateMqttClientSubscriptions();
  void onRecipeTreeWidgetChanged();
  void onReceivedConfiguredComponent(const Component &component);
  void onReceivedChangeIsScaleInTareMode(bool isInTareMode);
  void onReceivedTimeOutOccured(IODevice::IO_DEVICE_HIGH_LOW state);

};
#endif // MAINWINDOW_H
