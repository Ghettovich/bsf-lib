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
          this, &GroupBoxBinRecipeStatus::onUpdateIODevice);

  connect(prepareRecipeAppService.get(), &PrepareRecipeAppService::componentSelectionUpdated,
          this, &GroupBoxBinRecipeStatus::onUpdateComponentSelection);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("weightsensor");

  scale1 = std::make_unique<WeightSensor>(settings->value("weightbinload").toInt(), IODevice::LOW);

  settings->endGroup();
}

GroupBoxBinRecipeStatus::~GroupBoxBinRecipeStatus() {
  delete ui;
}

void GroupBoxBinRecipeStatus::onUpdateIODevice(const std::shared_ptr<RecipeSelection> &selection) {

  qDebug() << "recipe description = " << selection->getRecipeDescription();
  qDebug() << "recipe id = " << selection->getSelectedRecipeId();

//  if (scale && scale1->getId() == scale->getId()) {
//    if(scale->getComponent().getComponentId() == 0 || scale->getComponent().getRecipeId() == 0) {
//      // in tare mode
//      return;
//    }
//
//    else if (scale->getComponent().getRecipeId() != selectedRecipe.getId()) {
//      RecipeRepository recipeRepository;
//      selectedRecipe = recipeRepository.getRecipeWithComponents(sensor->getComponent().getRecipeId());
//      createRecipeComponentTableWidget();
//    }
//
//    if (activeComponent.getComponentId() != sensor->getComponent().getComponentId()) {
//      activeComponent = Component(sensor->getComponent().getComponentId(),
//                                  sensor->getComponent().getRecipeId());
//      updateComponentWidgetTable();
//    } else if (activeComponent.getComponentId() == sensor->getComponent().getComponentId()) {
//      activeComponentTableWidget->setData(Qt::UserRole, activeComponent.getComponentId());
//      activeComponentTableWidget->setData(Qt::DisplayRole, activeComponent.getCurrentWeight());
//    }
//
//    activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
//    setQLcdNumberDisplay();
//  }
}

void GroupBoxBinRecipeStatus::createRecipeComponentTableWidget() {
  if (ui->tableWidget->rowCount() > 0) {
    ui->tableWidget->setRowCount(0);
  }

  if (ui->tableWidget->columnCount() == 0) {
    auto headers = QStringList() << "Component" << "Target" << "Current" << "Margin %";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }

//  for (int i = 0; i < selectedRecipe.componentList.size(); ++i) {
//    const auto &comp = selectedRecipe.componentList.at(i);
//    ui->tableWidget->insertRow(i);
//
//    auto tableWidgetItem = new QTableWidgetItem(comp.getComponent(), Qt::DisplayRole);
//    tableWidgetItem->setData(Qt::UserRole, comp.getComponentId());
//
//    ui->tableWidget->setItem(i, 0, tableWidgetItem);
//
//    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getTargetWeight()), Qt::DisplayRole);
//    tableWidgetItem->setTextAlignment(Qt::AlignRight);
//    ui->tableWidget->setItem(i, 1, tableWidgetItem);
//
//    tableWidgetItem = new QTableWidgetItem(QString::number(0), Qt::DisplayRole);
//    tableWidgetItem->setTextAlignment(Qt::AlignRight);
//    ui->tableWidget->setItem(i, 2, tableWidgetItem);
//
//    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getMarginValue()), Qt::DisplayRole);
//    tableWidgetItem->setTextAlignment(Qt::AlignRight);
//    ui->tableWidget->setItem(i, 3, tableWidgetItem);
//
//    if (comp.getComponentId() == activeComponent.getComponentId()) {
//      activeComponentTableWidget = tableWidgetItem;
//    }
//  }
}

void GroupBoxBinRecipeStatus::setQLcdNumberDisplay() {
  //ui->lcdNumberBinRecipeWeight->display(activeComponent.getCurrentWeight());
}

void GroupBoxBinRecipeStatus::updateComponentWidgetTable() {
//  for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
//
//    if (ui->tableWidget->item(i, 0)->data(Qt::UserRole).toInt() == activeComponent.getComponentId()) {
//      activeComponentTableWidget = ui->tableWidget->item(i, 2);
//      activeComponentTableWidget->setData(Qt::UserRole, activeComponent.getComponentId());
//      activeComponentTableWidget->setData(Qt::DisplayRole, activeComponent.getCurrentWeight());
//      break;
//    }
//  }
}
void GroupBoxBinRecipeStatus::onUpdateComponentSelection(const std::shared_ptr<RecipeSelection> &selection) {
  qDebug() << "component id = " << selection->getSelectedComponentId();
  //qDebug() << "component id = " << selection->g();
}
