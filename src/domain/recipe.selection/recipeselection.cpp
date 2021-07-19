#include "recipeselection.h"

#include <utility>

RecipeSelection::RecipeSelection(QObject *parent) : QObject(parent) {

}
void RecipeSelection::updateSelectedRecipe(Recipe recipe) {
  selectedRecipe = std::move(recipe);
}
void RecipeSelection::updateSelectedComponent(int componentId, int currentWeight) {
  for(const auto &component : selectedRecipe.componentList) {
    if (component.getComponentId() == componentId) {
      selectedComponent = component;
      selectedComponent.setCurrentWeight(currentWeight);

      break;
    }
  }
}
QString RecipeSelection::getRecipeDescription() {
  return selectedRecipe.getDescription();
}
QVector<Component> RecipeSelection::getComponents() const {
  return selectedRecipe.componentList;
}
int RecipeSelection::getSelectedRecipeId() {
  return selectedRecipe.getId();
}
int RecipeSelection::getSelectedComponentId() {
  return selectedComponent.getComponentId();
}
void RecipeSelection::setCurrentWeightSelectedComponent(int currentWeight) {
  selectedComponent.setCurrentWeight(currentWeight);
}
