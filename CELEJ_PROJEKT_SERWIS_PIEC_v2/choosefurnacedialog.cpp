#include "stdafx.h"
#include "choosefurnacedialog.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"

chooseFurnaceDialog::chooseFurnaceDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	this->furnaceTable->horizontalHeader()->setStretchLastSection(true);
	QMetaObject::invokeMethod(this->refreshButton, "clicked");
}

chooseFurnaceDialog::~chooseFurnaceDialog()
{}


void chooseFurnaceDialog::on_refreshButton_clicked() {
	try {
		// clear the table for new data input
		this->furnaceTable->clearContents();
		this->furnaceTable->setRowCount(0);
		// set the selection behaviour to select entire rows in table
		this->furnaceTable->setSelectionBehavior(QAbstractItemView::SelectRows);

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* furnacesQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		furnacesQuery = con->createStatement();
		sql::ResultSet* queryResult;

		// use the furnaces query based on selected sorting method
		if (this->sortBox->currentIndex() == 1) {	// Manufacturer Z - A
			queryResult = furnacesQuery->executeQuery("SELECT id_pieca, producent, model, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 ORDER BY producent DESC");
		}
		else if (this->sortBox->currentIndex() == 2) {	// Model A - Z
			queryResult = furnacesQuery->executeQuery("SELECT id_pieca, producent, model, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 ORDER BY model ASC");
		}
		else if (this->sortBox->currentIndex() == 3) {	// Model Z - A
			queryResult = furnacesQuery->executeQuery("SELECT id_pieca, producent, model, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 ORDER BY model DESC");
		}
		else {	// Manufacturer A - Z
			queryResult = furnacesQuery->executeQuery("SELECT id_pieca, producent, model, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 ORDER BY producent ASC");
		}

		while (queryResult->next()) {
			int furnaceId = queryResult->getInt(1);
			QTableWidgetItem* item;

			this->furnaceTable->insertRow(this->furnaceTable->rowCount());

			// set furnace manufacturer in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
			item->setData(Qt::UserRole, QString::number(furnaceId));
			this->furnaceTable->setItem(this->furnaceTable->rowCount() - 1, 0, item);

			// set furnace model in table
			item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
			item->setData(Qt::UserRole, QString::number(furnaceId));
			this->furnaceTable->setItem(this->furnaceTable->rowCount() - 1, 1, item);


			// set furnace support in table
			if (queryResult->getInt(4) == 1) {

				item = new QTableWidgetItem("Tak");
			}
			else {
				item = new QTableWidgetItem("Nie");
			}
			item->setData(Qt::UserRole, QString::number(furnaceId));
			this->furnaceTable->setItem(this->furnaceTable->rowCount() - 1, 2, item);
		}

		delete queryResult;
		delete furnacesQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}