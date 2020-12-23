#include "tst_reciperepo.h"
#include <QtTest/QtTest>
#include <repo/reciperepo.h>

DECLARE_TEST_RECIPE_REPO(RecipeRepoTest)

void RecipeRepoTest::initTestCase() {
}

/*
 * Check if the recipe with id is found.
 * */
void RecipeRepoTest::isRecipeFound() {
    // ARRANGE
    int recipeId = 1;
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
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
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
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
    QDir dir(".");
    const QString testConnection = dir.absolutePath().append("/resource/database/bsf.db");
    RecipeRepository recipeRepository(testConnection);

    // ACT
    Recipe recipe = recipeRepository.getRecipeWithComponents(recipeId);

    // ASSERT
    QVERIFY(!recipe.componentList.isEmpty());
    QVERIFY(!recipe.getDescription().isEmpty());
}



void RecipeRepoTest::cleanupTestCase() {
}
