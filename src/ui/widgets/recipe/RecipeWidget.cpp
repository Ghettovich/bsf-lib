#include "ui_recipewidget.h"
#include "RecipeWidget.h"

#include <recipe/recipe.h>

using namespace appservice;

RecipeWidget::RecipeWidget(std::shared_ptr<PrepareRecipeAppService> &_recipeAppService, QWidget *parent) :
    ui(new Ui::RecipeWidget),
    prepareRecipeAppService(_recipeAppService),
    QWidget(parent) {
  ui->setupUi(this);

  createComboBox();

  QObject::connect(ui->lineEditBasalt, &QLineEdit::editingFinished, this, &RecipeWidget::onFinishEditingBasalt);
  QObject::connect(ui->lineEditSand, &QLineEdit::editingFinished, this, &RecipeWidget::onFinishEditingSand);
  QObject::connect(ui->doubleSpinBoxMaterialCementRatio, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                   this, &RecipeWidget::onChangeSpinboxMaterialCement);
  QObject::connect(ui->doubleSpinBoxWaterCement, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                   this, &RecipeWidget::onChangeSpinboxWaterCement);
  QObject::connect(ui->doubleSpinBoxPlastifierCementRatio, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                   this, &RecipeWidget::onChangeSpinboxPlastifierCement);
  QObject::connect(ui->spinBoxPigmentCementRatio, QOverload<int>::of(&QSpinBox::valueChanged),
                   this, &RecipeWidget::onChangeSpinboxPigmentCement);
}
RecipeWidget::~RecipeWidget() {
  delete ui;
}
void RecipeWidget::createComboBox() {
  auto recipes = prepareRecipeAppService->recipes();

  QObject::connect(ui->comboBoxRecipe, QOverload<int>::of(&QComboBox::currentIndexChanged),
                   this, &RecipeWidget::onChangeRecipeComboBox);

  for (int i = 0; i < recipes.size(); ++i) {
    ui->comboBoxRecipe->insertItem(i, recipes.at(i).getTitle(), recipes.at(i).getId());
  }
}
void RecipeWidget::fillForm() {
  ui->plainTextEditRecipe->setPlainText(selectedRecipe->getDescription());

  ui->lineEditBasalt->setText(QString::number(selectedRecipe->getMaterialByName("basalt 0-8").getWeight(), 10, 2));
  ui->lineEditSand->setText(QString::number(selectedRecipe->getMaterialByName("sand 0-2").getWeight(), 10, 2));

  ui->lineEditCement->setText(QString::number(selectedRecipe->getComponentByName("cement").getWeight(), 10, 2));
  ui->doubleSpinBoxMaterialCementRatio->setValue(selectedRecipe->getComponentByName("cement").getRatio());

  ui->doubleSpinBoxWaterCement->setValue(selectedRecipe->getComponentByName("water").getRatio());
  ui->doubleSpinBoxPlastifierCementRatio->setValue(selectedRecipe->getComponentByName("plastifier").getRatio());
  ui->spinBoxPigmentCementRatio->setValue((int)selectedRecipe->getComponentByName("pigment").getRatio());

  ui->lineEditWater->setText(QString::number(selectedRecipe->getComponentByName("water").getWeight(), 10, 2));
  ui->lineEditPlastifier->setText(QString::number(selectedRecipe->getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lineEditPigment->setText(QString::number(selectedRecipe->getComponentByName("pigment").getWeight(), 10, 2));
  ui->lcdNumberRecipeWeight->display(selectedRecipe->calculateRecipeTotalWeight());
}
void RecipeWidget::updateMaterialCement(double basaltWeight, double sandWeight, double ratio) {
  double weight = (basaltWeight + sandWeight) * ratio;
  selectedRecipe->updateComponentByName("cement", weight);
  ui->lineEditCement->setText(QString::number(selectedRecipe->getComponentByName("cement").getWeight(), 10, 2));
  ui->lcdNumberRecipeWeight->display(selectedRecipe->calculateRecipeTotalWeight());
}
void RecipeWidget::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if(recipeId != 0) {
    selectedRecipe = prepareRecipeAppService->recipeMaterials(recipeId);
    fillForm();
  }
}
void RecipeWidget::onFinishEditingBasalt() {
  bool succes = false;
  double basaltWeight = ui->lineEditBasalt->text().toDouble(&succes);
  double sandWeight = ui->lineEditSand->text().toDouble(&succes);
  double ratio =ui->doubleSpinBoxMaterialCementRatio->value();

  if(succes) {
    selectedRecipe->updateMaterialByName("basalt 0-8", basaltWeight);
    updateMaterialCement(basaltWeight, sandWeight, ratio);
  } else {
    qWarning() << "Failed to convert value in form";
  }
}
void RecipeWidget::onFinishEditingSand() {
  bool succes = false;
  double basaltWeight = ui->lineEditBasalt->text().toDouble(&succes);
  double sandWeight = ui->lineEditSand->text().toDouble(&succes);
  double ratio =ui->doubleSpinBoxMaterialCementRatio->value();

  if(succes) {
    selectedRecipe->updateMaterialByName("sand 0-2", sandWeight);
    updateMaterialCement(basaltWeight, sandWeight, ratio);
  } else {
    qWarning() << "Failed to convert value in form";
  }
}
void RecipeWidget::onChangeSpinboxMaterialCement(double value) {
  bool succes = false;
  double basaltWeight = ui->lineEditBasalt->text().toDouble(&succes);
  double sandWeight = ui->lineEditSand->text().toDouble(&succes);

  if(succes) {
    selectedRecipe->updateComponentRatio("cement", value);
    updateMaterialCement(basaltWeight, sandWeight, value);
  } else {
    qWarning() << "Failed to convert value in form";
  }
}
void RecipeWidget::onChangeSpinboxWaterCement(double value) {
  double waterWeight = value * selectedRecipe->getComponentByName("cement").getWeight();
  selectedRecipe->updateComponentByName("water", waterWeight);
  ui->lineEditWater->setText(QString::number(selectedRecipe->getComponentByName("water").getWeight(), 10, 2));
  ui->lcdNumberRecipeWeight->display(selectedRecipe->calculateRecipeTotalWeight());
}
void RecipeWidget::onChangeSpinboxPlastifierCement(double value) {
  double plastifierWeight = value * selectedRecipe->getComponentByName("cement").getWeight();
  selectedRecipe->updateComponentByName("plastifier", plastifierWeight);
  ui->lineEditPlastifier->setText(QString::number(selectedRecipe->getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lcdNumberRecipeWeight->display(selectedRecipe->calculateRecipeTotalWeight());
}
void RecipeWidget::onChangeSpinboxPigmentCement(int value) {
  double pigmentWeight = (selectedRecipe->getComponentByName("cement").getWeight() * value) / 100;
  selectedRecipe->updateComponentByName("pigment", pigmentWeight);
  ui->lineEditPigment->setText(QString::number(selectedRecipe->getComponentByName("pigment").getWeight(), 10, 2));
  ui->lcdNumberRecipeWeight->display(selectedRecipe->calculateRecipeTotalWeight());
}