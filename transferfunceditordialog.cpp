#include "transferfunceditordialog.h"

TransferFuncEditorDialog::TransferFuncEditorDialog(QWidget* parent)
    : QWidget(parent, Qt::Window)
{
    this->resize(200, 120);
    this->setWindowTitle("Transfer function editor");

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    this->setSizePolicy(sizePolicy1);
    QGridLayout* verticalLayout = new QGridLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton* showColorDialogButton = new QPushButton(QString::fromUtf8("Show Color Dialog"), this);
    showColorDialogButton->setGeometry(QRect(10, 120, 171, 24));
    colorDialogWidget = new QColorDialog(this);
    colorDialogWidget->setGeometry(QRect(1000, 120, 400, 300));
    colorDialogWidget->show();

    verticalLayout->addWidget(showColorDialogButton, 0,0);
    verticalLayout->addWidget(colorDialogWidget);
    setLayout(verticalLayout);
}

TransferFuncEditorDialog::~TransferFuncEditorDialog()
{
    delete colorDialogWidget;
}


void TransferFuncEditorDialog::closeEvent(QCloseEvent* event)
{
    colorDialogWidget->close();
}