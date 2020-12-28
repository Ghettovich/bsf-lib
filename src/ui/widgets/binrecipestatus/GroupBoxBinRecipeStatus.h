#ifndef BSF_LIB_GROUPBOXBINRECIPESTATUS_H
#define BSF_LIB_GROUPBOXBINRECIPESTATUS_H

namespace Ui {
class GroupBoxBinRecipeStatus;
}

#include <iodevice.h>
#include <widgets/interfaces/RecipeStatusInterface.h>
#include <recipe.h>
#include <MqttClient.h>
#include <fonts/MaterialRegular.h>
#include <QObject>
#include <QtWidgets/QWidget>
#include <QTableWidgetItem>

class GroupBoxBinRecipeStatus : public RecipeStatusInterface {

 Q_OBJECT
  Q_INTERFACES(RecipeStatusInterface)

 public:
  explicit GroupBoxBinRecipeStatus(MqttClient *m_client);
  virtual ~GroupBoxBinRecipeStatus();

 public slots:
  void onUpdateIODevice(WeightSensor *sensor) override;

 private:
  Ui::GroupBoxBinRecipeStatus *ui = nullptr;
  MqttClient *m_client = nullptr;
  IODevice *scale1 = nullptr;
  //IODevice *scaleBin = nullptr;
  Recipe selectedRecipe = Recipe(0);
  Component activeComponent = Component(0);
  QTableWidgetItem *activeComponentTableWidget = nullptr;

  void createRecipeComponentTableWidget();
  void updateComponentWidgetTable();
  void setQLcdNumberDisplay();
};

#endif //BSF_LIB_GROUPBOXBINRECIPESTATUS_H
