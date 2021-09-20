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

 private:
  Ui::RecipeWidget *ui = nullptr;
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;

  Recipe selectedRecipe;

  void createComboBox();
  void fillForm();
};

#endif //BSF_LIB_SRC_UI_WIDGETS_RECIPE_RECIPEWIDGET_H_
