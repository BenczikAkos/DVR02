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
public slots:
    void colorChanged(const QColor& newColor);
signals:
    void colorChangedAt(int index, QColor newColor);
protected:
    void closeEvent(QCloseEvent* event) override;
private:
    std::shared_ptr<TransferFuncProperty> funcProperty;
    std::unique_ptr <QColorDialog> colorDialogWidget;
    std::unique_ptr<TransferFuncEditorCanvas> transferFuncCanvas;
};

