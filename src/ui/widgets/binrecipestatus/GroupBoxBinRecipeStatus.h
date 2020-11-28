#ifndef BSF_LIB_GROUPBOXBINRECIPESTATUS_H
#define BSF_LIB_GROUPBOXBINRECIPESTATUS_H

namespace Ui {
    class GroupBoxBinRecipeStatus;
}

#include <QObject>
#include <QtWidgets/QWidget>

class GroupBoxBinRecipeStatus : public QWidget {

    Q_OBJECT

public:
    explicit GroupBoxBinRecipeStatus(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~GroupBoxBinRecipeStatus();

private:
    Ui::GroupBoxBinRecipeStatus *ui = nullptr;
};


#endif //BSF_LIB_GROUPBOXBINRECIPESTATUS_H
