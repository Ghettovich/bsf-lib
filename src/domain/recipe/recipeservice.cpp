#include "recipeservice.h"

using namespace service;

RecipeService::RecipeService(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent),
    recipeRepository(std::make_shared<RecipeRepository>(_databaseService)) {
}

QVector<Recipe> RecipeService::recipes() {
  return recipeRepository->getRecipes();
}
std::unique_ptr<Recipe>  RecipeService::recipe(int recipeId) {
  return recipeRepository->getRecipe(recipeId);
}
void RecipeService::saveRecipe(const Recipe &recipe) {
  recipeRepository->saveRecipe(recipe);
}
void RecipeService::updateRecipeMaterial(int id, double weight) {
  recipeRepository->updateRecipeMaterial(id, weight);
}
void RecipeService::updateRecipeComponent(int id, double weight, double ratio) {
  recipeRepository->updateRecipeComponent(id, weight, ratio);
}
void RecipeService::updateRecipe(int id, const QString &title, const QString &description, double errorMargin) {
  recipeRepository->updateRecipe(id, title, description, errorMargin);
}
