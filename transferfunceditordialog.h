#pragma once
#include <QColorDialog>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
    class TransferFuncEditorDialog;
}

class TransferFuncEditorDialog : public QWidget
{
public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
 
private:
    QColorDialog* colorDialogWidget;
};

