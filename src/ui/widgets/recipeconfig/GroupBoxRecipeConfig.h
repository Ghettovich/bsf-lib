#ifndef BSF_LIB_GROUPBOXRECIPECONFIG_H
#define BSF_LIB_GROUPBOXRECIPECONFIG_H

#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>

#include <recipe/recipe.h>
#include <appservice.broker/broker.appservice.h>
#include <appservice.prepare.recipe/preparerecipeappservice.h>

namespace Ui {
class GroupBoxRecipeConfig;
}

class GroupBoxRecipeConfig : public QWidget {
 Q_OBJECT

 public:
  explicit GroupBoxRecipeConfig(std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                                std::shared_ptr<appservice::PrepareRecipeAppService> &prepareRecipeAppService,
                                QWidget *parent = nullptr);
  virtual ~GroupBoxRecipeConfig();

 public slots:
  void onChangeRecipeComboBox(int index);
  void onClickButtonPublishRecipe();

 private:
  Recipe selectedRecipe;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  std::shared_ptr<appservice::PrepareRecipeAppService> prepareRecipeAppService;
  Ui::GroupBoxRecipeConfig *ui = nullptr;
  void init();
  void createRecipeComboBox();
  void createRecipeComponentsTable();

 signals:
};

#endif //BSF_LIB_GROUPBOXRECIPECONFIG_H
