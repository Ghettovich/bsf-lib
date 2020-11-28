#ifndef BSF_LIB_GROUPBOXBINLOADDROP_H
#define BSF_LIB_GROUPBOXBINLOADDROP_H

namespace Ui {
    class GroupBoxBinLoadDrop;
}

#include <QObject>
#include <QtWidgets/QWidget>

class GroupBoxBinLoadDrop : public QWidget {

    Q_OBJECT

public:
    explicit GroupBoxBinLoadDrop(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~GroupBoxBinLoadDrop();

private:
    Ui::GroupBoxBinLoadDrop *ui = nullptr;
};


#endif //BSF_LIB_GROUPBOXBINLOADDROP_H
