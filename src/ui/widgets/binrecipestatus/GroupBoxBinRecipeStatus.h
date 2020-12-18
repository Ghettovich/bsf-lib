#ifndef BSF_LIB_GROUPBOXBINRECIPESTATUS_H
#define BSF_LIB_GROUPBOXBINRECIPESTATUS_H

namespace Ui {
    class GroupBoxBinRecipeStatus;
}

#include <MqttClient.h>
#include <QObject>
#include <QtWidgets/QWidget>

class GroupBoxBinRecipeStatus : public QWidget {

    Q_OBJECT

public:
    explicit GroupBoxBinRecipeStatus(MqttClient *m_client);
    virtual ~GroupBoxBinRecipeStatus();

private:
    Ui::GroupBoxBinRecipeStatus *ui = nullptr;
    MqttClient *m_client = nullptr;
};


#endif //BSF_LIB_GROUPBOXBINRECIPESTATUS_H
