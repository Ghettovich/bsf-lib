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

  return {0, 0, QString(), QString()};
}
const QList<Component> &Recipe::getComponents() const {
  return components;
}
void Recipe::setComponents(QList<Component> _components) {
  components = std::move(_components);
}
double Recipe::calculateRecipeTotalWeight() {
  double total = 0.00;

  for (const auto &comp : components) {
    total += comp.getWeight();
  }

  for (const auto &mat : materials) {
    total += mat.getWeight();
  }

  return total;
}
Component Recipe::getComponentByName(const QString &name) {
  for(auto comp : components) {
    if(QString::compare(comp.getComponentName(), name) == 0) {
      return comp;
    }
  }

  return {0, 0, 0, QString(), QString(), 0, 0};
}
void Recipe::updateComponentByName(const QString &name, double weight) {
  for (auto &comp : components) {
    if(QString::compare(comp.getComponentName(), name) == 0) {
      comp.setWeight(weight);

      break;
    }
  }
}
void Recipe::updateMaterialByName(const QString &name, double weight) {
  for (auto &material : materials) {
    if(QString::compare(material.getName(), name) == 0) {
      material.setWeight(weight);

      break;
    }
  }
}
void Recipe::updateComponentRatio(const QString &name, double ratio) {
  for (auto &comp : components) {
    if(QString::compare(comp.getComponentName(), name) == 0) {
      comp.setRatio(ratio);

      break;
    }
  }
}
double Recipe::getErrorMargin() const {
  return errorMargin;
}
void Recipe::setErrorMargin(double _errorMargin) {
  errorMargin = _errorMargin;
}
void Recipe::setIntegrationFactor(double factor) {
  integrationFactor = factor;
}
double Recipe::getIntegrationFactor() const {
  return integrationFactor;
}
