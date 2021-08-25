#ifndef BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
#define BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_

#include <QWidget>

namespace Ui {
class Experimental;
}

class Experimental : public QWidget {
 Q_OBJECT

 public:
  explicit Experimental(QWidget *parent = nullptr);
  virtual ~Experimental();



 private:
  Ui::Experimental *ui = nullptr;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
