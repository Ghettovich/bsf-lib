#include "tst_reciperepo.h"
#include <QtTest/QtTest>
#include <repo/reciperepo.h>

void RecipeRepoTest::init() {
  QDir dir(".");
  testConnection = dir.absoluteFilePath("bsf.db");
}

/*
 * Check if the recipe with id is found.
 * */
void RecipeRepoTest::isRecipeFound() {
  // ARRANGE
  int recipeId = 1;
  RecipeRepository recipeRepository(testConnection);

  // ACT
  Recipe recipe = recipeRepository.getRecipe(recipeId);

  // ASSERT
  QVERIFY(recipe.getId() > 0);
}

/*
 * Check if the recipe list is not empty.
 * */
void RecipeRepoTest::isRecipeListEmpty() {
  // ARRANGE
  RecipeRepository recipeRepository(testConnection);

  // ACT
  QVector<Recipe> recipeList = recipeRepository.getRecipes();

  // ASSERT
  QVERIFY(!recipeList.isEmpty());
}

/*
 * Check if the recipe list is not empty.
 * */
void RecipeRepoTest::isRecipeWithComponentListEmpty() {
  // ARRANGE
  int recipeId = 1;
  RecipeRepository recipeRepository(testConnection);

  // ACT
  Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

  // ASSERT
  QVERIFY(!recipe.componentList.isEmpty());
  QVERIFY(!recipe.getDescription().isEmpty());
}

void RecipeRepoTest::cleanupTestCase() {
}
