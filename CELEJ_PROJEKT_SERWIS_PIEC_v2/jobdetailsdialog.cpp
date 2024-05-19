#include "stdafx.h"
#include "jobdetailsdialog.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"
#include "chooseworkerdialog.h"
#include "choosefurnacedialog.h"
#include "choosecustomerdialog.h"
#include "editjobdialog.h"
#include "yesnodialog.h"

jobDetailsDialog::jobDetailsDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

jobDetailsDialog::~jobDetailsDialog()
{}

void jobDetailsDialog::setJobId(QString id) {
	jobId = id;
}

void jobDetailsDialog::updateCustomerData() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* updateCustomerDataQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		updateCustomerDataQuery = con->prepareStatement("SELECT klienci.id_klienta, klienci.imie, klienci.nazwisko, klienci.nr_tel, klienci.adres FROM klienci INNER JOIN zlecenia ON klienci.id_klienta=zlecenia.id_klienta WHERE zlecenia.id_zlecenia=? LIMIT 1");
		updateCustomerDataQuery->setInt(1, jobId.toInt());

		sql::ResultSet* result;
		result = updateCustomerDataQuery->executeQuery();

		while (result->next()) {
			break;
		}

		this->customerIdLabel->setText(QString::number(result->getInt(1)));
		this->customerNameLabel->setText(QString::fromUtf8(result->getString(2).asStdString()) + " " + QString::fromUtf8(result->getString(3).asStdString()));
		this->customerPhoneLabel->setText(QString::fromUtf8(result->getString(4).asStdString()));
		this->customerAddressLabel->setText(QString::fromUtf8(result->getString(5).asStdString()));

		delete updateCustomerDataQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}

void jobDetailsDialog::updateWorkerData() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* updateWorkerDataQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		updateWorkerDataQuery = con->prepareStatement("SELECT pracownicy.id_pracownika, pracownicy.imie, pracownicy.nazwisko, pracownicy.nr_tel FROM pracownicy INNER JOIN zlecenia ON pracownicy.id_pracownika=zlecenia.id_pracownika WHERE zlecenia.id_zlecenia=? LIMIT 1");
		updateWorkerDataQuery->setInt(1, jobId.toInt());

		sql::ResultSet* result;
		result = updateWorkerDataQuery->executeQuery();

		while (result->next()) {
			break;
		}

		this->workerIdLabel->setText(QString::number(result->getInt(1)));
		this->workerNameLabel->setText(QString::fromUtf8(result->getString(2).asStdString()) + " " + QString::fromUtf8(result->getString(3).asStdString()));
		this->workerPhoneLabel->setText(QString::fromUtf8(result->getString(4).asStdString()));

		delete updateWorkerDataQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}

void jobDetailsDialog::updateFurnaceData() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* updateFurnaceDataQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		updateFurnaceDataQuery = con->prepareStatement("SELECT piece.producent, piece.model FROM piece INNER JOIN zlecenia ON piece.id_pieca=zlecenia.id_pieca WHERE zlecenia.id_zlecenia=? LIMIT 1");

		updateFurnaceDataQuery->setInt(1, jobId.toInt());

		sql::ResultSet* result;
		result = updateFurnaceDataQuery->executeQuery();

		while (result->next()) {
			break;
		}

		this->furnaceManufacturerLabel->setText(QString::fromUtf8(result->getString(1).asStdString()));
		this->furnaceModelLabel->setText(QString::fromUtf8(result->getString(2).asStdString()));


		delete updateFurnaceDataQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}

void jobDetailsDialog::updateJobStatus() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* jobStatusQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;


		if (this->jobStatusLabel->text() == "Zamknięte") {
			this->jobStatusLabel->setText("Otwarte");
			jobStatusQuery = con->prepareStatement("UPDATE zlecenia SET status='Otwarte' WHERE zlecenia.id_zlecenia=?");
		}
		else {
			this->jobStatusLabel->setText("Zamknięte");
			jobStatusQuery = con->prepareStatement("UPDATE zlecenia SET status='Zamkniete' WHERE zlecenia.id_zlecenia=?");
		}

		jobStatusQuery->setInt(1, jobId.toInt());

		jobStatusQuery->execute();

		delete jobStatusQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}

