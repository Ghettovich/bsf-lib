#ifndef BSF_LIB_GROUPBOXBINRECIPESTATUS_H
#define BSF_LIB_GROUPBOXBINRECIPESTATUS_H

namespace Ui {
class GroupBoxBinRecipeStatus;
}

#include <QtWidgets/QWidget>
#include <QTableWidgetItem>

#include <iodevice/iodevice.h>
#include <recipe/recipe.h>
#include <component/component.h>
#include <fonts/MaterialRegular.h>
#include <appservice.prepare.recipe/PrepareRecipeAppService.h>

class GroupBoxBinRecipeStatus : public QWidget {

 Q_OBJECT

 public:
  explicit GroupBoxBinRecipeStatus(std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService,
                                   QWidget *parent = nullptr);
  virtual ~GroupBoxBinRecipeStatus();

 public slots:
  //void onUpdateIODevice(IODevice *sensor);
  void onUpdateIODevice(const std::shared_ptr<RecipeSelection>& selection);
  void onUpdateComponentSelection(const std::shared_ptr<RecipeSelection>& selection);

 private:
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;
  Ui::GroupBoxBinRecipeStatus *ui = nullptr;
  std::unique_ptr<IODevice> scale1;
  std::unique_ptr<IODevice> scaleBin;
  Recipe selectedRecipe = Recipe(0);
  Component activeComponent = Component(0);
  QTableWidgetItem *activeComponentTableWidget = nullptr;

  void createRecipeComponentTableWidget();
  void updateComponentWidgetTable();
  void setQLcdNumberDisplay();
};

#endif //BSF_LIB_GROUPBOXBINRECIPESTATUS_H
