#ifndef BSF_LIB_SRC_UI_LABELS_PROXIMITY_PROXIMITY_LABEL_H_
#define BSF_LIB_SRC_UI_LABELS_PROXIMITY_PROXIMITY_LABEL_H_

#include <QLabel>
#include <fonts/MaterialRegular.h>

class ProximityLabel : public QLabel {
 Q_OBJECT

 public:
  explicit ProximityLabel(QWidget *parent = nullptr);
  void updateProximityStatus(bool on);

 private:
  MaterialRegular materialRegular;
};

#endif //BSF_LIB_SRC_UI_LABELS_PROXIMITY_PROXIMITY_LABEL_H_
