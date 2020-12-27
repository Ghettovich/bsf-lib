#include "tst_recipe.h"
#include <recipe.h>
#include <reciperepo.h>

DECLARE_TEST_RECIPE(RecipeTest)

void RecipeTest::initTestCase() {
}

/*
 * Increases and decreased weight to a recipe and check if target is met.
 * Default target values should be: 50 plastifier, 500 water and 500 sand.
 * */
void RecipeTest::isRecipeTargetMet1() {
    int recipeId = 1;
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    RecipeRepository recipeRepository(testConnection);
    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    recipe.updateComponentWeight(1, 1000);
    recipe.updateComponentWeight(2, 500);

    QVERIFY(!recipe.isRecipeTargetMet());

    recipe.updateComponentWeight(3, 50);

    QVERIFY(recipe.isRecipeTargetMet());
}

void RecipeTest::isRecipeTargetMet2() {
  int recipeId = 1;
  QDir dir(".");
  const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
  RecipeRepository recipeRepository(testConnection);
  Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    recipe.updateComponentWeight(3, 100);
    recipe.updateComponentWeight(1, 450);

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
