#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
  controller = std::make_unique<PavementController>();
  controller->createStackedWidget(ui->verticalLayoutMain);

  connect(ui->pushButtonHome, &QPushButton::clicked, this, &MainWindow::onShowStart);
  connect(ui->pushButtonNewMixture, &QPushButton::clicked, this, &MainWindow::onShowNewMixture);
  connect(ui->pushButtonExperimental, &QPushButton::clicked, this, &MainWindow::onShowExperimental);
  connect(ui->pushButtonRecipes, &QPushButton::clicked, this, &MainWindow::onShowRecipes);
}

MainWindow::~MainWindow() {
  delete ui;
}
void MainWindow::onShowStart() {
  controller->updateCurrentWidget(0);
}
void MainWindow::onShowNewMixture() {
  controller->updateCurrentWidget(1);
}
void MainWindow::onShowExperimental() {
  controller->updateCurrentWidget(2);
}
void MainWindow::onShowRecipes() {
  controller->updateCurrentWidget(3);
}
void MainWindow::onShowLogs() {
  controller->updateCurrentWidget(4);
}
