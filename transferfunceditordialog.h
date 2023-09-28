#pragma once
#include <QColorDialog>
#include <QVBoxLayout>
#include <QPushButton>

class TransferFuncEditorDialog : public QWidget
{
public:
    TransferFuncEditorDialog(QWidget* parent = nullptr);
 
private:
    QColorDialog* colorDialogWidget;
};

