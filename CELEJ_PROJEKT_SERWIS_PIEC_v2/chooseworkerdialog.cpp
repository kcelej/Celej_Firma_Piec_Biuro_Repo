#include "stdafx.h"
#include "chooseworkerdialog.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"

chooseWorkerDialog::chooseWorkerDialog(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
	QMetaObject::invokeMethod(this->refreshButton, "clicked");
}

chooseWorkerDialog::~chooseWorkerDialog()
{}


void chooseWorkerDialog::on_refreshButton_clicked() {
	// clear the table for new data input
	this->workerTable->clearContents();
	this->workerTable->setRowCount(0);
	// set the selection behaviour to select entire rows in table
	this->workerTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* workersQuery;

	driver = get_driver_instance();
	con = driver->connect(db_ip, db_login, db_password);

	sql::Statement* useDB;
	useDB = con->createStatement();
	useDB->execute("USE firma_piece");
	delete useDB;

	workersQuery = con->createStatement();
	sql::ResultSet* queryResult;

	// use the workers query based on selected sorting method
	if (this->sortBox->currentIndex() == 1) {	// Surname Z - A
		queryResult = workersQuery->executeQuery("SELECT id_pracownika, imie, nazwisko, nr_tel FROM pracownicy WHERE stanowisko='Serwisant' && id_pracownika NOT LIKE 1 ORDER BY nazwisko DESC");
	}
	else {	// Surname A - Z
		queryResult = workersQuery->executeQuery("SELECT id_pracownika, nazwisko, imie, nr_tel FROM pracownicy WHERE stanowisko='Serwisant' && id_pracownika NOT LIKE 1 ORDER BY nazwisko ASC");
	}
	while (queryResult->next()) {
		int workerId = queryResult->getInt(1);
		QTableWidgetItem* item;

		this->workerTable->insertRow(this->workerTable->rowCount());

		// set worker surname in table
		item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
		item->setData(Qt::UserRole, QString::number(workerId));
		this->workerTable->setItem(this->workerTable->rowCount() - 1, 0, item);

		// set worker name in table
		item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
		item->setData(Qt::UserRole, QString::number(workerId));
		this->workerTable->setItem(this->workerTable->rowCount() - 1, 1, item);

		// set worker phone in table

		item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(4).asStdString()));
		item->setData(Qt::UserRole, QString::number(workerId));
		this->workerTable->setItem(this->workerTable->rowCount() - 1, 2, item);
	}

	delete queryResult;
	delete workersQuery;
	delete con;
}