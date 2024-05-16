#pragma once

#include <QDialog>
#include "ui_editfurnacedialog.h"

class editFurnaceDialog : public QDialog, public Ui::editFurnaceDialogClass
{
	Q_OBJECT

public:
	editFurnaceDialog(QWidget *parent = nullptr);
	~editFurnaceDialog();

	void setFurnaceId(int i);
	int getFurnaceId();
private:
	int furnaceId;
private slots:
	void browse();	// browse files on the device
	void on_switchSupportButton_clicked();
	void on_confirmManualButton_clicked();
};
