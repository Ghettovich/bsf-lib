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
Recipe PrepareRecipeAppService::recipeMaterials(int recipeId) {
  return recipeService->recipeMaterials(recipeId);
}
