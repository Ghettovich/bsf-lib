#ifndef BSF_COMPONENT_H
#define BSF_COMPONENT_H

#include <QtCore/QString>

class Component {

 public:
  Component(int id,
            int component_id,
            int recipe_id,
            QString name,
            QString description,
            double weight,
            double ratio);
  int getId();
  int getComponentId() const;
  void setComponentId(int _componentId);
  int getRecipeId() const;
  void setRecipeId(int recipeId);
  const QString &getComponentName() const;
  void setComponentName(const QString &name);
  const QString &getComponentDescription() const;
  void setComponentDescription(const QString &description);
  double getWeight() const;
  void setWeight(double targetWeight);
  double getCurrentWeight() const;
  void setCurrentWeight(double currentWeight);
  double getRatio() const;
  void setRatio(double ratio);

 private:
  int id;
  int componentId;
  int recipeId = 0;
  QString name = "";
  QString description = "";
  double weight, currentWeight = 0;
  double ratio;

};

#endif //BSF_COMPONENT_H
