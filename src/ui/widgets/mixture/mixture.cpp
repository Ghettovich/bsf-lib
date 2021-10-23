#include "ui_mixture.h"
#include "mixture.h"
#include <iodevice/weightcensor.h>
#include <QMessageBox>

using namespace appservice;

Mixture::Mixture(std::shared_ptr<IODeviceAppService> &_deviceAppService,
                 std::shared_ptr<PrepareRecipeAppService> &_recipeAppService,
                 std::shared_ptr<appservice::BrokerAppService> &_brokerAppService,
                 QWidget *parent) :
    ui(new Ui::Mixture),
    deviceAppService(_deviceAppService),
    recipeAppservice(_recipeAppService),
    brokerAppService(_brokerAppService),
    QWidget(parent) {

  // Setup UI and fill fields
  ui->setupUi(this);
  createRecipeComboBox();
  fillScaleGroupBoxes();

  QObject::connect(ui->pushButtonCalibrateScaleBin, &QPushButton::clicked, this, &Mixture::onClickCalibrateScaleBin);
  QObject::connect(ui->pushButtonTareScaleBin, &QPushButton::clicked, this, &Mixture::onClickTareScaleBin);
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

void Mixture::fillScaleGroupBoxes() {
  // Set properties on widgets
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("scale");
  auto scaleBin = deviceAppService->findOne(settings->value("weightbinload").toInt());

  qDebug() << "got id " << scaleBin->getId() << " for scale";
  ui->groupBoxScaleBin->setTitle(scaleBin->getDescription());
  ui->lcdNumberScaleBin->setProperty("deviceId", scaleBin->getId());
  ui->lcdNumberScaleBin->setProperty("sensor", "scale");
  ui->pushButtonCalibrateScaleBin->setProperty("deviceId", scaleBin->getId());
}

void Mixture::onChangeRecipeComboBox(int index) {
  int recipeId = ui->comboBoxRecipe->itemData(index, Qt::UserRole).toInt();

  if (recipeId != 0) {
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
  emit stackedWidgetIndexChanged(ui->stackedWidget->currentIndex() - 1);
}
void Mixture::setStackedWidgetIndex(int index) {
  ui->stackedWidget->setCurrentIndex(index);
}
void Mixture::onClickTareScaleBin() {
  brokerAppService->tareScale(ui->pushButtonCalibrateScaleBin->property("deviceId").toInt());
}
void Mixture::onClickCalibrateScaleBin() {
  if (calibrationBinActive) {
    brokerAppService->calibrateScale(ui->pushButtonCalibrateScaleBin->property("deviceId").toInt(),
                                     calibrationBinActive);

    ui->pushButtonCalibrateScaleBin->setText("Calibrate scale bin");
    calibrationBinActive = false;
  } else {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Tare scale?"),
                                  "Please clear the scale... then proceed.\n\nExpected calibration weight 1kg.",
                                  QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
      brokerAppService->calibrateScale(ui->pushButtonCalibrateScaleBin->property("deviceId").toInt(),
                                       calibrationBinActive);
      ui->pushButtonCalibrateScaleBin->setText("Finish calibrating");
      calibrationBinActive = true;
    }
  }
}
QList<QWidget *> Mixture::deviceWidgets() {
  return QList<QWidget *>()
      << ui->lcdNumberScaleBin;
}
