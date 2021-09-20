#include "recipeservice.h"

using namespace service;

RecipeService::RecipeService(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent),
    recipeRepository(std::make_unique<RecipeRepository>(_databaseService)) {
}

QVector<Recipe> RecipeService::recipes() {
  return recipeRepository->getRecipes();
}
Recipe RecipeService::recipeMaterials(int recipeId) {
  return recipeRepository->getRecipeMaterials(recipeId);
}
