#ifndef BSF_TST_RECIPEREPO_H
#define BSF_TST_RECIPEREPO_H

#include "../autotest/AutoTest.h"
#include <QtCore/QObject>

class RecipeRepoTest : public QObject {
 Q_OBJECT

 private slots:
  void initTestCase();
  void isRecipeFound();
  void isRecipeListEmpty();
  void isRecipeWithComponentListEmpty();
  void cleanupTestCase();
};

#endif //BSF_TST_RECIPEREPO_H
