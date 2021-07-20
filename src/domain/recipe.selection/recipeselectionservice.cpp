#include "recipeselectionservice.h"
#include <iodevice/weightcensor.h>

RecipeSelectionService::RecipeSelectionService(std::shared_ptr<IODeviceService> &_deviceService,
                                               std::shared_ptr<RecipeService> &_recipeService,
                                               QObject *parent) :
    deviceService(_deviceService), recipeService(_recipeService), QObject(parent) {
  recipeSelection = std::make_shared<RecipeSelection>();

  connect(deviceService.get(), &IODeviceService::updateScale,
          this, &RecipeSelectionService::onUpdateRecipeSelection);
}
void RecipeSelectionService::onUpdateRecipeSelection(IODevice *device) {
  auto scale = dynamic_cast<WeightSensor *>(device);

  if (scale->getRecipeId() == 0 || scale->getComponentId() == 0) {
    // ToDo: fix tare
  } else {
    updateRecipeSelection(scale->getRecipeId());
    updateComponentSelection(scale->getComponentId(), scale->getCurrentWeight());

    qDebug() << "updated recipe and component selection.";
  }
}
void RecipeSelectionService::resetRecipe() {

}
void RecipeSelectionService::updateRecipeSelection(int recipeId) {
  int oldId = recipeSelection->getSelectedRecipeId();
  auto recipe = recipeService->recipeWithComponents(recipeId);

  recipeSelection->updateSelectedRecipe(recipe);

  if (oldId != recipeSelection->getSelectedRecipeId()) {
    emit recipeSelectionUpdated(recipeSelection);
    qDebug() << "old id" << oldId;
  }
}
void RecipeSelectionService::updateComponentSelection(int componentId, int currentWeight) {
  int oldId = recipeSelection->getSelectedComponentId();

  if (oldId == componentId) {
    recipeSelection->setCurrentWeightSelectedComponent(currentWeight);
  } else {
    recipeSelection->updateSelectedComponent(componentId, currentWeight);
  }

  emit componentSelectionUpdated(recipeSelection);
}
