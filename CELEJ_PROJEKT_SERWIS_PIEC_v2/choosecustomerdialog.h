#pragma once

#include <QDialog>
#include "ui_choosecustomerdialog.h"

class chooseCustomerDialog : public QDialog, public Ui::chooseCustomerDialogClass
{
	Q_OBJECT

public:
	chooseCustomerDialog(QWidget *parent = nullptr);
	~chooseCustomerDialog();

private:
	 
private slots:
	void on_refreshButton_clicked();
};
