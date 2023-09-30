#include "transferfunceditordialog.h"

TransferFuncEditorDialog::TransferFuncEditorDialog(QWidget* parent)
    : QWidget(parent, Qt::Window)
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

    transferFuncCanvas = std::make_unique<TransferFuncEditorCanvas>(this);

    colorDialogWidget = std::make_unique<QColorDialog>(this);
    colorDialogWidget->setOptions(QColorDialog::NoButtons);
    colorDialogWidget->setGeometry(QRect(1000, 120, 400, 300));
    colorDialogWidget->show();

    verticalLayout->addWidget(transferFuncCanvas.get());
    verticalLayout->addWidget(showColorDialogButton);
    verticalLayout->addWidget(colorDialogWidget.get());
    setLayout(verticalLayout);
}


void TransferFuncEditorDialog::closeEvent(QCloseEvent* event)
{
    colorDialogWidget->close();
}