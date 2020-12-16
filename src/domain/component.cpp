
#include "component.h"

Component::Component(int id)
    : componentId(id)
{
}

Component::Component(int componentId, int recipeId)
    : componentId(componentId), recipeId(recipeId)
{
}

int Component::getComponentId() const
{
    return componentId;
}

void Component::setComponentId(int _componentId)
{
    Component::componentId = _componentId;
}

int Component::getRecipeId() const
{
    return recipeId;
}

const QString &Component::getComponent() const
{
    return component;
}

void Component::setComponent(const QString &_component)
{
    Component::component = _component;
}

int Component::getTargetWeight() const
{
    return targetWeight;
}

void Component::setTargetWeight(int _targetWeight)
{
    targetWeight = _targetWeight;
}

int Component::getCurrentWeight() const
{
    return currentWeight;
}
void Component::setCurrentWeight(int _currentWeight)
{
    currentWeight = _currentWeight;
}

Component::COMPONENT Component::getRecipeComponent() const
{
    return recipeComponent;
}

void Component::setRecipeComponent(Component::COMPONENT _recipeComponent)
{
    recipeComponent = _recipeComponent;
}
Component::COMPONENT Component::identifyComponent(int componentType) const
{
    switch (componentType) {
        case Component::WATER :
            return WATER;
        case Component::SAND :
            return SAND;
        case Component::PLASTIFIER :
            return PLASTIFIER;
        default:
            return UNKNOWN_COMP;
    }
}
int Component::getMarginValue() const
{
    return marginValue;
}
void Component::setMarginValue(int _marginValue)
{
    marginValue = _marginValue;
}
