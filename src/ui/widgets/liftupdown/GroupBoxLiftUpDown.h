#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

namespace Ui {
    class GroupBoxLiftUpDown;
}

#include <QObject>
#include <QtWidgets/QWidget>

class GroupBoxLiftUpDown : public QWidget {

    Q_OBJECT

public:
    explicit GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f);
    void init();
    virtual ~GroupBoxLiftUpDown();

private:
    Ui::GroupBoxLiftUpDown *ui = nullptr;

private slots:
    void onClickPushButtonLiftDown();
    void onClickPushButtonLiftUp();

};


#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H
