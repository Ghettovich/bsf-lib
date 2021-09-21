#ifndef BSF_RECIPESERVICE_H_
#define BSF_RECIPESERVICE_H_

#include "recipe.h"
#include "reciperepo.h"

#include <memory>
#include <QObject>

#include <database/DatabaseService.h>

class RecipeService : public QObject {
 Q_OBJECT

 public:
  explicit RecipeService(std::shared_ptr<service::DatabaseService> &databaseService,
                         QObject *parent = nullptr);
  QVector<Recipe> recipes();
  std::unique_ptr<Recipe> recipe(int recipeId);
  void saveRecipe(const Recipe &recipe);
  void updateRecipeMaterial(int id, double weight);
  void updateRecipeComponent(int id, double weight, double ratio);
  void updateRecipe(int id, const QString &title, const QString &description, double errorMargin);

 private:
  std::shared_ptr<RecipeRepository> recipeRepository;
};

#endif //BSF_RECIPESERVICE_H_
