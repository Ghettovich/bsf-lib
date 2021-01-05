#include "tst_Recipe.h"
#include <recipe.h>
#include <reciperepo.h>

void RecipeTest::init() {
  QDir dir(".");
  QString path = dir.relativeFilePath("../data/bsf.db");
  testConnection = path;
}

/*
 * Increases and decreased weight to a recipe and check if target is met.
 * Default target values should be: 50 plastifier, 500 water and 500 sand.
 * */
void RecipeTest::isRecipeTargetMet1() {
  // ARRANGE
  int recipeId = 1;
  RecipeRepository recipeRepository(testConnection);
  Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

  // ACT
  recipe.updateComponentWeight(1, 1000);
  recipe.updateComponentWeight(2, 500);

  // ASSERT
  QVERIFY(!recipe.isRecipeTargetMet());

  recipe.updateComponentWeight(3, 50);

  QVERIFY(recipe.isRecipeTargetMet());
}

void RecipeTest::isRecipeTargetMet2() {
  // ARRANGE
  int recipeId = 1;
  RecipeRepository recipeRepository(testConnection);
  Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

  // ACT
  recipe.updateComponentWeight(3, 100);
  recipe.updateComponentWeight(1, 450);

  // ASSERT
  QVERIFY(!recipe.isRecipeTargetMet());

  recipe.updateComponentWeight(2, 2000);

  QVERIFY(!recipe.isRecipeTargetMet());

  recipe.updateComponentWeight(3, 50);
  recipe.updateComponentWeight(2, 500);

  QVERIFY(!recipe.isRecipeTargetMet());

  recipe.updateComponentWeight(1, 1000);

  QVERIFY(recipe.isRecipeTargetMet());
}

void RecipeTest::cleanupTestCase() {
}
