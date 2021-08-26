#ifndef BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
#define BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_

#include <QWidget>
#include <fonts/MaterialRegular.h>

namespace Ui {
class Experimental;
}

class Experimental : public QWidget {
 Q_OBJECT

 public:
  explicit Experimental(QWidget *parent = nullptr);
  virtual ~Experimental();

 public slots:
  void onUpdateLiftDown(bool off);
  void onUpdateLiftUp(bool off);

 private:
  Ui::Experimental *ui = nullptr;
  MaterialRegular materialRegular;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
