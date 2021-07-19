#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <QtCore/QVector>
#include <QtCore/QString>

#include <component/component.h>

class Recipe {

  Q_GADGET

 public:
  explicit Recipe(int id = 0);
  int getId() const;
  const QString &getDescription() const;
  void setDescription(const QString &_description);
  int getTargetWeightForComponent(int componentId);
  Component getComponent(int componentId);
  void updateComponentWeight(int componentId, int weight);
  bool isRecipeTargetMet();
  int getSumOfCurrentWeight();
  int getSumOfTargetWeight();
  QVector<Component> componentList;

 private:
  int id = 0;
  QString description;

};
#endif //BSF_RECIPE_H
