#include "tst_recipe.h"

int main(int argc, char *argv[]) {
  int status = 0;

  {
    RecipeTest recipeTest;
    status |= QTest::qExec(&recipeTest, argc, argv);
  }

  return status;
}