void jobDetailsDialog::updateJobData() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* updateJobDataQuery;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		updateJobDataQuery = con->prepareStatement("SELECT id_zlecenia, status, data_zgloszenia, data_serwisu, data_zakonczenia, opis, komentarz FROM zlecenia WHERE id_zlecenia=? LIMIT 1");
		updateJobDataQuery->setInt(1, jobId.toInt());

		sql::ResultSet* result;
		result = updateJobDataQuery->executeQuery();

		while (result->next()) {
			break;
		}

		this->jobIdLabel->setText(QString::number(result->getInt(1)));
		this->jobStatusLabel->setText(QString::fromUtf8(result->getString(2).asStdString()));
		this->jobBeginDateLabel->setText(QString::fromUtf8(result->getString(3).asStdString()));
		this->jobServiceDateLabel->setText(QString::fromUtf8(result->getString(4).asStdString()));
		if (!QString::fromUtf8(result->getString(5).asStdString()).isEmpty()) {
			this->jobEndLabel->setText(QString::fromUtf8(result->getString(5).asStdString()));
		}
		else {
			this->jobEndLabel->setText("<brak>");
		}
		if (!QString::fromUtf8(result->getString(6).asStdString()).isEmpty()) {
			this->jobDescriptionLabel->setText(QString::fromUtf8(result->getString(6).asStdString()));
		}
		else {
			this->jobEndLabel->setText("<brak>");
		}
		if (!QString::fromUtf8(result->getString(7).asStdString()).isEmpty()) {
			this->jobCommentLabel->setText(QString::fromUtf8(result->getString(7).asStdString()));
		}
		else {
			this->jobEndLabel->setText("<brak>");
		}


		delete updateJobDataQuery;
		delete con;
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
	}
}


void jobDetailsDialog::updateAllData() {
	updateWorkerData();
	updateJobData();
	updateFurnaceData();
	updateCustomerData();
}

void jobDetailsDialog::on_changeStatusButton_clicked() {
	updateJobStatus();
}


void jobDetailsDialog::on_workerChangeButton_clicked() {
	try {
		chooseWorkerDialog chooseWorker(this);
		if (chooseWorker.exec()) {
			QString workerId = chooseWorker.workerTable->currentItem()->data(Qt::UserRole).toString();

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* changeWorkerId;

			driver = get_driver_instance();
			con = driver->connect(db_ip, db_login, db_password);

			sql::Statement* useDB;
			useDB = con->createStatement();
			useDB->execute("USE firma_piece");
			delete useDB;

			changeWorkerId = con->prepareStatement("UPDATE zlecenia SET id_pracownika=? WHERE zlecenia.id_zlecenia=?");

			changeWorkerId->setInt(1, workerId.toInt());
			changeWorkerId->setInt(2, jobId.toInt());

			sql::ResultSet* result;
			result = changeWorkerId->executeQuery();

			delete changeWorkerId;
			delete con;

			updateWorkerData();
		}
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas zmiany pracownika.");
	}
}

void jobDetailsDialog::on_furnaceChangeButton_clicked() {
	try {
		chooseFurnaceDialog chooseFurnace(this);
		if (chooseFurnace.exec()) {
			QString furnaceId = chooseFurnace.furnaceTable->currentItem()->data(Qt::UserRole).toString();

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* changeFurnaceId;

			driver = get_driver_instance();
			con = driver->connect(db_ip, db_login, db_password);

			sql::Statement* useDB;
			useDB = con->createStatement();
			useDB->execute("USE firma_piece");
			delete useDB;

			changeFurnaceId = con->prepareStatement("UPDATE zlecenia SET id_pieca=? WHERE zlecenia.id_zlecenia=?");

			changeFurnaceId->setInt(1, furnaceId.toInt());
			changeFurnaceId->setInt(2, jobId.toInt());

			sql::ResultSet* result;
			result = changeFurnaceId->executeQuery();

			delete changeFurnaceId;
			delete con;

			updateFurnaceData();
		}
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas zmiany pieca.");
	}
}

