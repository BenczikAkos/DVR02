#pragma once
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
    class TransferFuncEditorDialog;
}

class TransferFuncEditorDialog : public QWidget
{
public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
 
protected:
    void closeEvent(QCloseEvent* event) override;
private:
    QColorDialog* colorDialogWidget;
};

