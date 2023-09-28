#include "transferfunceditordialog.h"

TransferFuncEditorDialog::TransferFuncEditorDialog(QWidget* parent)
    : QWidget(parent)
{
    this->resize(800, 600);
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton* showColorDialogButton = new QPushButton("Show Color Dialog", this);
    colorDialogWidget = new QColorDialog(this);
    colorDialogWidget->show();

    verticalLayout->addWidget(showColorDialogButton);
    verticalLayout->addWidget(colorDialogWidget);
    setLayout(verticalLayout);
}
