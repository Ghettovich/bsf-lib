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

