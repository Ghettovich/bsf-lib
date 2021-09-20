#ifndef BSF_COMPONENT_H
#define BSF_COMPONENT_H

#include <QObject>
#include <QtCore/QString>

class Component {

 Q_GADGET

 public:
  Component(int id,
            int component_id,
            int recipe_id,
            QString name,
            QString description,
            int weight,
            float ratio);
  int getId();
  int getComponentId() const;
  void setComponentId(int _componentId);
  int getRecipeId() const;
  void setRecipeId(int recipeId);
  const QString &getComponentName() const;
  void setComponentName(const QString &name);
  const QString &getComponentDescription() const;
  void setComponentDescription(const QString &description);
  int getWeight() const;
  void setWeight(int targetWeight);
  int getCurrentWeight() const;
  void setCurrentWeight(int currentWeight);
  float getRatio() const;
  void setRatio(float ratio);

 private:
  int id;
  int componentId;
  int recipeId = 0;
  QString name = "";
  QString description = "";
  int weight, currentWeight = 0;
  float ratio;

};

#endif //BSF_COMPONENT_H
