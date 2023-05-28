#pragma once
#include <qdialog.h>
class GraphDialog : public QDialog
{
	Q_OBJECT
public:
	GraphDialog(const QByteArray& data);
};

