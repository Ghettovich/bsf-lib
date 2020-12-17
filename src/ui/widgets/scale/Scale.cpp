#include "ui_scale.h"
#include "Scale.h"
#include <weightcensor.h>
#include <BsfWidgetEnum.h>

Scale::Scale(MqttClient *_m_client) :
    ui(new Ui::Scale), m_client(_m_client)
{
    ui->setupUi(this);
    QVariant formId = WIDGET_TYPES::SCALE_1;
    this->setProperty("formId", formId);

    weightSensor = new WeightSensor(1, IODevice::LOW);
}
Scale::~Scale()
{
    delete ui;
}
void Scale::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{
}
void Scale::onUpdateIODevice(const IODevice *ioDevice)
{
    if(ioDevice->getId() == weightSensor->getId()) {
        qDebug() << "Scale id match";
    }
}
void Scale::onSelectRecipeChanged(const Recipe &recipe)
{
    selectedRecipe = Recipe(recipe.getId());
    selectedRecipe.setDescription(recipe.getDescription());

    for(const auto& comp : recipe.componentList) {
        selectedRecipe.addComponent(comp);
    }

    createRecipeComponentTableWidget();
}
void Scale::createRecipeComponentTableWidget()
{
    if (ui->tableWidget->rowCount() > 0) {
        ui->tableWidget->setRowCount(0);
    }

    if(ui->tableWidget->columnCount() == 0) {
        auto headers = QStringList() << "Component" << "Target" << "Current" << "Margin %";
        ui->tableWidget->setColumnCount(headers.size());
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    for (int i = 0; i < selectedRecipe.componentList.size(); ++i) {
        const auto &comp = selectedRecipe.componentList.at(i);
        ui->tableWidget->insertRow(i);

        auto tableWidgetItem = new QTableWidgetItem(comp.getComponent(), Qt::DisplayRole);
        tableWidgetItem->setData(Qt::UserRole, comp.getComponentId());

        ui->tableWidget->setItem(i, 0, tableWidgetItem);

        tableWidgetItem = new QTableWidgetItem(QString::number(comp.getTargetWeight()), Qt::DisplayRole);
        tableWidgetItem->setTextAlignment(Qt::AlignRight);
        ui->tableWidget->setItem(i, 1, tableWidgetItem);

        tableWidgetItem = new QTableWidgetItem(QString::number(0), Qt::DisplayRole);
        tableWidgetItem->setTextAlignment(Qt::AlignRight);
        ui->tableWidget->setItem(i, 2, tableWidgetItem);

        tableWidgetItem = new QTableWidgetItem(QString::number(comp.getMarginValue()), Qt::DisplayRole);
        tableWidgetItem->setTextAlignment(Qt::AlignRight);
        ui->tableWidget->setItem(i, 3, tableWidgetItem);
    }
}
