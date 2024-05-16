#pragma once

#include <QDialog>
#include "ui_custombasicdialog.h"

class customBasicDialog : public QDialog, public Ui::customBasicDialogClass
{
	Q_OBJECT

public:
	customBasicDialog(QWidget* parent = nullptr);
	~customBasicDialog();

	void setMessage(QString newDialogMessage);	// set the message for the custom dialog
private:
	 
};
