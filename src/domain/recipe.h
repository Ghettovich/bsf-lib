#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H


#include "component.h"
#include <QtCore/QString>
#include <QtCore/QJsonObject>

class Recipe
{

public:
    Recipe(int id = 0);
    int getId() const;
    int getActualWeightForComponent(int componentId) const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    Component::COMPONENT getSelectedComponent() const;
    void setSelectedComponent(Component::COMPONENT);
    QVector<Component> componentList;
    QMap<int, int> targetComponentMap;
    QMap<int, int> actualComponentMap;
    void updateWeightForComponent(int, int);
    void initComponentMaps();
    void addComponent(const Component& c);
    void updateComponents(const QVector<Component> &compList);
    bool isRecipeTargetMet();
    void findComponentWithId(int componentId, Component &component);

private:
    int id = 0;
    Component::COMPONENT selectedComponent;
    QString description;

};
#endif //BSF_RECIPE_H
