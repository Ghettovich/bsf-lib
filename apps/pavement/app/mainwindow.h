#ifndef PAVEMENT_APP_MAINWINDOW_H_
#define PAVEMENT_APP_MAINWINDOW_H_

#include "pavement.controller.h"

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
  void onShowNewMixture();
  void onShowExperimental();
  void onShowRecipes();
  void onShowLogs();

 private:
  Ui::MainWindow *ui;
  std::unique_ptr<PavementController> controller;
};

#endif //PAVEMENT_APP_MAINWINDOW_H_
