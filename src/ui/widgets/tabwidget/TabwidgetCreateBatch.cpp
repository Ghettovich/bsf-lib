#include "ui_tabwidgetcreatebatch.h"
#include "TabwidgetCreateBatch.h"

TabWidgetCreateBatch::TabWidgetCreateBatch(QWidget *parent) :
    ui(new Ui::TabWidgetCreateBatch), QTabWidget(parent) {
  ui->setupUi(this);
}
