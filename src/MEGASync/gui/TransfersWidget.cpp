#include "TransfersWidget.h"
#include "ui_TransfersWidget.h"
#include "MegaApplication.h"
#include <QTimer>

using namespace mega;

TransfersWidget::TransfersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransfersWidget)
{
    ui->setupUi(this);
    this->model = nullptr;
    tDelegate = nullptr;
    isPaused = false;
    app = (MegaApplication *)qApp;
}

void TransfersWidget::setupTransfers(std::shared_ptr<MegaTransferData> transferData, int type)
{
    this->type = type;
    model = new QActiveTransfersModel(type, transferData);

    connect(model, SIGNAL(noTransfers()), this, SLOT(noTransfers()));
    connect(model, SIGNAL(onTransferAdded()), this, SLOT(onTransferAdded()));

    noTransfers();
    configureTransferView();

    if ((type == MegaTransfer::TYPE_DOWNLOAD && transferData->getNumDownloads())
            || (type == MegaTransfer::TYPE_UPLOAD && transferData->getNumUploads()))
    {
        onTransferAdded();
    }
}

void TransfersWidget::setupFinishedTransfers(QList<MegaTransfer* > transferData, int modelType)
{
    this->type = modelType;
    model = new QFinishedTransfersModel(transferData, modelType);
    connect(model, SIGNAL(noTransfers()), this, SLOT(noTransfers()));
    connect(model, SIGNAL(onTransferAdded()), this, SLOT(onTransferAdded()));
    // Subscribe to MegaApplication for changes on finished transfers generated by other finished model to keep consistency
    connect(app, SIGNAL(clearAllFinishedTransfers()), model, SLOT(removeAllTransfers()));
    connect(app, SIGNAL(clearFinishedTransfer(int)),  model, SLOT(removeTransferByTag(int)));

    noTransfers();
    configureTransferView();

    if (transferData.size())
    {
        onTransferAdded();
    }
}

void TransfersWidget::refreshTransferItems()
{
    if (model) model->refreshTransfers();
}

void TransfersWidget::clearTransfers()
{
    if (model) model->removeAllTransfers();
}

TransfersWidget::~TransfersWidget()
{
    delete ui;
    delete tDelegate;
    delete model;
}

bool TransfersWidget::areTransfersActive()
{
    return model && model->rowCount(QModelIndex()) != 0;
}

void TransfersWidget::configureTransferView()
{
    if (!model)
    {
        return;
    }

    tDelegate = new MegaTransferDelegate(model, this);
    ui->tvTransfers->setup(type);
    ui->tvTransfers->setItemDelegate((QAbstractItemDelegate *)tDelegate);
    ui->tvTransfers->header()->close();
    ui->tvTransfers->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->tvTransfers->setDragEnabled(true);
    ui->tvTransfers->viewport()->setAcceptDrops(true);
    ui->tvTransfers->setDropIndicatorShown(true);
    ui->tvTransfers->setDragDropMode(QAbstractItemView::InternalMove);
    ui->tvTransfers->setModel(model);

    switch (type)
    {
        case QTransfersModel::TYPE_DOWNLOAD:
            ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_DOWNLOADS);
            break;
        case QTransfersModel::TYPE_UPLOAD:
            ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_UPLOADS);
            break;
        default:
            ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_TRANSFERS);
            break;
    }
}

void TransfersWidget::pausedTransfers(bool paused)
{
    isPaused = paused;
    if (model && model->rowCount(QModelIndex()) == 0)
    {
        noTransfers();
    }
    else
    {
        ui->sWidget->setCurrentWidget(ui->pTransfers);
    }
}

void TransfersWidget::disableGetLink(bool disable)
{
    ui->tvTransfers->disableGetLink(disable);
}

QTransfersModel *TransfersWidget::getModel()
{
    return model;
}

void TransfersWidget::noTransfers()
{
    if (isPaused)
    {
        ui->pNoTransfers->setState(TransfersStateInfoWidget::PAUSED);
    }
    else
    {
        switch (type)
        {
            case QTransfersModel::TYPE_DOWNLOAD:
                ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_DOWNLOADS);
                break;
            case QTransfersModel::TYPE_UPLOAD:
                ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_UPLOADS);
                break;
            default:
                ui->pNoTransfers->setState(TransfersStateInfoWidget::NO_TRANSFERS);
                break;
        }
    }

    ui->sWidget->setCurrentWidget(ui->pNoTransfers);
}

void TransfersWidget::onTransferAdded()
{
    ui->sWidget->setCurrentWidget(ui->pTransfers);
}

void TransfersWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}
