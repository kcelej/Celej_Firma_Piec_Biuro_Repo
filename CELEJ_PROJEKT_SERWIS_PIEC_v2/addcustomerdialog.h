#pragma once

#include <QDialog>
#include "ui_addcustomerdialog.h"

class addCustomerDialog : public QDialog, public Ui::addCustomerDialogClass
{
	Q_OBJECT

public:
	addCustomerDialog(QWidget *parent = nullptr);
	~addCustomerDialog();

private:
	 
};
