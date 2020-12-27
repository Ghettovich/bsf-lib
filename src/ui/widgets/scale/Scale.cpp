#include "ui_scale.h"
#include "Scale.h"
#include <reciperepo.h>
#include <weightcensor.h>
#include <BsfWidgetEnum.h>
#include <QMessageBox>
#include <QErrorMessage>

Scale::Scale(MqttClient *_m_client) :
    ui(new Ui::Scale), m_client(_m_client) {
  ui->setupUi(this);
  QVariant formId = WIDGET_TYPES::SCALE_1;
  this->setProperty("formId", formId);

  weightSensor = new WeightSensor(1, IODevice::LOW);
  activeComponentTableWidget = new QTableWidgetItem;

  init();
}

Scale::~Scale() {
  delete ui;
}

void Scale::init() {
  ui->pushButtonTareScale->setIcon(material.syncProblemIcon());
  connect(ui->pushButtonTareScale, &QPushButton::clicked, this, &Scale::onClickPushButtonTare);

  ui->pushButtonConfirmRecipe->setIcon(material.updateDisabledIcon());
  connect(ui->pushButtonClearRecipe, &QPushButton::clicked, this, &Scale::onClickPushButtonClearRecipe);

  ui->pushButtonConfirmRecipe->setDisabled(true);
  ui->pushButtonConfirmRecipe->setIcon(material.updateDisabledIcon());
  connect(ui->pushButtonConfirmRecipe, &QPushButton::clicked, this, &Scale::onClickPushButtonConfirmRecipe);
}

void Scale::onUpdateIODevice(const WeightSensor *sensor) {
  if (sensor->getId() == weightSensor->getId()) {
    if(sensor->getComponent().getRecipeId() == 0 || sensor->getComponent().getComponentId() == 0) {
      activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
      ui->pushButtonTareScale->setIcon(material.syncProblemIcon());
      setQLcdNumberDisplay();
      isTareActive = true;
      emit scaleInTareMode(true);
      return;
    }

    else if (sensor->getComponent().getRecipeId() != configuredRecipe.getId()) {
      RecipeRepository recipeRepository;
      configuredRecipe = recipeRepository.getRecipeWithComponents(sensor->getComponent().getRecipeId());
      createRecipeComponentTableWidget();
    }

    if (activeComponent.getComponentId() != sensor->getComponent().getComponentId() ||
        sensor->getComponent().getRecipeId() != activeComponent.getRecipeId()) {

      for (const auto &comp: configuredRecipe.componentList) {
        if (comp.getComponentId() == sensor->getComponent().getComponentId()) {
          activeComponent.setComponentId(sensor->getComponent().getComponentId());
          activeComponent.setRecipeId(sensor->getComponent().getRecipeId());
          activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
          break;
        }
      }

      updateComponentWidgetTable();

    } else if (activeComponent.getComponentId() == sensor->getComponent().getComponentId()) {
      activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
      configuredRecipe.updateComponentWeight(activeComponent.getComponentId(), activeComponent.getCurrentWeight());
      activeComponentTableWidget->setText(QString::number(activeComponent.getCurrentWeight()));
    }

    setQLcdNumberDisplay();
    setPushButtonConfirmRecipe();

    // SIGNALS
    emit receivedComponent(activeComponent);
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
  if(configuredRecipe.isRecipeTargetMet()) {
    ui->pushButtonConfirmRecipe->setIcon(material.updateIcon());
    ui->pushButtonConfirmRecipe->setDisabled(false);
  } else {
    ui->pushButtonConfirmRecipe->setIcon(material.updateDisabledIcon());
    ui->pushButtonConfirmRecipe->setDisabled(true);
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
  if(!isTareActive) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Tare scale"),
                                  "Reset scale and tare scale?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
      m_client->publishTareScale(false);
    }
  }
  else {
    isTareActive = false;
    emit scaleInTareMode(false);
    m_client->publishTareScale(true);
  }
}

void Scale::onClickPushButtonClearRecipe() {

}

void Scale::onClickPushButtonConfirmRecipe() {

}
