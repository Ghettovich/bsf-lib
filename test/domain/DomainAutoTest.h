#ifndef DOMAINAUTOTEST_H
#define DOMAINAUTOTEST_H

#include "../autotest/AutoTest.h"

// DOMAIN
#define DECLARE_TEST_RECIPE(className) static Test<className> t("RecipeTest");

#define TEST_MAIN_DOMAIN \
 int main(int argc, char *argv[]) \
 {                \
    QApplication app(argc, argv); \
    return AutoTest::run(argc, argv); \
 }

#endif //DOMAINAUTOTEST_H
