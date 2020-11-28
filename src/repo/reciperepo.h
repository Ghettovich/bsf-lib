#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include <bsfdatabaseconfig.h>
#include <recipe.h>
#include <QtSql/QSqlDatabase>
#include <QtCore/QVector>

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