void jobDetailsDialog::on_customerChangeButton_clicked() {
	try {
		chooseCustomerDialog chooseCustomer(this);
		if (chooseCustomer.exec()) {
			QString customerId = chooseCustomer.customerTable->currentItem()->data(Qt::UserRole).toString();

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* changeCustomerId;

			driver = get_driver_instance();
			con = driver->connect(db_ip, db_login, db_password);

			sql::Statement* useDB;
			useDB = con->createStatement();
			useDB->execute("USE firma_piece");
			delete useDB;

			changeCustomerId = con->prepareStatement("UPDATE zlecenia SET id_klienta=? WHERE zlecenia.id_zlecenia=?");

			changeCustomerId->setInt(1, customerId.toInt());
			changeCustomerId->setInt(2, jobId.toInt());

			sql::ResultSet* result;
			result = changeCustomerId->executeQuery();

			delete changeCustomerId;
			delete con;

			updateCustomerData();
		}
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas zmiany klienta.");
	}
}

void jobDetailsDialog::on_jobDataChangeButton_clicked() {
	try {
		editJobDialog editJob(this);
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* getJobData;

		driver = get_driver_instance();
		con = driver->connect(db_ip, db_login, db_password);

		sql::Statement* useDB;
		useDB = con->createStatement();
		useDB->execute("USE firma_piece");
		delete useDB;

		getJobData = con->prepareStatement("SELECT data_zgloszenia, data_serwisu, data_zakonczenia, opis, komentarz FROM zlecenia WHERE zlecenia.id_zlecenia=?");
		getJobData->setInt(1, jobId.toInt());

		sql::ResultSet* resultGet;
		resultGet = getJobData->executeQuery();

		while (resultGet->next()) {
			break;
		}

		editJob.beginDateEdit->setDate(QDate::fromString(QString::fromUtf8(resultGet->getString(1).asStdString()), "yyyy-MM-dd"));
		editJob.serviceDateEdit->setDate(QDate::fromString(QString::fromUtf8(resultGet->getString(2).asStdString()), "yyyy-MM-dd"));
		editJob.endDateEdit->setDate(QDate::fromString(QString::fromUtf8(resultGet->getString(3).asStdString()), "yyyy-MM-dd"));
		editJob.descriptionEdit->setText(QString::fromUtf8(resultGet->getString(4).asStdString()));
		editJob.commentEdit->setText(QString::fromUtf8(resultGet->getString(5).asStdString()));

		delete getJobData;
		delete con;
		if (editJob.exec()) {
			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* editJobData;

			driver = get_driver_instance();
			con = driver->connect(db_ip, db_login, db_password);

			sql::Statement* useDB;
			useDB = con->createStatement();
			useDB->execute("USE firma_piece");
			delete useDB;

			editJobData = con->prepareStatement("UPDATE zlecenia SET data_zgloszenia=?, data_serwisu=?, data_zakonczenia=?, opis=?, komentarz=? WHERE zlecenia.id_zlecenia=?");

			editJobData->setString(1, editJob.beginDateEdit->date().toString("yyyy-MM-dd").toStdString());
			editJobData->setString(2, editJob.serviceDateEdit->date().toString("yyyy-MM-dd").toStdString());
			editJobData->setString(3, editJob.endDateEdit->date().toString("yyyy-MM-dd").toStdString());
			editJobData->setString(4, editJob.descriptionEdit->text().toStdString());
			editJobData->setString(5, editJob.commentEdit->text().toStdString());
			editJobData->setInt(6, jobId.toInt());


			sql::ResultSet* result;
			result = editJobData->executeQuery();

			delete editJobData;
			delete con;

			updateJobData();
		}
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas zmiany danych zlecenia.");
	}
}


void jobDetailsDialog::on_deleteButton_clicked() {
	try {
		yesNoDialog confirmDialog(this);
		confirmDialog.setMessage("Czy na pewno usunąć zlecenie?");
		if (confirmDialog.exec()) {
			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* deleteJob;

			driver = get_driver_instance();
			con = driver->connect(db_ip, db_login, db_password);

			sql::Statement* useDB;
			useDB = con->createStatement();
			useDB->execute("USE firma_piece");
			delete useDB;

			deleteJob = con->prepareStatement("UPDATE zlecenia SET usuniety=1 WHERE id_zlecenia=?");
			deleteJob->setInt(1, jobId.toInt());

			deleteJob->execute();

			delete deleteJob;
			delete con;
			this->close();
		}
	}
	catch (sql::SQLException) {
		QMessageBox::information(this, "Błąd", "Wystąpił problem podczas usuwania zlecenia.");
	}
}