#pragma once

#include <QDialog>
#include "ui_addworkerdialog.h"

class addWorkerDialog : public QDialog, public Ui::addWorkerDialogClass
{
	Q_OBJECT

public:
	addWorkerDialog(QWidget *parent = nullptr);
	~addWorkerDialog();

private:
	 
};
