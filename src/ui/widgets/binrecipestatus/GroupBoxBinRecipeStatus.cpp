#include <BsfWidgetEnum.h>
#include <reciperepo.h>
#include "ui_groupboxbinrecipestatus.h"
#include "GroupBoxBinRecipeStatus.h"

GroupBoxBinRecipeStatus::GroupBoxBinRecipeStatus(MqttClient *_m_client) :
        m_client(_m_client)
        , ui(new Ui::GroupBoxBinRecipeStatus){
    ui->setupUi(this);

    QVariant formId = WIDGET_TYPES::SCALE_BIN;
    this->setProperty("formId", formId);

    scale1 = new WeightSensor(1, IODevice::LOW);
}

GroupBoxBinRecipeStatus::~GroupBoxBinRecipeStatus() {
    delete ui;
}
void GroupBoxBinRecipeStatus::onUpdateIODevice(const WeightSensor *sensor)
{
    if(scale1->getId() == sensor->getId()) {

        if(sensor->getComponent().getRecipeId() != selectedRecipe.getId()) {
            RecipeRepository recipeRepository;
            selectedRecipe = recipeRepository.getRecipeWithComponents(sensor->getComponent().getRecipeId());
            createRecipeComponentTableWidget();
        }

        if(activeComponent.getComponentId() != sensor->getComponent().getComponentId()) {
            activeComponent = Component(sensor->getComponent().getComponentId(),
                                        sensor->getComponent().getRecipeId());
            updateComponentWidgetTable();
        } else if(activeComponent.getComponentId() == sensor->getComponent().getComponentId()) {
            activeComponentTableWidget->setData(Qt::UserRole, activeComponent.getComponentId());
            activeComponentTableWidget->setData(Qt::DisplayRole, activeComponent.getCurrentWeight());
        }

        activeComponent.setCurrentWeight(sensor->getComponent().getCurrentWeight());
        setQLcdNumberDisplay();
    }
}
void GroupBoxBinRecipeStatus::createRecipeComponentTableWidget()
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

        if(comp.getComponentId() == activeComponent.getComponentId()) {
            activeComponentTableWidget = tableWidgetItem;
        }
    }
}
void GroupBoxBinRecipeStatus::setQLcdNumberDisplay()
{
    ui->lcdNumberBinRecipeWeight->display(activeComponent.getCurrentWeight());
}
void GroupBoxBinRecipeStatus::updateComponentWidgetTable()
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