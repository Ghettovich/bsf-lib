#include "material.h"

#include <utility>

Material::Material(int id, double weight, QString name, QString description)
    : id(id), weight(weight), name(std::move(name)), description(std::move(description)) {}

int Material::getId() const {
  return id;
}
const QString &Material::getName() const {
  return name;
}
void Material::setName(const QString &_name) {
  name = _name;
}
const QString &Material::setDescription() const {
  return description;
}
void Material::setDescription(const QString &_description) {
  description = _description;
}
double Material::getWeight() const {
  return weight;
}
void Material::setWeight(double _weight) {
  weight = _weight;
}
