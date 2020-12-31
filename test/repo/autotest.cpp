#include "tst_actionarduinorepo.h"
#include "tst_arduinorepo.h"
#include "tst_iodevicerepo.h"
#include "tst_logrepo.h"
#include "tst_reciperepo.h"
#include "tst_statecoderepo.h"
#include <QTest>

int main(int argc, char *argv[]) {
  int status = 0;

  {
    ActionArduinoRepoTest actionArduinoRepoTest;
    status |= QTest::qExec(&actionArduinoRepoTest, argc, argv);
  }

  {
    ArduinoRepoTest arduinoRepoTest;
    status |= QTest::qExec(&arduinoRepoTest, argc, argv);
  }

  {
    IODeviceRepoTest iodeviceRepoTest;
    status |= QTest::qExec(&iodeviceRepoTest, argc, argv);
  }

  {
    LogRepoTest logRepoTest;
    status |= QTest::qExec(&logRepoTest, argc, argv);
  }

  {
    RecipeRepoTest recipeRepoTest;
    status |= QTest::qExec(&recipeRepoTest, argc, argv);
  }

  {
    StateCodeRepoTest stateCodeRepoTest;
    status |= QTest::qExec(&stateCodeRepoTest, argc, argv);
  }

  return status;
}