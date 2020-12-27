#include "recipe.h"

Recipe::Recipe(int id)
    : id(id) {
}

int Recipe::getId() const {
  return id;
}

const QString &Recipe::getDescription() const {
  return description;
}

void Recipe::setDescription(const QString &_description) {
  description = _description;
}

int Recipe::getTargetWeightForComponent(int componentId) {
  int targetWeight = 0;

  for (const auto &comp: componentList) {
    if (comp.getComponentId() == componentId) {
      targetWeight = comp.getTargetWeight();
      break;
    }
  }

  return targetWeight;
}

Component Recipe::getComponent(int componentId) {
  for (auto &comp: componentList) {
    if (comp.getComponentId() == componentId) {
      return comp;
    }
  }

  return Component(0);
}

bool Recipe::isRecipeTargetMet() {
  for (const auto &comp: componentList) {
    if(!comp.isTargetMet()) {
      return false;
    }
  }

  return true;
}

void Recipe::updateComponentWeight(int componentId, int weight) {
  for (auto &comp: componentList) {
    if (comp.getComponentId() == componentId) {
      comp.setCurrentWeight(weight);
    }
  }
}

