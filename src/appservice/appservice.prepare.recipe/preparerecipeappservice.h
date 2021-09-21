#ifndef BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_
#define BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_

#include <memory>
#include <QObject>
#include <recipe/recipeservice.h>
#include <iodevice/iodeviceservice.h>
#include <recipe.selection/recipeselectionservice.h>

namespace appservice {
class PrepareRecipeAppService;
}

class appservice::PrepareRecipeAppService : public QObject {
 Q_OBJECT

 public:
  explicit PrepareRecipeAppService(std::shared_ptr<IODeviceService> &deviceService,
                                   std::shared_ptr<RecipeService> &recipeService,
                                   QObject *parent = nullptr);

  /// Return a list of recipes
  QVector<Recipe> recipes();

  /// Return a recipe
  std::unique_ptr<Recipe> recipe(int recipeId);

  /// Create a new recipe.
  void saveRecipe(const Recipe &recipe);

  /// Update recipe title, description and error margin.
  void updateRecipe(int id, const QString &title, const QString &description, double errorMargin);

  /// Update a material weight by their id.
  void updateRecipeMaterial(int id, double weight);

  /// Update a components weight and ratio by their id.
  void updateRecipeComponent(int id, double weight, double ratio);

 private:
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<RecipeService> recipeService;

};

#endif //BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_
