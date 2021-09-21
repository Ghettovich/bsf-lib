#include "component.h"

#include <utility>

Component::Component(int id,
                     int component_id,
                     int recipe_id,
                     QString name,
                     QString description,
                     double weight,
                     double ratio)
    : id(id),
      componentId(component_id),
      recipeId(recipe_id),
      name(std::move(name)),
      description(std::move(description)),
      weight(weight),
      ratio(ratio) {}

int Component::getId() {
  return id;
}

int Component::getComponentId() const {
  return componentId;
}

void Component::setComponentId(int _componentId) {
  Component::componentId = _componentId;
}

int Component::getRecipeId() const {
  return recipeId;
}

void Component::setRecipeId(int _recipeId) {
  recipeId = _recipeId;
}

double Component::getWeight() const {
  return weight;
}
void Component::setWeight(double targetWeight) {
  weight = targetWeight;
}
double Component::getCurrentWeight() const {
  return currentWeight;
}
void Component::setCurrentWeight(double currentWeight) {
  currentWeight = currentWeight;
}
const QString &Component::getComponentName() const {
  return name;
}
void Component::setComponentName(const QString &_name) {
  name = _name;
}
const QString &Component::getComponentDescription() const {
  return description;
}
void Component::setComponentDescription(const QString &_description) {
  description = _description;
}
double Component::getRatio() const {
  return ratio;
}
void Component::setRatio(double ratio) {
  ratio = ratio;
}
