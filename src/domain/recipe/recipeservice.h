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
  std::unique_ptr<Recipe> recipeMaterials(int recipeId);

 private:
  std::shared_ptr<RecipeRepository> recipeRepository;
};

#endif //BSF_RECIPESERVICE_H_
