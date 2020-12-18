#ifndef SCALE_H
#define SCALE_H

namespace Ui
{
class Scale;
}

#include <iodevice.h>
#include <weightcensor.h>
#include <MqttClient.h>
#include <fonts/MaterialRegular.h>
#include <widgets/interfaces/RecipeStatusInterface.h>
#include <QTableWidgetItem>
#include <QtWidgets/QWidget>

class Scale: public RecipeStatusInterface
{
    Q_OBJECT
    Q_INTERFACES(RecipeStatusInterface)

public:
    explicit Scale(MqttClient *_m_client);
    virtual ~Scale();

public slots:
    void onUpdateIODevice(const WeightSensor *sensor) override;

private:
    Ui::Scale *ui = nullptr;
    MqttClient *m_client = nullptr;
    IODevice *weightSensor = nullptr;
    QTableWidgetItem *activeComponentTableWidget = nullptr;
    Recipe configuredRecipe = Recipe(0);
    Component activeComponent = Component(0);

    void createRecipeComponentTableWidget();
    void setQLcdNumberDisplay();
    void updateComponentWidgetTable();
};


#endif //SCALE_H
