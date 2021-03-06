#ifndef BSF_LIB_GROUPBOXRECIPECONFIG_H
#define BSF_LIB_GROUPBOXRECIPECONFIG_H

namespace Ui {
class GroupBoxRecipeConfig;
}

#include <recipe.h>
#include <MqttClient.h>
#include <QObject>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>

class GroupBoxRecipeConfig : public QWidget {

 Q_OBJECT

 public:
  explicit GroupBoxRecipeConfig(MqttClient *_m_client);
  virtual ~GroupBoxRecipeConfig();

 public slots:
  void onChangeRecipeComboBox(int index);
  void onClickButtonPublishRecipe();

 private:
  Recipe selectedRecipe;
  MqttClient *m_client;
  Ui::GroupBoxRecipeConfig *ui = nullptr;
  void init();
  void createRecipeComboBox();
  void createRecipeComponentsTable();

  signals:
};

#endif //BSF_LIB_GROUPBOXRECIPECONFIG_H
