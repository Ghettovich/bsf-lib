#include "MainWindow.h"
#include <reciperepo.h>
#include <BsfWidgetEnum.h>
#include <widgets/scale/Scale.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new MqttClient(this);

    connect(m_client, &MqttClient::brokerConnected,
            this, &MainWindow::onCreateMqttClientSubscriptions);

    m_client->connectToHost();

    init();
    createStatusBar();
    createRecipeTreeWidget();
    createScale_1_Widget();
}

void MainWindow::init() {

    connect(ui->pushButtonRecipeDown, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonRecipeDown);
    ui->pushButtonRecipeDown->setIcon(materialRegular.arrowCircleDownIcon());

    connect(ui->pushButtonRecipeUp, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonRecipeUp);
    ui->pushButtonRecipeUp->setIcon(materialRegular.arrowCircleUpIcon());

    connect(ui->pushButtonRecipeChange, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonChangeRecipe);
    ui->pushButtonRecipeChange->setIcon(materialRegular.updateDisabledIcon());

    connect(ui->pushButtonComponentDown, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonComponentDown);
    ui->pushButtonComponentDown->setIcon(materialRegular.arrowCircleDownIcon());

    connect(ui->pushButtonComponentUp, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonComponentUp);
    ui->pushButtonComponentUp->setIcon(materialRegular.arrowCircleUpIcon());

    connect(ui->pushButtonConfirm, &QPushButton::clicked,
            this, &MainWindow::onClickPushButtonConfirmComponent);
    ui->pushButtonConfirm->setDisabled(true);
    ui->pushButtonConfirm->setIcon(materialRegular.updateDisabledIcon());

    QStringList headers;
    headers.append("Components");
    ui->componentTreeWidget->setHeaderLabels(headers);

    connect(ui->componentTreeWidget, &QTreeWidget::itemSelectionChanged
        , this, &MainWindow::onComponentTreeWidgetSelectionChanged);

    headers = QStringList();
    headers.append("Recipe");
    ui->recipeTreeWidget->setHeaderLabels(headers);

    connect(ui->recipeTreeWidget, &QTreeWidget::itemSelectionChanged
        , this, &MainWindow::onRecipeTreeWidgetChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createStatusBar()
{
    mainStatusBar = statusBar();
    mainStatusBar->showMessage(tr("Ready"));
}

void MainWindow::createRecipeTreeWidget()
{
    RecipeRepository recipeRepository;
    QList<QTreeWidgetItem *> recipeTreeWidgets = recipeRepository.getRecipesTreeWidgetList();

    ui->recipeTreeWidget->insertTopLevelItems(0, recipeTreeWidgets);

}
void MainWindow::createComponentsListWidget(const Recipe &recipe)
{
    ui->componentTreeWidget->clear();

    setChangeRecipeButtonState(true);

    for (int i = 0; i < recipe.componentList.size(); ++i) {
        const auto &comp = recipe.componentList.at(i);
        auto widgetItem = new QTreeWidgetItem(ui->componentTreeWidget, i);

        widgetItem->setData(0, Qt::UserRole, comp.getComponentId());
        widgetItem->setData(0, Qt::DisplayRole, comp.getComponent());
        widgetItem->setIcon(0, materialRegular.highlightOffIcon(Qt::red));

        ui->componentTreeWidget->insertTopLevelItem(i, widgetItem);

        if(comp.getComponentId() == activeComponent.getComponentId()) {
            ui->componentTreeWidget->setCurrentItem(ui->componentTreeWidget->topLevelItem(i));
            activeCompTreeWidgetItem = widgetItem;
        }
    }
}
void MainWindow::createScale_1_Widget()
{
    scale = new Scale(m_client);
    ui->gridLayout_2->addWidget(scale);

    connect(qobject_cast<Scale*>(scale), &Scale::receivedComponent,
            this, &MainWindow::onReceivedConfiguredComponent);
}
void MainWindow::onCreateMqttClientSubscriptions()
{
    quint8 QoS = 1;

    m_client->addRecipeDataSubscription(QoS, scale);
}
void MainWindow::onRecipeTreeWidgetChanged()
{
    int recipeId = ui->recipeTreeWidget->currentIndex().data(Qt::UserRole).toInt();

    RecipeRepository recipeRepository;
    selectedRecipe = recipeRepository.getRecipeWithComponents(recipeId);

    if(recipeId != configuredRecipe.getId()) {
        setChangeRecipeButtonState(false);
    } else {
        setChangeRecipeButtonState(true);
    }
}
void MainWindow::onComponentTreeWidgetSelectionChanged()
{
    if(ui->componentTreeWidget->currentIndex().isValid()) {

        int componentId = ui->componentTreeWidget->currentItem()->data(0, Qt::UserRole).toInt();

        if (activeComponent.getRecipeId() == configuredRecipe.getId()) {
            Component comp = configuredRecipe.getComponent(componentId);

            if (comp.getComponentId() != 0) {
                m_client->publishRecipe(configuredRecipe, comp);
            }
        }
    }
}

void MainWindow::onClickPushButtonRecipeDown()
{
    if(ui->recipeTreeWidget->currentIndex().isValid()) {
        auto indexes = ui->recipeTreeWidget->selectionModel()->selectedIndexes().first();

        if((indexes.row() + 1) < ui->recipeTreeWidget->topLevelItemCount()) {
            ui->recipeTreeWidget->setCurrentItem(ui->recipeTreeWidget->topLevelItem(indexes.row() + 1));
        }
    }
}
void MainWindow::onClickPushButtonRecipeUp()
{
    if(ui->recipeTreeWidget->currentIndex().isValid()) {
        auto indexes = ui->recipeTreeWidget->selectionModel()->selectedIndexes().first();

        if((indexes.row() - 1) < ui->recipeTreeWidget->topLevelItemCount()) {
            ui->recipeTreeWidget->setCurrentItem(ui->recipeTreeWidget->topLevelItem(indexes.row() - 1));
        }
    }
}
void MainWindow::onClickPushButtonChangeRecipe()
{
    m_client->publishRecipe(selectedRecipe);
}
void MainWindow::onClickPushButtonComponentDown()
{
    if(ui->componentTreeWidget->currentIndex().isValid()) {
        auto indexes = ui->componentTreeWidget->selectionModel()->selectedIndexes().first();

        if((indexes.row() + 1) < ui->componentTreeWidget->topLevelItemCount()) {
            ui->componentTreeWidget->setCurrentItem(ui->componentTreeWidget->topLevelItem(indexes.row() + 1));
        }
    }
}
void MainWindow::onClickPushButtonComponentUp()
{
    if(ui->componentTreeWidget->currentIndex().isValid()) {
        auto indexes = ui->componentTreeWidget->selectionModel()->selectedIndexes().first();

        if((indexes.row() - 1) >= 0) {
            ui->componentTreeWidget->setCurrentItem(ui->componentTreeWidget->topLevelItem(indexes.row() - 1));
        }
    }
}
void MainWindow::onClickPushButtonConfirmComponent()
{
    m_client->publishConfirmComponent(activeComponent);
    ui->componentTreeWidget->currentItem()->setDisabled(true);
    ui->pushButtonConfirm->setDisabled(true);
}
void MainWindow::onReceivedConfiguredComponent(const Component &component)
{

    if(configuredRecipe.getId() != component.getRecipeId()) {
        RecipeRepository recipeRepository;
        configuredRecipe = recipeRepository.getRecipeWithComponents(component.getRecipeId());

        activeComponent = configuredRecipe.componentList.first();
        selectItemInTreeWidgetWithId(ui->recipeTreeWidget, component.getRecipeId());

        createComponentsListWidget(configuredRecipe);
    }

    else if(configuredRecipe.getId() == component.getRecipeId() &&
        activeComponent.getComponentId() != component.getComponentId()) {

        activeComponent = configuredRecipe.getComponent(component.getComponentId());
        activeComponent.setCurrentWeight(component.getCurrentWeight());

        updateRecipeComponentsTable(activeComponent);

    } else {
        activeComponent.setCurrentWeight(component.getCurrentWeight());
        setActiveComponentTreeWidgetTargetsMet(activeCompTreeWidgetItem);
    }

    setConfirmComponentButtonState();
}
void MainWindow::setChangeRecipeButtonState(bool isRecipeIdEqual)
{
    if(isRecipeIdEqual) {
        ui->componentTreeWidget->setDisabled(false);
        ui->pushButtonRecipeChange->setDisabled(true);
        ui->pushButtonRecipeChange->setIcon(materialRegular.updateDisabledIcon());
    } else {
        ui->componentTreeWidget->setDisabled(true);
        ui->pushButtonRecipeChange->setDisabled(false);
        ui->pushButtonRecipeChange->setIcon(materialRegular.updateIcon());
    }
}
void MainWindow::setConfirmComponentButtonState()
{
    if(activeComponent.isTargetMet()) {
        ui->pushButtonConfirm->setDisabled(false);
        ui->pushButtonConfirm->setIcon(materialRegular.updateIcon());
    } else {
        ui->pushButtonConfirm->setDisabled(true);
        ui->pushButtonConfirm->setIcon(materialRegular.updateDisabledIcon());
    }
}
void MainWindow::setActiveComponentTreeWidgetTargetsMet(QTreeWidgetItem *item)
{
    if (activeComponent.isTargetMet()) {
        item->setIcon(0, materialRegular.checkCircleOutlineIcon(Qt::green));
    }
    else {
        item->setIcon(0, materialRegular.highlightOffIcon(Qt::red));
    }
}
void MainWindow::selectItemInTreeWidgetWithId(QTreeWidget *treeWidget, int id)
{
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        if(treeWidget->topLevelItem(i)->data(0, Qt::UserRole).toInt() == id) {
            treeWidget->setCurrentItem(treeWidget->topLevelItem(i));
            break;
        }
    }
}
void MainWindow::updateRecipeComponentsTable(const Component &component)
{
    for (int i = 0; i < ui->componentTreeWidget->topLevelItemCount(); ++i) {
        if(ui->componentTreeWidget->topLevelItem(i)->data(0, Qt::UserRole).toInt() == component.getComponentId()) {
            ui->componentTreeWidget->setCurrentItem(ui->componentTreeWidget->topLevelItem(i));

            setActiveComponentTreeWidgetTargetsMet(ui->componentTreeWidget->topLevelItem(i));
            activeCompTreeWidgetItem = ui->componentTreeWidget->topLevelItem(i);
            break;
        }
    }
}

