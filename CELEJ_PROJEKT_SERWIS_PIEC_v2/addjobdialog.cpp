#include "stdafx.h"
#include "addjobdialog.h"

#include "chooseworkerdialog.h"
#include "choosefurnacedialog.h"
#include "choosecustomerdialog.h"

addJobDialog::addJobDialog(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
}

addJobDialog::~addJobDialog()
{}

void addJobDialog::on_chooseWorkerButton_clicked() {
	chooseWorkerDialog chooseWorker(this);
	if (chooseWorker.exec()) {
		workerId = chooseWorker.workerTable->currentItem()->data(Qt::UserRole).toString();	// get chosen worker's id from the table data
		if (!workerId.isEmpty()) {
			int row = chooseWorker.workerTable->currentRow();
			this->workerLabel->setText(chooseWorker.workerTable->item(row, 0)->text() + " " + chooseWorker.workerTable->item(row, 1)->text());	// show the chosen worker's full name next to the button
		}
	}
}

void addJobDialog::on_chooseFurnaceButton_clicked() {
	chooseFurnaceDialog chooseFurnace(this);
	if (chooseFurnace.exec()) {
		furnaceId = chooseFurnace.furnaceTable->currentItem()->data(Qt::UserRole).toString();	// get chosen furnace's id from the table data
		if (!furnaceId.isEmpty()) {
			int row = chooseFurnace.furnaceTable->currentRow();
			this->furnaceLabel->setText(chooseFurnace.furnaceTable->item(row, 1)->text());	// show the chosen furnace's model next to the button
		}
	}
}

void addJobDialog::on_chooseCustomerButton_clicked() {
	chooseCustomerDialog chooseCustomer(this);
	if (chooseCustomer.exec()) {
		customerId = chooseCustomer.customerTable->currentItem()->data(Qt::UserRole).toString();	// get chosen customer's id from the table data
		if (!customerId.isEmpty()) {
			int row = chooseCustomer.customerTable->currentRow();
			this->customerLabel->setText(chooseCustomer.customerTable->item(row, 0)->text() + " " + chooseCustomer.customerTable->item(row, 1)->text());	// show the chosen cutomer's full name next to the button
		}
	}
}

QString addJobDialog::getWorkerId() {
	return workerId;
}

QString addJobDialog::getFurnaceId() {
	return furnaceId;
}

QString addJobDialog::getCustomerId() {
	return customerId;
}