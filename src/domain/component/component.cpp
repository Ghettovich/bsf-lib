#include "component.h"

#include <utility>

Component::Component(int id,
                     int component_id,
                     int recipe_id,
                     QString name,
                     QString description,
                     int weight,
                     float ratio)
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

int Component::getWeight() const {
  return weight;
}
void Component::setWeight(int _targetWeight) {
  weight = _targetWeight;
}
int Component::getCurrentWeight() const {
  return currentWeight;
}
void Component::setCurrentWeight(int _currentWeight) {
  currentWeight = _currentWeight;
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
float Component::getRatio() const {
  return ratio;
}
void Component::setRatio(float _ratio) {
  ratio = _ratio;
}
