#ifndef BSF_LIB_GROUPBOXRECIPECONFIG_H
#define BSF_LIB_GROUPBOXRECIPECONFIG_H

namespace Ui {
    class GroupBoxRecipeConfig;
}

#include <QObject>
#include <QtWidgets/QWidget>

class GroupBoxRecipeConfig : public QWidget {

Q_OBJECT

public:
    GroupBoxRecipeConfig(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~GroupBoxRecipeConfig();

private:
    Ui::GroupBoxRecipeConfig *ui = nullptr;
};


#endif //BSF_LIB_GROUPBOXRECIPECONFIG_H
