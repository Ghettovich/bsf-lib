#ifndef SCALE_H
#define SCALE_H

namespace Ui {
class Scale;
}

#include <iodevice.h>
#include <weightcensor.h>
#include <MqttClient.h>
#include <fonts/MaterialRegular.h>
#include <widgets/interfaces/RecipeStatusInterface.h>
#include <QTableWidgetItem>
#include <QtWidgets/QWidget>

class Scale : public RecipeStatusInterface {
 Q_OBJECT
  Q_INTERFACES(RecipeStatusInterface)

 public:
  explicit Scale(MqttClient *_m_client);
  virtual ~Scale();
  void init();

 public slots:
  void onUpdateIODevice(WeightSensor *sensor) override;
  void onScaleTimeOutOccured(IODevice::IO_DEVICE_HIGH_LOW state);

 private:
  Ui::Scale *ui = nullptr;
  MqttClient *m_client = nullptr;
  IODevice *weightSensor = nullptr;
  QTableWidgetItem *activeComponentTableWidget = nullptr;
  MaterialRegular material;
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
