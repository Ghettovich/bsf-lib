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

  QVector<Recipe> recipes();
  std::unique_ptr<Recipe>  recipeMaterials(int recipeId);

 private:
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<RecipeService> recipeService;

};

#endif //BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_
