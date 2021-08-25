#ifndef BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_
#define BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_

#include <QWidget>

namespace Ui {
class Home;
}

class Home : public QWidget {
  Q_OBJECT

 public:
  explicit Home(QWidget *parent = nullptr);
  virtual ~Home();

 private:
  Ui::Home *ui = nullptr;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_
