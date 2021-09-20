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

  ui->lineEditBasalt->setText(QString::number(selectedRecipe.getMaterialByName("basalt 0-8").getWeight()));
  ui->lineEditSand->setText(QString::number(selectedRecipe.getMaterialByName("sand 0-2").getWeight()));

  ui->lineEditCement->setText(QString::number(selectedRecipe.getComponentByName("cement").getWeight()));
  ui->doubleSpinBoxMaterialCementRatio->setValue(selectedRecipe.getComponentByName("cement").getRatio());


  ui->doubleSpinBoxWaterCement->setValue(selectedRecipe.getComponentByName("water").getRatio());
  ui->doubleSpinBoxPlastifierCementRatio->setValue(selectedRecipe.getComponentByName("plastifier").getRatio());
  ui->doubleSpinBoxPigmentCementRatio->setValue(selectedRecipe.getComponentByName("pigment").getRatio());

}
void RecipeWidget::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if(recipeId != 0) {
    selectedRecipe = prepareRecipeAppService->recipeMaterials(recipeId);

    fillForm();
  }
}
