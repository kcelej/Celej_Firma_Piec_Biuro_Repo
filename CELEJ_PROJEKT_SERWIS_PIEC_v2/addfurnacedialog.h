#pragma once

#include <QDialog>
#include "ui_addfurnacedialog.h"

class addFurnaceDialog : public QDialog, public Ui::addFurnaceDialogClass
{
	Q_OBJECT

public:
	addFurnaceDialog(QWidget *parent = nullptr);
	~addFurnaceDialog();

private:
	 
private slots:
	void browse();	// browse files on the device
};
