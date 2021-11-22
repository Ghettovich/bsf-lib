#include "ui_tabwidgetcreatebatch.h"
#include "TabwidgetCreateBatch.h"

#include <iodevice/iodevice.h>

#include <QSettings>

using namespace appservice;

TabWidgetCreateBatch::TabWidgetCreateBatch(std::shared_ptr<IODeviceAppService> &_deviceAppService,
                                           std::shared_ptr<appservice::PrepareRecipeAppService> &_recipeAppService,
                                           QWidget *parent) :
    ui(new Ui::TabWidgetCreateBatch),
    deviceAppService(_deviceAppService),
    recipeAppService(_recipeAppService),
    QTabWidget(parent) {
  ui->setupUi(this);

  initLiftControlGroupBox();
  initBinControlGroupBox();
  initRecipeComboBox();
}
TabWidgetCreateBatch::~TabWidgetCreateBatch() {
  delete ui;
}
QList<QWidget *> TabWidgetCreateBatch::deviceWidgets() {
  return QList<QWidget *>()
      << ui->labelLiftTop
      << ui->labelLiftBottom
      << ui->labelBinDrop
      << ui->labelBinLoad
      << ui->pushButtonLiftTop
      << ui->pushButtonLiftBottom
      << ui->pushButtonBinDrop
      << ui->pushButtonBinLoad;
}
void TabWidgetCreateBatch::initLiftControlGroupBox() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  auto relayBinLiftDown = deviceAppService->findOne(settings->value("liftdown").toInt());

  ui->pushButtonLiftBottom->setProperty("deviceId", relayBinLiftDown->getId());
  ui->pushButtonLiftBottom->setProperty("sensor", "relay");
  ui->pushButtonLiftBottom->setText(relayBinLiftDown->getDescription());

  auto relayBinLiftUp = deviceAppService->findOne(settings->value("liftup").toInt());

  ui->pushButtonLiftTop->setProperty("deviceId", relayBinLiftUp->getId());
  ui->pushButtonLiftTop->setProperty("sensor", "relay");
  ui->pushButtonLiftTop->setText(relayBinLiftUp->getDescription());

  settings->endGroup();

  settings->beginGroup("detectionsensor");

  auto proximityLiftTop = deviceAppService->findOne(settings->value("lifttop").toInt());
  ui->labelLiftTop->setToolTip(proximityLiftTop->getDescription());
  ui->labelLiftTop->setProperty("sensor", "proximity");
  ui->labelLiftTop->setProperty("deviceId", proximityLiftTop->getId()); // PULL UP (HIGH = OFF!)

  auto proximityLiftBottom = deviceAppService->findOne(settings->value("liftbottom").toInt());
  ui->labelLiftBottom->setToolTip(proximityLiftBottom->getDescription());
  ui->labelLiftBottom->setProperty("sensor", "proximity");
  ui->labelLiftBottom->setProperty("deviceId", proximityLiftBottom->getId()); // PULL UP (HIGH = OFF!)

  settings->endGroup();
}
void TabWidgetCreateBatch::initBinControlGroupBox() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  auto relayBinLoad = deviceAppService->findOne(settings->value("binload").toInt());

  ui->pushButtonBinLoad->setProperty("deviceId", relayBinLoad->getId());
  ui->pushButtonBinLoad->setProperty("sensor", "relay");
  ui->pushButtonBinLoad->setText(relayBinLoad->getDescription());

  auto relayBinDrop = deviceAppService->findOne(settings->value("bindrop").toInt());

  ui->pushButtonBinDrop->setProperty("deviceId", relayBinLoad->getId());
  ui->pushButtonBinDrop->setProperty("sensor", "relay");
  ui->pushButtonBinDrop->setText(relayBinLoad->getDescription());

  settings->endGroup();

  settings->beginGroup("detectionsensor");

  auto proximityBinLoad = deviceAppService->findOne(settings->value("binload").toInt());

  ui->labelBinLoad->setToolTip(proximityBinLoad->getDescription());
  ui->labelBinLoad->setProperty("sensor", "proximity");
  ui->labelBinLoad->setProperty("deviceId", proximityBinLoad->getId()); // PULL UP (HIGH = OFF!)

  auto proximityBinDrop = deviceAppService->findOne(settings->value("bindrop").toInt());

  ui->labelBinDrop->setToolTip(proximityBinDrop->getDescription());
  ui->labelBinDrop->setProperty("sensor", "proximity");
  ui->labelBinDrop->setProperty("deviceId", proximityBinDrop->getId()); // PULL UP (HIGH = OFF!)
}
void TabWidgetCreateBatch::initRecipeComboBox() {
  auto recipes = recipeAppService->recipes();

  QObject::connect(ui->comboBoxRecipe, QOverload<int>::of(&QComboBox::currentIndexChanged),
                   this, &TabWidgetCreateBatch::onChangeRecipeComboBox);

  for (int i = 0; i < recipes.size(); ++i) {
    ui->comboBoxRecipe->insertItem(i, recipes.at(i).getTitle(), recipes.at(i).getId());
  }
}
void TabWidgetCreateBatch::fillRecipeGroupBox() {
  ui->lineEditBasalt->setText(QString::number(selectedRecipe->getMaterialByName("basalt 0-8").getWeight(), 10, 2));
  ui->lineEditSand->setText(QString::number(selectedRecipe->getMaterialByName("sand 0-2").getWeight(), 10, 2));

  double sumRawMaterial = selectedRecipe->getMaterialByName("basalt 0-8").getWeight() +
      selectedRecipe->getMaterialByName("sand 0-2").getWeight() +
      selectedRecipe->getComponentByName("cement").getWeight();
  ui->lineEditBinTargetWeight->setText(QString::number(sumRawMaterial, 10, 2));

  ui->lineEditCement->setText(QString::number(selectedRecipe->getComponentByName("cement").getWeight(), 10, 2));
  ui->lineEditWater->setText(QString::number(selectedRecipe->getComponentByName("water").getWeight(), 10, 2));
  ui->lineEditWaterTargetWeight->setText(QString::number(selectedRecipe->getComponentByName("water").getWeight(), 10, 2));
  ui->lineEditPlastifier->setText(QString::number(selectedRecipe->getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lineEditComponentTargetWeight->setText(QString::number(selectedRecipe->getComponentByName("plastifier").getWeight(), 10, 2));
  ui->lineEditPigment->setText(QString::number(selectedRecipe->getComponentByName("pigment").getWeight(), 10, 2));
  ui->lineEditPigmentTargetWeight->setText(QString::number(selectedRecipe->getComponentByName("pigment").getWeight(), 10, 2));
}
void TabWidgetCreateBatch::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if (recipeId != 0) {
    selectedRecipe = recipeAppService->recipe(recipeId);
    fillRecipeGroupBox();
  }
}
