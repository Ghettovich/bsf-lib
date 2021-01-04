#include "tst_Recipe.h"
#include "tst_Arduino.h"

int main(int argc, char *argv[]) {
  int status = 0;

  {
    RecipeTest recipeTest;
    status |= QTest::qExec(&recipeTest, argc, argv);
  }

  {
    ArduinoTest arduinoTest;
    status |= QTest::qExec(&arduinoTest, argc, argv);
  }

  return status;
}
