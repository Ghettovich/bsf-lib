#ifndef BSF_COMPONENTREPO_H
#define BSF_COMPONENTREPO_H

#include <domain/component.h>
#include <data/bsfdatabaseconfig.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ComponentRepo
{

public:
    ComponentRepo(const QString &connection = "");
    Component getComponentFromRecipe(int recipeId, int componentId);
    QVector<Component> getComponentsFromRecipe(int);

private:
    BsfDbconfig bsfDbConfig;
};


#endif //BSF_COMPONENTREPO_H
