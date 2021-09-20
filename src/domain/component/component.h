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
            float weight,
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
  float getWeight() const;
  void setWeight(float targetWeight);
  float getCurrentWeight() const;
  void setCurrentWeight(float currentWeight);
  float getRatio() const;
  void setRatio(float ratio);

 private:
  int id;
  int componentId;
  int recipeId = 0;
  QString name = "";
  QString description = "";
  float weight, currentWeight = 0;
  float ratio;

};

#endif //BSF_COMPONENT_H
