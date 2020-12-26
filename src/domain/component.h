#ifndef BSF_COMPONENT_H
#define BSF_COMPONENT_H

#include <QObject>
#include <QtCore/QString>

class Component {

 Q_GADGET

 public:
  enum COMPONENT {
    UNKNOWN_COMP = -1,
    WATER = 1,
    SAND = 2,
    PLASTIFIER = 3
  };

  Q_ENUM(COMPONENT);

  explicit Component(int id = 0);
  Component(int componentId, int recipeId);
  int getComponentId() const;
  void setComponentId(int _componentId);
  int getRecipeId() const;
  void setRecipeId(int recipeId);
  const QString &getComponent() const;
  void setComponent(const QString &_component);
  int getTargetWeight() const;
  void setTargetWeight(int targetWeight);
  int getCurrentWeight() const;
  void setCurrentWeight(int currentWeight);
  int getMarginValue() const;
  void setMarginValue(int marginValue);
  bool isTargetMet() const;

  COMPONENT getRecipeComponent() const;
  void setRecipeComponent(COMPONENT);
  COMPONENT identifyComponent(int) const;

 private:
  int componentId;
  int recipeId = 0;
  QString component = "";
  int targetWeight = 0;
  int currentWeight = 0;
  int marginValue = 0;
  COMPONENT recipeComponent;
};

#endif //BSF_COMPONENT_H
