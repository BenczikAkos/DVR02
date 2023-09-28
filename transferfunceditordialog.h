#pragma once
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>
#include "transferfunceditorcanvas.h"

namespace Ui {
    class TransferFuncEditorDialog;
}

class TransferFuncEditorDialog : public QWidget
{
    Q_OBJECT

public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
 
protected:
    void closeEvent(QCloseEvent* event) override;
private:
    std::unique_ptr <QColorDialog> colorDialogWidget;
    std::unique_ptr<TransferFuncEditorCanvas> transferFuncCanvas;
};

