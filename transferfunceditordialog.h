#pragma once
#include <QColorDialog>

class TransferFuncEditorDialog : public QColorDialog
{
public:
    TransferFuncEditorDialog(QWidget* parent = nullptr) : QColorDialog(parent)
    {
    }
    void show()
    {
        QColorDialog::show();
    }
};

