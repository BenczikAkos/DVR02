#pragma once
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
    class TransferFuncEditorDialog;
}

class TransferFuncEditorDialog : public QWidget
{
    Q_OBJECT

public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
    ~TransferFuncEditorDialog();
 
protected:
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:
    QColorDialog* colorDialogWidget = nullptr;
};

