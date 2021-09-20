#include "recipe.h"

#include <utility>

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
const QString &Recipe::getTitle() const {
  return title;
}
void Recipe::setTitle(const QString &_title) {
  title = _title;
}
const QList<Material> &Recipe::getMaterials() const {
  return materials;
}
void Recipe::setMaterials(QList<Material> _materials) {
  materials = std::move(_materials);
}
Material Recipe::getMaterialByName(const QString &name) {
  for(auto material : materials) {
    if(QString::compare(material.getName(), name) == 0) {
      return material;
    }
  }

  return Material(0);
}
const QList<Component> &Recipe::getComponents() const {
  return components;
}
void Recipe::setComponents(QList<Component> _components) {
  components = std::move(_components);
}
Component Recipe::getComponentByName(const QString &name) {
  for(auto comp : components) {
    if(QString::compare(comp.getComponentName(), name) == 0) {
      return comp;
    }
  }

  return {0, 0, 0, QString(), QString(), 0, 0};
}
