#include "ui_groupboxrecipeconfig.h"
#include "GroupBoxRecipeConfig.h"
#include <reciperepo.h>
#include <BsfWidgetEnum.h>

GroupBoxRecipeConfig::GroupBoxRecipeConfig(MqttClient *_m_client) :
    m_client(_m_client), ui(new Ui::GroupBoxRecipeConfig) {
  ui->setupUi(this);

  QVariant formId = WIDGET_TYPES::GROUPBOX_RECIPE_CONFIG;
  this->setProperty("formId", formId);

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
  RecipeRepository recipeRepository;
  QVector<Recipe> recipeList = recipeRepository.getRecipes();

  connect(ui->comboBoxSelectRecipe, SIGNAL(currentIndexChanged(int)),
          this, SLOT(onChangeRecipeComboBox(int)));

  for (int i = 0; i < recipeList.size(); ++i) {
    ui->comboBoxSelectRecipe->insertItem(i, recipeList.at(i).getDescription(), recipeList.at(i).getId());
  }
}

void GroupBoxRecipeConfig::onChangeRecipeComboBox(int index) {
  RecipeRepository recipeRepository;
  QVariant recipeId = ui->comboBoxSelectRecipe->itemData(index, Qt::UserRole);
  selectedRecipe = recipeRepository.getRecipeWithComponents(recipeId.toInt());

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
  m_client->publishRecipe(selectedRecipe);
}
