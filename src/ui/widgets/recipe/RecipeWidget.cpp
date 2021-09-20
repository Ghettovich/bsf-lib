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
  ui->plainTextEditRecipe->setPlainText(selectedRecipe.getDescription());

  ui->lineEditBasalt->setText(QString::number(selectedRecipe.getMaterialByName("basalt 0-8").getWeight(), 10, 2));
  ui->lineEditSand->setText(QString::number(selectedRecipe.getMaterialByName("sand 0-2").getWeight(), 10, 2));

  ui->lineEditCement->setText(QString::number(selectedRecipe.getComponentByName("cement").getWeight(), 10, 2));
  ui->doubleSpinBoxMaterialCementRatio->setValue(selectedRecipe.getComponentByName("cement").getRatio());


  ui->doubleSpinBoxWaterCement->setValue(selectedRecipe.getComponentByName("water").getRatio());
  ui->doubleSpinBoxPlastifierCementRatio->setValue(selectedRecipe.getComponentByName("plastifier").getRatio());
  ui->doubleSpinBoxPigmentCementRatio->setValue(selectedRecipe.getComponentByName("pigment").getRatio());

  ui->lineEditWater->setText(QString::number(selectedRecipe.getComponentByName("water").getWeight(), 10, 2));
  ui->lineEditPlastifier->setText(QString::number(selectedRecipe.getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lineEditPigment->setText(QString::number(selectedRecipe.getComponentByName("pigment").getWeight(), 10, 2));
}
void RecipeWidget::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if(recipeId != 0) {
    selectedRecipe = prepareRecipeAppService->recipeMaterials(recipeId);

    fillForm();
  }
}
