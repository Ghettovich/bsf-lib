#include "tst_GroupBoxRecipeConfig.h"
#include <QSignalSpy>
#include <widgets/recipeconfig/GroupBoxRecipeConfig.h>

void GroupBoxRecipeConfigTest::init() {
  m_client = new MqttClient(this, host);
  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void GroupBoxRecipeConfigTest::publishRecipe() {
  // ARRANGE
  auto groupboxRecipeConfig = new GroupBoxRecipeConfig(m_client);

  // ACT
  groupboxRecipeConfig->onChangeRecipeComboBox(0);
  groupboxRecipeConfig->onChangeRecipeComboBox(1);

  groupboxRecipeConfig->onClickButtonPublishRecipe();

  // ASSERT
  QVERIFY(groupboxRecipeConfig->isEnabled());
}

void GroupBoxRecipeConfigTest::cleanupTestCase() {
}

QTEST_MAIN(GroupBoxRecipeConfigTest);
