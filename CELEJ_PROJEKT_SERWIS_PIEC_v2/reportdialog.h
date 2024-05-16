#pragma once

#include <QDialog>
#include "ui_reportdialog.h"

class reportDialog : public QDialog, public Ui::reportDialogClass
{
	Q_OBJECT

public:
	reportDialog(QWidget *parent = nullptr);
	~reportDialog();

private:
	 
private slots:
	void on_generateButton_clicked();
};
