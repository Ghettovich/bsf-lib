#ifndef BSF_TST_RECIPE_H
#define BSF_TST_RECIPE_H

#include <QtTest/QTest>
#include <QtCore/QObject>


class RecipeTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isRecipeTargetMet1();
    void isRecipeTargetMet2();
    void cleanupTestCase();

};

#endif //BSF_TST_RECIPE_H
