#ifndef RECIPESTATUSINTERFACE_H
#define RECIPESTATUSINTERFACE_H

#include <QWidget>
#include <QtPlugin>
#include <weightcensor.h>

class RecipeStatusInterface : public QWidget {
 Q_OBJECT

 public:
  virtual void onUpdateIODevice(WeightSensor *ioDevice) = 0;
};

#define RecipeStatusInterface_iid "plugins.RecipeStatusInterface"

Q_DECLARE_INTERFACE(RecipeStatusInterface, RecipeStatusInterface_iid)

#endif //RECIPESTATUSINTERFACE_H
