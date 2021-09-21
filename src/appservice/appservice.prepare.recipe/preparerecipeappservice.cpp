#include "preparerecipeappservice.h"
#include <QDebug>

using namespace appservice;

PrepareRecipeAppService::PrepareRecipeAppService(std::shared_ptr<IODeviceService> &_deviceService,
                                                 std::shared_ptr<RecipeService> &_recipeService,
                                                 QObject *parent) :
    deviceService(_deviceService),
    recipeService(_recipeService),
    QObject(parent) {

}
QVector<Recipe> PrepareRecipeAppService::recipes() {
  return recipeService->recipes();
}
std::unique_ptr<Recipe> PrepareRecipeAppService::recipe(int recipeId) {
  return recipeService->recipe(recipeId);
}
void PrepareRecipeAppService::saveRecipe(const Recipe &recipe) {
  //recipeService->saveRecipe(recipe);
}
void PrepareRecipeAppService::updateRecipeMaterial(int id, double weight) {
  recipeService->updateRecipeMaterial(id, weight);
}
void PrepareRecipeAppService::updateRecipeComponent(int id, double weight, double ratio) {
  recipeService->updateRecipeComponent(id, weight, ratio);
}
void PrepareRecipeAppService::updateRecipe(int id,
                                           const QString &title,
                                           const QString &description,
                                           double errorMargin) {
  recipeService->updateRecipe(id, title, description, errorMargin);
}
