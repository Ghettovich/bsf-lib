#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <recipe.h>
#include <bsfdatabaseconfig.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class RecipeRepository
{

public:
    explicit RecipeRepository(const QString &connection = "");
    Recipe getRecipe(int);
    Recipe getRecipeWithComponents(int);
    QVector<Recipe> getRecipes();

private:
    BsfDbconfig bsfDbConfig;
    void addComponent(Component &, QVector<Component> &, QSqlQuery &);

};
#endif //BSF_RECIPEREPO_H
