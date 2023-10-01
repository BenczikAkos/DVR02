#include "transferfunceditordialog.h"

TransferFuncEditorDialog::TransferFuncEditorDialog(QWidget* parent)
    : QWidget(parent, Qt::Window),
    funcProperty(std::make_shared<TransferFuncProperty>())
{
    this->resize(800, 200);
    this->setWindowTitle("Transfer function editor");
    this->setGeometry(700, 600, 800, 200);

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    this->setSizePolicy(sizePolicy1);
    QGridLayout* verticalLayout = new QGridLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton* showColorDialogButton = new QPushButton(QString::fromUtf8("Show Color Dialog"), this);
    showColorDialogButton->setGeometry(QRect(10, 120, 171, 24));

    transferFuncCanvas = std::make_unique<TransferFuncEditorCanvas>(this, funcProperty);

    colorDialogWidget = std::make_unique<QColorDialog>(this);
    colorDialogWidget->setOptions(QColorDialog::NoButtons);
    colorDialogWidget->setGeometry(QRect(1000, 120, 400, 300));
    colorDialogWidget->show();

    verticalLayout->addWidget(transferFuncCanvas.get());
    verticalLayout->addWidget(showColorDialogButton);
    verticalLayout->addWidget(colorDialogWidget.get());
    setLayout(verticalLayout);

    //signals
    QObject::connect(colorDialogWidget.get(), SIGNAL(currentColorChanged(const QColor&)), this, SLOT(colorChanged(const QColor&)));
    QObject::connect(this, SIGNAL(colorChangedAt(int, QColor)), funcProperty.get(), SLOT(colorChangedAt(int, QColor)));
    //QObject::connect(transferFuncCanvas.get(), SIGNAL(selectedPointColor(const QColor&)), colorDialogWidget.get(), SLOT(QColorDialog::setCurrentColor(const QColor&)));
}

void TransferFuncEditorDialog::colorChanged(const QColor& newColor)
{
    int activePointIndex = transferFuncCanvas->getActivePointIndex();
    if(activePointIndex >= 0)
    {
        emit colorChangedAt(transferFuncCanvas->getActivePointIndex(), newColor);
    }
}


void TransferFuncEditorDialog::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event)
    colorDialogWidget->close();
}