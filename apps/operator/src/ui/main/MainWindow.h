#ifndef BSF_MAINWINDOW_H
#define BSF_MAINWINDOW_H

namespace Ui
{
class MainWindow;
}

#include "ui_mainwindow.h"
#include <MqttClient.h>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QTreeWidget>

class QAction;
class QMenu;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void onCreateMqttClientSubscriptions();

private:
    Ui::MainWindow *ui;
    MqttClient *m_client = nullptr;
    QWidget *relayTreeWidget = nullptr;
    QWidget *proximityTreeWidget = nullptr;
    QWidget *groupBoxLiftUpDown = nullptr;
    QWidget *groupBoxBinLoadDrop = nullptr;
    QWidget *groupBoxBeltFeeders = nullptr;
    QWidget *groupBoxRecipeConfig = nullptr;
    QWidget *groupBoxBinRecipeStatus = nullptr;

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
