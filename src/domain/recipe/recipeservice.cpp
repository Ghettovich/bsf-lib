#include "recipeservice.h"

using namespace service;

RecipeService::RecipeService(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent),
    recipeRepository(std::make_unique<RecipeRepository>(_databaseService)) {
}

QVector<Recipe> RecipeService::recipes() {
  return recipeRepository->getRecipes();
}

Recipe RecipeService::recipe(int recipeId) {
  return recipeRepository->getRecipe(recipeId);
}

Recipe RecipeService::recipeWithComponents(int recipeId) {
  return recipeRepository->getRecipeWithComponents(recipeId);
}
