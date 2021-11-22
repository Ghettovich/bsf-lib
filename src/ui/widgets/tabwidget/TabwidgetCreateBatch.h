#ifndef BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_
#define BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_

#include <QWidget>
#include <QTabWidget>
#include <recipe/recipe.h>
#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

namespace Ui {
class TabWidgetCreateBatch;
}

class TabWidgetCreateBatch : public QTabWidget {
 Q_OBJECT

 public:
  explicit TabWidgetCreateBatch(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                                std::shared_ptr<appservice::PrepareRecipeAppService> &recipeAppService,
                                QWidget *parent = nullptr);
  virtual ~TabWidgetCreateBatch();
  QList<QWidget *> deviceWidgets();

 public slots:
  void onChangeRecipeComboBox(int index);

 private:
  Ui::TabWidgetCreateBatch *ui = nullptr;
  std::unique_ptr<Recipe> selectedRecipe;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> recipeAppService;

  void initLiftControlGroupBox();
  void initBinControlGroupBox();
  void initRecipeComboBox();
  void fillRecipeGroupBox();

  void setLiftBottomTopRelayButtons();
  void setBinDropLoadRelayButtons();
};

#endif //BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_
