#ifndef BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_
#define BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_

#include <QWidget>
#include <QTabWidget>

namespace Ui {
class TabWidgetCreateBatch;
}

class TabWidgetCreateBatch : public QTabWidget {

 Q_OBJECT

 public:
  explicit TabWidgetCreateBatch(QWidget *parent = nullptr);

 private:
  Ui::TabWidgetCreateBatch *ui = nullptr;
};

#endif //BSF_LIB_SRC_TABWIDGETCREATEBATCH_H_
