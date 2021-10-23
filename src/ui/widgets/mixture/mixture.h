#ifndef BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_
#define BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_

#include <QWidget>
#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>
#include <appservice.broker/broker.appservice.h>

namespace Ui {
class Mixture;
}

class Mixture : public QWidget {

 Q_OBJECT

 public:
  explicit Mixture(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                   std::shared_ptr<appservice::PrepareRecipeAppService> &recipeAppService,
                   std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                   QWidget *parent = nullptr);
 QList<QWidget *> deviceWidgets();

 public slots:
  void onChangeRecipeComboBox(int index);
  void onClickStartBatch();
  void setStackedWidgetIndex(int index);
  void onClickTareScaleBin();
  void onClickCalibrateScaleBin();
//  void onClickTareScaleWater();
//  void onClickTareScalePigment();
//  void onClickTareScalePlastifier();

 private:
  Ui::Mixture *ui = nullptr;
  std::unique_ptr<Recipe> selectedRecipe;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> recipeAppservice;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;

  bool calibrationBinActive = false;

  void createRecipeComboBox();
  void fillRecipeGroupBox();
  void fillScaleGroupBoxes();

 signals:
  void stackedWidgetIndexChanged(int previousIndex);
};

#endif //BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_
