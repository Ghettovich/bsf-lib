#include "recipe.h"
#include <QtCore/QJsonArray>

Recipe::Recipe(int id)
    : id(id)
{
}

int Recipe::getId() const
{
    return id;
}

const QString &Recipe::getDescription() const
{
    return description;
}

void Recipe::setDescription(const QString &_description)
{
    description = _description;
}

void Recipe::updateWeightForComponent(int componentId, int weight)
{
    actualComponentMap.insert(componentId, weight);
}

void Recipe::initComponentMaps()
{

    for (const auto &comp: componentList) {
        actualComponentMap.insert(comp.getComponentId(), 0);
        targetComponentMap.insert(comp.getComponentId(), comp.getTargetWeight());
    }
}

bool Recipe::isRecipeTargetMet()
{
    int targetsMet = 0;
    QMapIterator<int, int> i(targetComponentMap);

    while (i.hasNext()) {
        i.next();
        if (actualComponentMap.contains(i.key())) {
            if (actualComponentMap.value(i.key()) ==
                targetComponentMap.find(i.key()).value()) {
                targetsMet++;
            }
        }
    }

    return (targetsMet == targetComponentMap.size());
}

int Recipe::getActualWeightForComponent(int componentId) const
{
    return actualComponentMap.contains(componentId) ?
           actualComponentMap.find(componentId).value() : -1;
}

void Recipe::updateComponents(const QVector<Component> &compList)
{
    for (const auto &comp: compList) {
        if (targetComponentMap.contains(comp.getComponentId())) {
            updateWeightForComponent(comp.getComponentId(), comp.getTargetWeight());
        }
    }
}

Component::COMPONENT Recipe::getSelectedComponent() const
{
    return selectedComponent;
}

void Recipe::setSelectedComponent(Component::COMPONENT _component)
{
    selectedComponent = _component;
}
