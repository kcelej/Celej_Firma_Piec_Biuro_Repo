#include "stdafx.h"
#include "choosecustomerdialog.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"

chooseCustomerDialog::chooseCustomerDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	this->customerTable->horizontalHeader()->setStretchLastSection(true);
	QMetaObject::invokeMethod(this->refreshButton, "clicked");
}

chooseCustomerDialog::~chooseCustomerDialog()
{}

void chooseCustomerDialog::on_refreshButton_clicked() {
	try {
		// clear the table for new data input
		this->customerTable->clearContents();
		this->customerTable->setRowCount(0);
		// set the selection behaviour to select entire rows in table
		this->customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* customersQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		customersQuery = con->createStatement();
		sql::ResultSet* queryResult;

		// use the customers query based on selected sorting method
		if (this->sortBox->currentIndex() == 1) {	// name Z - A
			queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE id_klienta NOT LIKE 1 ORDER BY imie DESC");
		}
		else if (this->sortBox->currentIndex() == 2) {	// surname A - Z
			queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE id_klienta NOT LIKE 1 ORDER BY nazwisko ASC");
		}
		else if (this->sortBox->currentIndex() == 3) { // surname Z - A
			queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE id_klienta NOT LIKE 1 ORDER BY nazwisko DESC");
		}
		else {	// name A - Z
			queryResult = customersQuery->executeQuery("SELECT id_klienta, nazwisko, imie, nr_tel, adres FROM klienci WHERE id_klienta NOT LIKE 1 ORDER BY imie ASC");
		}

		while (queryResult->next()) {
			int customerId = queryResult->getInt(1);
			QTableWidgetItem* item;

			this->customerTable->insertRow(this->customerTable->rowCount());

			// set customer surname in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
			item->setData(Qt::UserRole, QString::number(customerId));
			this->customerTable->setItem(this->customerTable->rowCount() - 1, 0, item);

			// set customer name in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
			item->setData(Qt::UserRole, QString::number(customerId));
			this->customerTable->setItem(this->customerTable->rowCount() - 1, 1, item);

			// set customer phone in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(4).asStdString()));
			item->setData(Qt::UserRole, QString::number(customerId));
			this->customerTable->setItem(this->customerTable->rowCount() - 1, 2, item);

			// set customer address in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(5).asStdString()));
			item->setData(Qt::UserRole, QString::number(customerId));
			this->customerTable->setItem(this->customerTable->rowCount() - 1, 3, item);
		}

		delete queryResult;
		delete customersQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}