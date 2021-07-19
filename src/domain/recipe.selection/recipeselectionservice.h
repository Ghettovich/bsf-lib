#ifndef BSF_SELECTION_RECIPESELECTIONSERVICE_H_
#define BSF_SELECTION_RECIPESELECTIONSERVICE_H_

#include "recipeselection.h"

#include <memory>
#include <QObject>
#include <iodevice/iodeviceservice.h>
#include <recipe/recipeservice.h>

class RecipeSelectionService : public QObject {
 Q_OBJECT

 public:
  explicit RecipeSelectionService(std::shared_ptr<IODeviceService> &deviceService,
                                  std::shared_ptr<RecipeService> &recipeService,
                                  QObject *parent = nullptr);
  void resetRecipe();


 public slots:
  void onUpdateRecipeSelection(IODevice *device);

 private:
  std::shared_ptr<RecipeSelection> recipeSelection;
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<RecipeService> recipeService;

  void updateRecipeSelection(int recipeId);
  void updateComponentSelection(int componentId, int currentWeight);

 signals:
  void recipeSelectionUpdated(std::shared_ptr<RecipeSelection> &selection);
  void componentSelectionUpdated(std::shared_ptr<RecipeSelection> &selection);
};

#endif //BSF_SELECTION_RECIPESELECTIONSERVICE_H_
