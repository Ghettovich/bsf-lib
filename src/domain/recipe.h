#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H


#include "component.h"
#include <QtCore/QMap>
#include <QtCore/QVector>
#include <QtCore/QString>

class Recipe
{

public:
    explicit Recipe(int id = 0);
    int getId() const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    QVector<Component> componentList;
    QMap<int, int> actualComponentMap;
    void updateWeightForComponent(int, int);
    int getTargetWeightForComponent(int componentId);

private:
    int id = 0;
    QString description;

};
#endif //BSF_RECIPE_H
