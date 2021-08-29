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
#include <appservice.prepare.recipe/preparerecipeappservice.h>

class GroupBoxBinRecipeStatus : public QWidget {

 Q_OBJECT

 public:
  explicit GroupBoxBinRecipeStatus(std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService,
                                   QWidget *parent = nullptr);
  virtual ~GroupBoxBinRecipeStatus();

 public slots:
  void onRecipeSelectionUpdated(const std::shared_ptr<RecipeSelection>& selection);
  void onUpdateComponentSelection(const std::shared_ptr<RecipeSelection>& selection);

 private:
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;
  Ui::GroupBoxBinRecipeStatus *ui = nullptr;
  QTableWidgetItem *activeComponentTableWidget = new QTableWidgetItem;

  std::unique_ptr<IODevice> scale1;
  std::unique_ptr<IODevice> scaleBin;
  //Recipe selectedRecipe = Recipe(0);
  //Component activeComponent = Component(0);


  void createRecipeComponentTableWidget(const QVector<Component> &components, int componentId);
  void updateComponentWidgetTable(const Component &component);
  void setQLcdNumberDisplay(int value);
};

#endif //BSF_LIB_GROUPBOXBINRECIPESTATUS_H
