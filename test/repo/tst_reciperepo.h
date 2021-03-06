#ifndef BSF_TST_RECIPEREPO_H
#define BSF_TST_RECIPEREPO_H

#include <QtCore/QObject>

class RecipeRepoTest : public QObject {
 Q_OBJECT

 private:
  QString testConnection;

 private slots:
  void init();
  void isRecipeFound();
  void isRecipeListEmpty();
  void isRecipeWithComponentListEmpty();
  void cleanupTestCase();
};

#endif //BSF_TST_RECIPEREPO_H
