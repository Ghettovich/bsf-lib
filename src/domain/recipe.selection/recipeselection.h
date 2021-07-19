#ifndef BSF_RECIPESELECTION_H_
#define BSF_RECIPESELECTION_H_

#include <QObject>
#include <recipe/recipe.h>
#include <component/component.h>

class RecipeSelection : public QObject {
 Q_OBJECT

 public:
  explicit RecipeSelection(QObject *parent = nullptr);
  void updateSelectedRecipe(Recipe recipe);
  void updateSelectedComponent(int componentId, int currentWeight = 0);
  void setCurrentWeightSelectedComponent(int currentWeight);
  QString getRecipeDescription();
  int getSelectedRecipeId();
  int getSelectedComponentId();
  QVector<Component> getComponents() const;

 private:
  Recipe selectedRecipe = Recipe(0);
  Component selectedComponent = Component(0);
};

#endif //BSF_RECIPESELECTION_H_
