#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"

GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f) :
        QWidget(parent, f)
        , ui(new Ui::GroupBoxLiftUpDown) {
    ui->setupUi(this);
    init();
}

GroupBoxLiftUpDown::~GroupBoxLiftUpDown() {
    delete ui;
}

void GroupBoxLiftUpDown::init() {


    connect(ui->pushButtonLiftDown, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftDown);

    connect(ui->pushButtonLiftUp, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftUp);
}

void GroupBoxLiftUpDown::onClickPushButtonLiftDown() {
    printf("\ndown clicked");
}

void GroupBoxLiftUpDown::onClickPushButtonLiftUp() {
    printf("\nup clicked");
}

