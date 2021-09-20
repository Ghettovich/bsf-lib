#include "component.h"

#include <utility>

Component::Component(int id,
                     int component_id,
                     int recipe_id,
                     QString name,
                     QString description,
                     float weight,
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

float Component::getWeight() const {
  return weight;
}
void Component::setWeight(float _targetWeight) {
  weight = _targetWeight;
}
float Component::getCurrentWeight() const {
  return currentWeight;
}
void Component::setCurrentWeight(float _currentWeight) {
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
