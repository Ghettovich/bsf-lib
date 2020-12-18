#include "ui_groupboxbinrecipestatus.h"
#include "GroupBoxBinRecipeStatus.h"

GroupBoxBinRecipeStatus::GroupBoxBinRecipeStatus(MqttClient *_m_client) :
        m_client(_m_client)
        , ui(new Ui::GroupBoxBinRecipeStatus){
    ui->setupUi(this);
}

GroupBoxBinRecipeStatus::~GroupBoxBinRecipeStatus() {
    delete ui;
}
