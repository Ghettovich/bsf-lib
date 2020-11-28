#ifndef BSF_LIB_GROUPBOXBELTFEEDERS_H
#define BSF_LIB_GROUPBOXBELTFEEDERS_H

namespace Ui {
    class GroupBoxBeltFeeders;
}

#include <QObject>
#include <QtWidgets/QWidget>


class GroupBoxBeltFeeders : public QWidget {

    Q_OBJECT

public:
    explicit GroupBoxBeltFeeders();

private:
    Ui::GroupBoxBeltFeeders *ui = nullptr;
};


#endif //BSF_LIB_GROUPBOXBELTFEEDERS_H
