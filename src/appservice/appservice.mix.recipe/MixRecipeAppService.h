#ifndef BSF_MIXRECIPEAPPSERVICE_H_
#define BSF_MIXRECIPEAPPSERVICE_H_

#include <memory>

#include <QObject>
#include <iodevice/iodeviceservice.h>

namespace appservice {
class MixRecipeAppService;
}

class appservice::MixRecipeAppService : public QObject {
 Q_OBJECT

 public:
  explicit MixRecipeAppService(std::shared_ptr<IODeviceService> &deviceService, QObject *parent = nullptr);

 private:
  std::shared_ptr<IODeviceService> deviceService;

};

#endif //BSF_MIXRECIPEAPPSERVICE_H_
