#pragma once

#include <QDialog>
#include "ui_choosefurnacedialog.h"

class chooseFurnaceDialog : public QDialog, public Ui::chooseFurnaceDialogClass
{
	Q_OBJECT

public:
	chooseFurnaceDialog(QWidget *parent = nullptr);
	~chooseFurnaceDialog();

private:
	 
private slots:
	void on_refreshButton_clicked();
};
