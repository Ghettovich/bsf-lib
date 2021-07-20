#include "preparerecipeappservice.h"
#include <QDebug>

using namespace appservice;

PrepareRecipeAppService::PrepareRecipeAppService(std::shared_ptr<IODeviceService> &_deviceService,
                                                 std::shared_ptr<RecipeService> &_recipeService,
                                                 std::shared_ptr<RecipeSelectionService> &_recipeSelectionService,
                                                 QObject *parent) :
    deviceService(_deviceService),
    recipeService(_recipeService),
    recipeSelectionService(_recipeSelectionService),
    QObject(parent) {

  connect(recipeSelectionService.get(), &RecipeSelectionService::recipeSelectionUpdated, [=](std::shared_ptr<RecipeSelection> &selection){
    emit recipeSelectionUpdated(selection);
  });

  connect(recipeSelectionService.get(), &RecipeSelectionService::componentSelectionUpdated, [=](std::shared_ptr<RecipeSelection> &selection){
    emit componentSelectionUpdated(selection);
  });
}
Recipe PrepareRecipeAppService::recipe(int recipeId) {
  return recipeService->recipe(recipeId);
}
Recipe PrepareRecipeAppService::recipeWithComponents(int recipeId) {
  return recipeService->recipeWithComponents(recipeId);
}
QVector<Recipe> PrepareRecipeAppService::recipes() {
  return recipeService->recipes();
}
