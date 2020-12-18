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
#include <QtWidgets/QWidget>

class Scale: public RecipeStatusInterface
{
    Q_OBJECT
    Q_INTERFACES(RecipeStatusInterface)

public:
    explicit Scale(MqttClient *_m_client);
    virtual ~Scale();

public slots:
    void onSelectRecipeChanged(const Recipe &recipe);
    void onUpdateIODevice(const WeightSensor *sensor) override;

private:
    Ui::Scale *ui = nullptr;
    MqttClient *m_client = nullptr;
    IODevice *weightSensor = nullptr;
    Recipe selectedRecipe;
    Component activeComponent;

    void createRecipeComponentTableWidget();
    void setQLcdNumberDisplay();
};


#endif //SCALE_H
