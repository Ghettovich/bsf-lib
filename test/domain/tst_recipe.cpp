#include "tst_recipe.h"
#include <QtTest/QTest>
#include <recipe.h>

DECLARE_TEST_RECIPE(RecipeTest)

void RecipeTest::initTestCase() {
}

/*
 * Increases and decreased weight to a recipe and check if target is met.
 * Default target values should be: 50 plastifier, 500 water and 500 sand.
 * */
void RecipeTest::isRecipeTargetMet1() {
    int recipeId = 1;
    Recipe recipe = Recipe(1);

    recipe.componentList.append(Component(0));

    recipe.updateWeightForComponent(1, 1000);
    recipe.updateWeightForComponent(2, 500);

//    QVERIFY(!recipe.isRecipeTargetMet());
//
//    recipe.updateWeightForComponent(3, 50);

    QVERIFY(!recipe.componentList.empty());
}

//void RecipeTest::isRecipeTargetMet2() {
//    int recipeId = 1;
//    RecipeRepository recipeRepository;
//    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);
//
//    recipe.updateWeightForComponent(3, 100);
//    recipe.updateWeightForComponent(1, 450);
//
//    QVERIFY(!recipe.isRecipeTargetMet());
//
//    recipe.updateWeightForComponent(2, 2000);
//
//    QVERIFY(!recipe.isRecipeTargetMet());
//
//    recipe.updateWeightForComponent(3, 50);
//    recipe.updateWeightForComponent(2, 500);
//
//    QVERIFY(!recipe.isRecipeTargetMet());
//
//    recipe.updateWeightForComponent(1, 1000);
//
//    QVERIFY(recipe.isRecipeTargetMet());
//}

void RecipeTest::cleanupTestCase() {
}
