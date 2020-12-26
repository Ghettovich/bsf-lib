#ifndef BSFWIDGETENUM_H
#define BSFWIDGETENUM_H

#include <QObject>
#include <QMetaType>
#include <QMetaEnum>

enum WIDGET_TYPES {
  TREEWIDGET_RELAY_STATUS,
  TREEWIDGET_PROXITY_STATUS,
  GROUPBOX_LIFT_UP_DOWN,
  GROUPBOX_BIN_LOAD_DROP,
  GROUPBOX_BELT_FEEDERS,
  GROUPBOX_RECIPE_CONFIG,
  SCALE_1,
  SCALE_BIN
};
Q_DECLARE_METATYPE(WIDGET_TYPES);

#endif //BSFWIDGETENUM_H
