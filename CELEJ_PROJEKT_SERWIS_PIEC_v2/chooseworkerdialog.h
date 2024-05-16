#pragma once

#include <QDialog>
#include "ui_chooseworkerdialog.h"

class chooseWorkerDialog : public QDialog, public Ui::chooseWorkerDialogClass
{
	Q_OBJECT

public:
	chooseWorkerDialog(QWidget* parent = nullptr);
	~chooseWorkerDialog();

private:

private slots:
	void on_refreshButton_clicked();
};
