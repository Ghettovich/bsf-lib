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
                                   std::shared_ptr<RecipeSelectionService> &recipeSelectionService,
                                   QObject *parent = nullptr);
  Recipe recipe(int recipeId);
  Recipe recipeWithComponents(int recipeId);
  QVector<Recipe> recipes();

 private:
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<RecipeService> recipeService;
  std::shared_ptr<RecipeSelectionService> recipeSelectionService;

 signals:
  void recipeSelectionUpdated(std::shared_ptr<RecipeSelection> &selection);
  void componentSelectionUpdated(std::shared_ptr<RecipeSelection> &selection);
};

#endif //BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_