#include "ui_groupboxrecipeconfig.h"
#include "GroupBoxRecipeConfig.h"

GroupBoxRecipeConfig::GroupBoxRecipeConfig(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , ui(new Ui::GroupBoxRecipeConfig){
    ui->setupUi(this);
}

GroupBoxRecipeConfig::~GroupBoxRecipeConfig() {
    delete ui;
}
