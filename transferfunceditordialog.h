#pragma once
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>

namespace Ui {
    class TransferFuncEditorDialog;
}

class TransferFuncEditorDialog : public QWidget
{
public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
 
protected:
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:
    QColorDialog* colorDialogWidget;
};

