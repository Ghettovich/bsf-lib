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
#include <widgets/devicestatus/IOWidgetStatusInterface.h>
#include <QtWidgets/QWidget>

class Scale: public IOWidgetStatusInterface
{
    Q_OBJECT
    Q_INTERFACES(IOWidgetStatusInterface)

public:
    explicit Scale(MqttClient *_m_client);
    virtual ~Scale();

public slots:
    void onSelectRecipeChanged(const Recipe &recipe);
    void onUpdateIODevice(const IODevice *ioDevice) override;
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

private:
    Ui::Scale *ui = nullptr;
    MqttClient *m_client = nullptr;
    IODevice *weightSensor = nullptr;
    Recipe selectedRecipe;

    void createRecipeComponentTableWidget();
};


#endif //SCALE_H
