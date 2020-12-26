#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <recipe.h>
#include <bsfdatabaseconfig.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>
#include <QTreeWidgetItem>

class RecipeRepository {

 public:
  explicit RecipeRepository(const QString &connection = "");
  Recipe getRecipe(int);
  Recipe getRecipeWithComponents(int);
  QVector<Recipe> getRecipes();
  QList<QTreeWidgetItem *> getRecipesTreeWidgetList();

 private:
  BsfDbconfig bsfDbConfig;
  void addComponent(int recipeId, Component &, QVector<Component> &, QSqlQuery &);

};
#endif //BSF_RECIPEREPO_H
