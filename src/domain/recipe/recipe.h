#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <QMap>
#include <QtCore/QString>

#include <material/material.h>
#include <component/component.h>

class Recipe {

 public:
  explicit Recipe(int id = 0);
  int getId() const;
  const QString &getTitle() const;
  void setTitle(const QString &title);
  const QString &getDescription() const;
  void setDescription(const QString &description);
  const QList<Material> &getMaterials() const;
  void setMaterials(QList<Material> materials);
  const QList<Component> &getComponents() const;
  void setComponents(QList<Component> components);

  Material getMaterialByName(const QString &name);
  Component getComponentByName(const QString &name);

 private:
  int id = 0;
  QString title;
  QString description;
  QList<Material> materials;
  QList<Component> components;

};
#endif //BSF_RECIPE_H
