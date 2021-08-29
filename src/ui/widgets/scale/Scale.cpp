#include "ui_scale.h"
#include "Scale.h"

#include <iodevice/weightcensor.h>
#include <QMessageBox>

using namespace appservice;

Scale::Scale(std::shared_ptr<BrokerAppService> &_brokerAppService,
             std::shared_ptr<appservice::PrepareRecipeAppService> &_prepareRecipeAppService,
             QWidget *parent) :
    ui(new Ui::Scale),
    brokerAppService(_brokerAppService),
    prepareRecipeAppService(_prepareRecipeAppService),
    QWidget(parent) {
  ui->setupUi(this);

//  connect(brokerAppService.get(), &BrokerAppService::updateDeviceWithState, this, &Scale::onUpdateIODevice);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("weightsensor");

  weightSensor = std::make_unique<WeightSensor>(settings->value("weightcomponent").toInt(), IODevice::LOW);

  settings->endGroup();

  activeComponentTableWidget = new QTableWidgetItem;
  ui->progressBar->setValue(0);
  ui->progressBar->setRange(0, 100);

  init();
}

Scale::~Scale() {
  delete ui;
}

void Scale::init() {
  //ui->pushButtonTareScale->setIcon(material.syncProblemIcon());
  connect(ui->pushButtonTareScale, &QPushButton::clicked, this, &Scale::onClickPushButtonTare);

  ui->pushButtonConfirmRecipe->setDisabled(true);
  //ui->pushButtonConfirmRecipe->setIcon(material.updateDisabledIcon());
  connect(ui->pushButtonConfirmRecipe, &QPushButton::clicked, this, &Scale::onClickPushButtonConfirmRecipe);

  connect(this, &Scale::scaleTimeOutOccured,
          this, &Scale::onScaleTimeOutOccured);
}

void Scale::onUpdateIODevice(IODevice *sensor) {
  auto device = sensor;

  auto scale = dynamic_cast<WeightSensor*>(device);

  qDebug() << "device id = " << scale->getId();


//  IODevice *test;
//
//  WeightSensor sensorTest(1, IODevice::LOW);
//
//  auto *sensorTest2 = (WeightSensor*)(test);
//
//
//  if (sensor->getId() == weightSensor->getId()) {
//    weightSensor->setDeviceState(sensor->getDeviceState());
//
//    if (sensor->getComponent().getRecipeId() == 0 || sensor->getComponent().getComponentId() == 0) {
//      activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
//      ui->pushButtonTareScale->setIcon(material.syncProblemIcon());
//      setQLcdNumberDisplay();
//      isTareActive = true;
//      emit scaleInTareMode(true);
//      return;
//    } else if (sensor->getComponent().getRecipeId() != configuredRecipe.getId()) {
//      configuredRecipe = prepareRecipeAppService->recipeWithComponents(sensor->getComponent().getRecipeId());
//      createRecipeComponentTableWidget();
//    }
//
//    if (activeComponent.getComponentId() != sensor->getComponent().getComponentId() ||
//        sensor->getComponent().getRecipeId() != activeComponent.getRecipeId()) {
//
//      activeComponent = configuredRecipe.getComponent(sensor->getComponent().getComponentId());
//      activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
//
//      updateComponentWidgetTable();
//
//    } else if (activeComponent.getComponentId() == sensor->getComponent().getComponentId()) {
//      activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
//      configuredRecipe.updateComponentWeight(activeComponent.getComponentId(), activeComponent.getCurrentWeight());
//      activeComponentTableWidget->setText(QString::number(activeComponent.getCurrentWeight()));
//
//      if (activeComponent.isTargetMet()) {
//        activeComponentTableWidget->setData(Qt::ForegroundRole, QColor(Qt::green));
//      } else {
//        activeComponentTableWidget->setData(Qt::ForegroundRole, QColor(Qt::white));
//      }
//    }
//
//    setQLcdNumberDisplay();
//    setPushButtonConfirmRecipe();
//    setRecipeProgressBar();
//
//    // SIGNALS
//    emit receivedComponent(activeComponent);
//    emit scaleTimeOutOccured(weightSensor->getDeviceState());
//  }
}

