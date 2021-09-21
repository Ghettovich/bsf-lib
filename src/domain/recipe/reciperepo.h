#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include "recipe.h"

#include <memory>
#include <QObject>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

#include <database/DatabaseService.h>

class RecipeRepository : public QObject {

 public:
  explicit RecipeRepository(std::shared_ptr<service::DatabaseService> &databaseService, QObject *parent = nullptr);
  QVector<Recipe> getRecipes();
  std::unique_ptr<Recipe> getRecipe(int recipeId);
  void saveRecipe(const Recipe &recipe);
  void updateRecipeMaterial(int id, double weight);
  void updateRecipeComponent(int id, double weight, double ratio);
  void updateRecipe(int id, const QString &title, const QString &description, double errorMargin);

 private:
  std::shared_ptr<service::DatabaseService> databaseService;
  QList<Material> getMaterials(int recipeId);
  QList<Component> getComponents(int recipeId);

};
#endif //BSF_RECIPEREPO_H
