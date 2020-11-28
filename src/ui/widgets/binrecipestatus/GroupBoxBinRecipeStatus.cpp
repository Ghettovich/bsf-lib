#include "ui_groupboxbinrecipestatus.h"
#include "GroupBoxBinRecipeStatus.h"

GroupBoxBinRecipeStatus::GroupBoxBinRecipeStatus(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , ui(new Ui::GroupBoxBinRecipeStatus){
    ui->setupUi(this);
}

GroupBoxBinRecipeStatus::~GroupBoxBinRecipeStatus() {
    delete ui;
}
