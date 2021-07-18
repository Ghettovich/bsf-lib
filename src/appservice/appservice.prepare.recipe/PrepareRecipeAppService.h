#ifndef BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_
#define BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_

#include <memory>
#include <QObject>
#include <iodevice/iodeviceservice.h>

namespace appservice {
class PrepareRecipeAppService;
}

class appservice::PrepareRecipeAppService : public QObject {
 Q_OBJECT

 public:
  explicit PrepareRecipeAppService(std::shared_ptr<IODeviceService> &deviceService, QObject *parent = nullptr);

 private:
  std::shared_ptr<IODeviceService> deviceService;
};

#endif //BSF_APP_SERVICES_PREPARERECIPEAPPSERVICE_H_
