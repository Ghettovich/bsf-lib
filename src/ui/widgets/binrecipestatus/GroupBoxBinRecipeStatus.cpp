#include "ui_groupboxbinrecipestatus.h"
#include "GroupBoxBinRecipeStatus.h"

#include <iodevice/weightcensor.h>

using namespace appservice;

GroupBoxBinRecipeStatus::GroupBoxBinRecipeStatus(std::shared_ptr<appservice::PrepareRecipeAppService> &_prepareRecipeAppService,
                                                 QWidget *parent) :
    ui(new Ui::GroupBoxBinRecipeStatus),
    prepareRecipeAppService(_prepareRecipeAppService),
    QWidget(parent) {
  ui->setupUi(this);

  connect(prepareRecipeAppService.get(), &PrepareRecipeAppService::recipeSelectionUpdated,
          this, &GroupBoxBinRecipeStatus::onRecipeSelectionUpdated);

  connect(prepareRecipeAppService.get(), &PrepareRecipeAppService::componentSelectionUpdated,
          this, &GroupBoxBinRecipeStatus::onUpdateComponentSelection);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("weightsensor");

  scale1 = std::make_unique<WeightSensor>(settings->value("weightbinload").toInt(), IODevice::LOW);

  settings->endGroup();

  ui->label->setText("No recipe known");
}

GroupBoxBinRecipeStatus::~GroupBoxBinRecipeStatus() {
  delete ui;
}

void GroupBoxBinRecipeStatus::onRecipeSelectionUpdated(const std::shared_ptr<RecipeSelection> &selection) {
  qDebug() << "recipe description = " << selection->getRecipeDescription();
  qDebug() << "recipe id = " << selection->getSelectedRecipeId();

  ui->label->setText(selection->getRecipeDescription());
  createRecipeComponentTableWidget(selection->getComponents(), selection->getSelectedComponentId());
}

void GroupBoxBinRecipeStatus::onUpdateComponentSelection(const std::shared_ptr<RecipeSelection> &selection) {
  qDebug() << "component id = " << selection->getSelectedComponentId();
  qDebug() << "current weight = " << selection->getSelectedComponent().getCurrentWeight();

  if(selection->getSelectedComponentId() == activeComponentTableWidget->data(Qt::UserRole).toInt()) {
    activeComponentTableWidget->setData(Qt::DisplayRole, selection->getSelectedComponent().getCurrentWeight());
    qDebug() << "updated component";
  }
  else {
    updateComponentWidgetTable(selection->getSelectedComponent());
    qDebug() << "updated component widget table";
  }

  setQLcdNumberDisplay(selection->getSelectedComponent().getCurrentWeight());
}

void GroupBoxBinRecipeStatus::createRecipeComponentTableWidget(const QVector<Component> &components, int componentId) {
  if (ui->tableWidget->rowCount() > 0) {
    ui->tableWidget->setRowCount(0);
  }

  if (ui->tableWidget->columnCount() == 0) {
    auto headers = QStringList() << "Component" << "Target" << "Current" << "Margin %";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }

  for (int i = 0; i < components.size(); ++i) {
    const auto &comp = components.at(i);
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

    if (comp.getComponentId() == componentId) {
      activeComponentTableWidget = tableWidgetItem;
    }
  }
}

void GroupBoxBinRecipeStatus::setQLcdNumberDisplay(int value) {
  ui->lcdNumberBinRecipeWeight->display(value);
}

void GroupBoxBinRecipeStatus::updateComponentWidgetTable(const Component &component) {
  int currentWeightColumn = 2;

  for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

    if (ui->tableWidget->item(i, 0)->data(Qt::UserRole).toInt() == component.getComponentId()) {
      activeComponentTableWidget = ui->tableWidget->item(i, currentWeightColumn);
      activeComponentTableWidget->setData(Qt::UserRole, component.getComponentId());
      activeComponentTableWidget->setData(Qt::DisplayRole, component.getCurrentWeight());
      break;
    }
  }
}