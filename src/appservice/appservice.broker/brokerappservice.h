#ifndef BSF_BROKERAPPSERVICE_H_
#define BSF_BROKERAPPSERVICE_H_

#include <memory>
#include <QObject>
#include <broker/BrokerService.h>
#include <iodevice/iodeviceservice.h>
#include <state/stateservice.h>

namespace appservice {
class BrokerAppService;
}

class appservice::BrokerAppService : public QObject {
 Q_OBJECT

 public:
  explicit BrokerAppService(std::shared_ptr<service::BrokerService> &brokerService,
                            std::shared_ptr<StateService> &stateService,
                            QObject *parent = nullptr);

  /// Connect to broker. Host is defined in configuration file.
  void connectToHost();

  /// Publish message to toggle a relay. @relayId is used to identify the relay.
  void toggleRelay(int relayId);

  /// Publish a recipe. @recipeId and @componentId are used to identify the selected recipe.
  /// @targetWeight is the amount of material needed to fulfill the recipe.
  void configureRecipe(int recipeId, int componentId, int targetWeight);

 public slots:
  /// Subscribe to broker. Topics hardcoded.
  void createDeviceStateSubscriptions();

 private:
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<StateService> stateService;

 signals:
  void connectedToHost();
};

#endif //BSF_BROKERAPPSERVICE_H_
