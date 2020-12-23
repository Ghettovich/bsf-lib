#include "ui_scale.h"
#include "Scale.h"
#include <reciperepo.h>
#include <weightcensor.h>
#include <BsfWidgetEnum.h>

Scale::Scale(MqttClient *_m_client) :
    ui(new Ui::Scale), m_client(_m_client)
{
    ui->setupUi(this);
    QVariant formId = WIDGET_TYPES::SCALE_1;
    this->setProperty("formId", formId);

    weightSensor = new WeightSensor(1, IODevice::LOW);
    activeComponentTableWidget = new QTableWidgetItem;

    init();
}
Scale::~Scale()
{
    delete ui;
}
void Scale::init()
{
    connect(ui->pushButtonTareScale, &QPushButton::clicked
    , this, &Scale::onClickPushButtonTare);

    connect(ui->pushButtonClearRecipe, &QPushButton::clicked
        , this, &Scale::onClickPushButtonClearRecipe);

    connect(ui->pushButtonConfirmRecipe, &QPushButton::clicked
        , this, &Scale::onClickPushButtonConfirmRecipe);
}
void Scale::onUpdateIODevice(const WeightSensor *sensor)
{
    if(sensor->getId() == weightSensor->getId()) {

        if(sensor->getComponent().getRecipeId() != configuredRecipe.getId()) {
            RecipeRepository recipeRepository;
            configuredRecipe = recipeRepository.getRecipeWithComponents(sensor->getComponent().getRecipeId());
            createRecipeComponentTableWidget();
        }

        if(activeComponent.getComponentId() != sensor->getComponent().getComponentId() ||
            sensor->getComponent().getRecipeId() != activeComponent.getRecipeId()) {

            for (const auto &comp: configuredRecipe.componentList) {
                if(comp.getComponentId() == sensor->getComponent().getComponentId()) {
                    //activeComponent = comp;
                    activeComponent.setComponentId(sensor->getComponent().getComponentId());
                    activeComponent.setRecipeId(sensor->getComponent().getRecipeId());
                    activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
                    break;
                }
            }

            updateComponentWidgetTable();

        } else if(activeComponent.getComponentId() == sensor->getComponent().getComponentId()) {
            activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
            activeComponentTableWidget->setText(QString::number(activeComponent.getCurrentWeight()));
        }

        configuredRecipe.updateWeightForComponent(sensor->getComponent().getComponentId()
            , sensor->getComponent().getCurrentWeight());

        setQLcdNumberDisplay();

        // SIGNALS
        emit receivedComponent(activeComponent);
    }
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

    for (int i = 0; i < configuredRecipe.componentList.size(); ++i) {
        const auto &comp = configuredRecipe.componentList.at(i);
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

        if(comp.getComponentId() == activeComponent.getComponentId()) {
            activeComponentTableWidget = tableWidgetItem;
        }
    }
}
void Scale::setQLcdNumberDisplay()
{
    ui->lcdNumber->display(activeComponent.getCurrentWeight());
}
void Scale::updateComponentWidgetTable()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

        if(ui->tableWidget->item(i, 0)->data(Qt::UserRole).toInt() == activeComponent.getComponentId()) {
            activeComponentTableWidget = ui->tableWidget->item(i, 2);
            activeComponentTableWidget->setData(Qt::UserRole, activeComponent.getComponentId());
            activeComponentTableWidget->setData(Qt::DisplayRole, activeComponent.getCurrentWeight());
            break;
        }
    }
}
void Scale::onClickPushButtonTare()
{

}
void Scale::onClickPushButtonClearRecipe()
{

}
void Scale::onClickPushButtonConfirmRecipe()
{

}