#include "ui_groupboxrecipeconfig.h"
#include "GroupBoxRecipeConfig.h"

#include <QTableWidgetItem>

using namespace appservice;

GroupBoxRecipeConfig::GroupBoxRecipeConfig(std::shared_ptr<BrokerAppService> &_brokerAppService,
                                           std::shared_ptr<appservice::PrepareRecipeAppService> &_prepareRecipeAppService,
                                           QWidget *parent) :
    ui(new Ui::GroupBoxRecipeConfig),
    brokerAppService(_brokerAppService),
    prepareRecipeAppService(_prepareRecipeAppService),
    QWidget(parent) {
  ui->setupUi(this);

  init();
}

GroupBoxRecipeConfig::~GroupBoxRecipeConfig() {
  delete ui;
}

void GroupBoxRecipeConfig::init() {
  connect(ui->pushButtonPublishRecipe, &QPushButton::clicked,
          this, &GroupBoxRecipeConfig::onClickButtonPublishRecipe);

  createRecipeComboBox();
}

void GroupBoxRecipeConfig::createRecipeComboBox() {
  QVector<Recipe> recipeList = prepareRecipeAppService->recipes();

  connect(ui->comboBoxSelectRecipe, SIGNAL(currentIndexChanged(int)),
          this, SLOT(onChangeRecipeComboBox(int)));

  for (int i = 0; i < recipeList.size(); ++i) {
    ui->comboBoxSelectRecipe->insertItem(i, recipeList.at(i).getDescription(), recipeList.at(i).getId());
  }
}

void GroupBoxRecipeConfig::onChangeRecipeComboBox(int index) {
  QVariant recipeId = ui->comboBoxSelectRecipe->itemData(index, Qt::UserRole);
  selectedRecipe = prepareRecipeAppService->recipeWithComponents(recipeId.toInt());

  if (selectedRecipe.getId() != 0) {
    createRecipeComponentsTable();
  }
}

void GroupBoxRecipeConfig::createRecipeComponentsTable() {
  if (ui->tableWidgetRecipeComponents->rowCount() > 0) {
    ui->tableWidgetRecipeComponents->setRowCount(0);
  }

  if (ui->tableWidgetRecipeComponents->columnCount() == 0) {
    auto headers = QStringList() << "Component" << "Target" << "Margin %";
    ui->tableWidgetRecipeComponents->setColumnCount(headers.size());
    ui->tableWidgetRecipeComponents->setHorizontalHeaderLabels(headers);
    ui->tableWidgetRecipeComponents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }

  for (int i = 0; i < selectedRecipe.componentList.size(); ++i) {
    const auto &comp = selectedRecipe.componentList.at(i);
    ui->tableWidgetRecipeComponents->insertRow(i);

    auto tableWidgetItem = new QTableWidgetItem(comp.getComponent(), Qt::DisplayRole);
    tableWidgetItem->setData(Qt::UserRole, comp.getComponentId());

    ui->tableWidgetRecipeComponents->setItem(i, 0, tableWidgetItem);

    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getTargetWeight()), Qt::DisplayRole);
    tableWidgetItem->setTextAlignment(Qt::AlignRight);
    ui->tableWidgetRecipeComponents->setItem(i, 1, tableWidgetItem);

    tableWidgetItem = new QTableWidgetItem(QString::number(comp.getMarginValue()), Qt::DisplayRole);
    tableWidgetItem->setTextAlignment(Qt::AlignRight);
    ui->tableWidgetRecipeComponents->setItem(i, 2, tableWidgetItem);
  }
}

void GroupBoxRecipeConfig::onClickButtonPublishRecipe() {
  brokerAppService->configureRecipe(selectedRecipe.getId(),
                                    selectedRecipe.componentList.first().getComponentId(),
                                    selectedRecipe.componentList.first().getTargetWeight());
}
