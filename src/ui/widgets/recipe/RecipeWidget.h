#ifndef BSF_LIB_SRC_UI_WIDGETS_RECIPE_RECIPEWIDGET_H_
#define BSF_LIB_SRC_UI_WIDGETS_RECIPE_RECIPEWIDGET_H_

#include <memory>
#include <QtWidgets/QWidget>

#include <recipe/recipe.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

namespace Ui {
class RecipeWidget;
}

class RecipeWidget : public QWidget {
 Q_OBJECT

 public:
  explicit RecipeWidget(std::shared_ptr<appservice::PrepareRecipeAppService> &recipeAppService,
                        QWidget *parent = nullptr);
  virtual ~RecipeWidget();

 public slots:
  void onChangeRecipeComboBox(int index);
  void onFinishEditingBasalt();
  void onFinishEditingSand();
  void onChangeSpinboxMaterialCement(double value);

 private:
  Ui::RecipeWidget *ui = nullptr;
  std::unique_ptr<Recipe> selectedRecipe;
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;

  void createComboBox();
  void fillForm();
  void updateMaterialCement(double basaltWeight, double sandWeight, double ratio);
};

#endif //BSF_LIB_SRC_UI_WIDGETS_RECIPE_RECIPEWIDGET_H_
