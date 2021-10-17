#ifndef BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_
#define BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_

#include <QWidget>
#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

namespace Ui {
class Mixture;
}

class Mixture : public QWidget {

 Q_OBJECT

 public:
  explicit Mixture(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                   std::shared_ptr<appservice::PrepareRecipeAppService> &recipeAppService,
                   QWidget *parent = nullptr);

 public slots:
  void onChangeRecipeComboBox(int index);
  void onClickStartBatch();
  void setStackedWidgetIndex(int index);

 private:
  Ui::Mixture *ui = nullptr;
  std::unique_ptr<Recipe> selectedRecipe;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> recipeAppservice;

  void createRecipeComboBox();
  void fillRecipeGroupBox();

 signals:
  void stackedWidgetIndexChanged(int previousIndex);
};

#endif //BSF_LIB_SRC_UI_WIDGETS_MIXTURE_MIXTURE_H_
