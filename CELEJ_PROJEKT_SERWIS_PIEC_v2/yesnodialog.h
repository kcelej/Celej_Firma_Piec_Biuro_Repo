#pragma once

#include <QDialog>
#include "ui_yesnodialog.h"

class yesNoDialog : public QDialog, public Ui::yesNoDialogClass
{
	Q_OBJECT

public:
	yesNoDialog(QWidget *parent = nullptr);
	~yesNoDialog();

	void setMessage(QString newDialogMessage);	// set message for the dialog window
private:
	 
};
