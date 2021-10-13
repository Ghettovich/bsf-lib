#include "ui_mixture.h"
#include "mixture.h"

using namespace appservice;

Mixture::Mixture(std::shared_ptr<IODeviceAppService> &_deviceAppService,
                 std::shared_ptr<PrepareRecipeAppService> &_recipeAppService,
                 QWidget *parent) :
    ui(new Ui::Mixture),
    deviceAppService(_deviceAppService),
    recipeAppservice(_recipeAppService),
    QWidget(parent) {
  // Setup UI and fill fields
  ui->setupUi(this);
  createRecipeComboBox();

  QObject::connect(ui->pushButtonStartBatch, &QPushButton::clicked, this, &Mixture::onClickStartBatch);
}
void Mixture::createRecipeComboBox() {
  auto recipes = recipeAppservice->recipes();

  QObject::connect(ui->comboBoxRecipe, QOverload<int>::of(&QComboBox::currentIndexChanged),
                   this, &Mixture::onChangeRecipeComboBox);

  for (int i = 0; i < recipes.size(); ++i) {
    ui->comboBoxRecipe->insertItem(i, recipes.at(i).getTitle(), recipes.at(i).getId());
  }
}
void Mixture::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if(recipeId != 0) {
    selectedRecipe = recipeAppservice->recipe(recipeId);
    fillRecipeGroupBox();
  }
}
void Mixture::fillRecipeGroupBox() {
  ui->lineEditBasalt->setText(QString::number(selectedRecipe->getMaterialByName("basalt 0-8").getWeight(), 10, 2));
  ui->lineEditSand->setText(QString::number(selectedRecipe->getMaterialByName("sand 0-2").getWeight(), 10, 2));

  ui->lineEditCement->setText(QString::number(selectedRecipe->getComponentByName("cement").getWeight(), 10, 2));
  ui->lineEditWater->setText(QString::number(selectedRecipe->getComponentByName("water").getWeight(), 10, 2));
  ui->lineEditPlastifier->setText(QString::number(selectedRecipe->getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lineEditPigment->setText(QString::number(selectedRecipe->getComponentByName("pigment").getWeight(), 10, 2));
}
void Mixture::onClickStartBatch() {
  ui->stackedWidget->setCurrentIndex(1);
}
