#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include "component.h"
#include <QtCore/QVector>
#include <QtCore/QString>

class Recipe {

 public:
  explicit Recipe(int id = 0);
  int getId() const;
  const QString &getDescription() const;
  void setDescription(const QString &_description);
  int getTargetWeightForComponent(int componentId);
  Component getComponent(int componentId);
  void updateComponentWeight(int componentId, int weight);
  bool isRecipeTargetMet();
  QVector<Component> componentList;

 private:
  int id = 0;
  QString description;

};
#endif //BSF_RECIPE_H