void Scale::onScaleTimeOutOccured(IODevice::IO_DEVICE_HIGH_LOW state) {
  if(state == IODevice::LOW) {
    ui->tableWidget->setDisabled(true);
  } else {
    ui->tableWidget->setDisabled(false);
  }
}

void Scale::createRecipeComponentTableWidget() {
  if (ui->tableWidget->rowCount() > 0) {
    ui->tableWidget->setRowCount(0);
  }

  if (ui->tableWidget->columnCount() == 0) {
    auto headers = QStringList() << "Component" << "Target" << "Current" << "Margin %";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }

  for (int i = 0; i < configuredRecipe.componentList.size(); ++i) {
    const auto &comp = configuredRecipe.componentList.at(i);
    ui->tableWidget->insertRow(i);

    auto tableWidgetItem = new QTableWidgetItem(comp.getComponent(), Qt::DisplayRole);
    tableWidgetItem->setData(Qt::UserRole, comp.getComponentId());

    ui->tableWidget->setItem(i, 0, tableWidgetItem);

    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getTargetWeight()), Qt::DisplayRole);
    tableWidgetItem->setTextAlignment(Qt::AlignRight);
    ui->tableWidget->setItem(i, 1, tableWidgetItem);

    tableWidgetItem = new QTableWidgetItem(QString::number(0), Qt::DisplayRole);
    tableWidgetItem->setTextAlignment(Qt::AlignRight);
    ui->tableWidget->setItem(i, 2, tableWidgetItem);

    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getMarginValue()), Qt::DisplayRole);
    tableWidgetItem->setTextAlignment(Qt::AlignRight);
    ui->tableWidget->setItem(i, 3, tableWidgetItem);

    if (comp.getComponentId() == activeComponent.getComponentId()) {
      activeComponentTableWidget = tableWidgetItem;
    }
  }
}

void Scale::setQLcdNumberDisplay() {
  ui->lcdNumber->display(activeComponent.getCurrentWeight());
}

void Scale::setPushButtonConfirmRecipe() {
  if (configuredRecipe.isRecipeTargetMet()) {
    //ui->pushButtonConfirmRecipe->setIcon(material.updateIcon());
    ui->pushButtonConfirmRecipe->setDisabled(false);
  } else {
    //ui->pushButtonConfirmRecipe->setIcon(material.updateDisabledIcon());
    ui->pushButtonConfirmRecipe->setDisabled(true);
  }
}

void Scale::setRecipeProgressBar() {
  auto totalCurrentWeight = (float)configuredRecipe.getSumOfCurrentWeight();
  auto totalTargetWeight = (float)configuredRecipe.getSumOfTargetWeight();
  auto val = (int)100 * (totalCurrentWeight / totalTargetWeight);

  if((int)val > ui->progressBar->maximum()) {
    ui->progressBar->setValue(ui->progressBar->maximum());
  }
  else {
    ui->progressBar->setValue((int)val);
  }
}

void Scale::updateComponentWidgetTable() {
  for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

    if (ui->tableWidget->item(i, 0)->data(Qt::UserRole).toInt() == activeComponent.getComponentId()) {
      activeComponentTableWidget = ui->tableWidget->item(i, 2);
      activeComponentTableWidget->setData(Qt::UserRole, activeComponent.getComponentId());
      activeComponentTableWidget->setData(Qt::DisplayRole, activeComponent.getCurrentWeight());
      break;
    }
  }
}

void Scale::onClickPushButtonTare() {
  if (!isTareActive) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Tare scale?"),
                                  "Please clear the scale... then proceed.\n\nExpected calibration weight 1kg.",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
      //m_client->publishTareScale(false);
      //ui->pushButtonTareScale->setIcon(material.syncIcon());
    }
  } else {
    isTareActive = false;
    //m_client->publishTareScale(true);
    //ui->pushButtonTareScale->setIcon(material.syncProblemIcon());

    emit scaleInTareMode(false);
  }
}

void Scale::onClickPushButtonConfirmRecipe() {
  //m_client->publishConfirmComponent(activeComponent);
}
