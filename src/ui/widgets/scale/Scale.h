#ifndef SCALE_H
#define SCALE_H

#include <QtWidgets/QWidget>
#include <QTableWidgetItem>

#include <recipe/recipe.h>
#include <iodevice/iodevice.h>

#include <appservice.broker/brokerappservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

namespace Ui {
class Scale;
}

class Scale : public QWidget {
 Q_OBJECT

 public:
  explicit Scale(std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                 std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService,
                 QWidget *parent = nullptr);
  virtual ~Scale();
  void init();

 public slots:
  void onUpdateIODevice(IODevice *device);
  void onScaleTimeOutOccured(IODevice::IO_DEVICE_HIGH_LOW state);

 private:
  Ui::Scale *ui = nullptr;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;

  std::unique_ptr<IODevice> weightSensor;
  QTableWidgetItem *activeComponentTableWidget = nullptr;
  Recipe configuredRecipe = Recipe(0);
  Component activeComponent = Component(0);
  bool isTareActive = false;

  void createRecipeComponentTableWidget();
  void setQLcdNumberDisplay();
  void setPushButtonConfirmRecipe();
  void setRecipeProgressBar();
  void updateComponentWidgetTable();

 private slots:
  void onClickPushButtonTare();
  void onClickPushButtonConfirmRecipe();

 signals:
  void receivedComponent(const Component &component);
  void scaleInTareMode(bool isInTareMode);
  void scaleTimeOutOccured(IODevice::IO_DEVICE_HIGH_LOW state);
};

#endif //SCALE_H
