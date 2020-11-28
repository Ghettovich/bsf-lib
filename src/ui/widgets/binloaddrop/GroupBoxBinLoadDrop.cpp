#include "ui_groupboxbinloaddrop.h"
#include "GroupBoxBinLoadDrop.h"

GroupBoxBinLoadDrop::~GroupBoxBinLoadDrop() {
    delete ui;
}

GroupBoxBinLoadDrop::GroupBoxBinLoadDrop(QWidget *parent, const Qt::WindowFlags &f)  :
        QWidget(parent, f)
        , ui(new Ui::GroupBoxBinLoadDrop)  {
    ui->setupUi(this);
}
