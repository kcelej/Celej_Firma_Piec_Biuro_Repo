#pragma once

#include <QDialog>
#include "ui_addjobdialog.h"

class addJobDialog : public QDialog, public Ui::addJobDialogClass
{
	Q_OBJECT

public:
	addJobDialog(QWidget* parent = nullptr);
	~addJobDialog();

	// id getters for later insert query
	QString getWorkerId();
	QString getFurnaceId();
	QString getCustomerId();
private:
	// id storage for insert query
	QString workerId;
	QString furnaceId;
	QString customerId;
private slots:
	void on_chooseWorkerButton_clicked();
	void on_chooseFurnaceButton_clicked();
	void on_chooseCustomerButton_clicked();

};
