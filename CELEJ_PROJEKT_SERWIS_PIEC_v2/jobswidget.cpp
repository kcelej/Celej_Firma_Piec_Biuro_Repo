#include "stdafx.h"
#include "jobswidget.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"
#include "addjobdialog.h"
#include "reportdialog.h"
#include "jobdetailsdialog.h"

jobsWidget::jobsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QMetaObject::invokeMethod(ui.refreshButton, "clicked");
}

jobsWidget::~jobsWidget()
{}

void jobsWidget::on_refreshButton_clicked() {
    try {
        // clear the table for new data input
        ui.jobsList->clearContents();
        ui.jobsList->setRowCount(0);
        // set the selection behaviour to select entire rows in table
        ui.jobsList->setSelectionBehavior(QAbstractItemView::SelectRows);

        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* jobsQuery;

        driver = get_driver_instance();
        con = driver->connect(db_ip, db_login, db_password);

        sql::Statement* useDB;
        useDB = con->createStatement();
        useDB->execute("USE firma_piece");
        delete useDB;

        jobsQuery = con->createStatement();
        sql::ResultSet* queryResult;

        // use the jobs query based on selected sorting method
        if (ui.sortBox->currentIndex() == 1) {    //od najstarszych
            queryResult = jobsQuery->executeQuery("SELECT id_zlecenia, status, data_zgloszenia, klienci.adres FROM zlecenia INNER JOIN klienci ON zlecenia.id_klienta=klienci.id_klienta ORDER BY data_zgloszenia ASC");
        }
        else { //od najnowszych
            queryResult = jobsQuery->executeQuery("SELECT id_zlecenia, status, data_zgloszenia, klienci.adres FROM zlecenia INNER JOIN klienci ON zlecenia.id_klienta=klienci.id_klienta ORDER BY data_zgloszenia DESC");
        }
        while (queryResult->next()) {
            int jobId = queryResult->getInt(1);
            QTableWidgetItem* item;

            ui.jobsList->insertRow(ui.jobsList->rowCount());

            // set job id
            item = new QTableWidgetItem(QString::number(jobId));
            item->setData(Qt::UserRole, QString::number(jobId));
            ui.jobsList->setItem(ui.jobsList->rowCount() - 1, 0, item);

            // set job status
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
            item->setData(Qt::UserRole, QString::number(jobId));
            ui.jobsList->setItem(ui.jobsList->rowCount() - 1, 1, item);

            // set job start date
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
            item->setData(Qt::UserRole, QString::number(jobId));
            ui.jobsList->setItem(ui.jobsList->rowCount() - 1, 2, item);

            // set job address
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(4).asStdString()));
            item->setData(Qt::UserRole, QString::number(jobId));
            ui.jobsList->setItem(ui.jobsList->rowCount() - 1, 3, item);
        }

        delete queryResult;
        delete jobsQuery;
        delete con;
    }
    catch (sql::SQLException) {
        QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
    }
}

void jobsWidget::on_addButton_clicked() {
    try {
        addJobDialog addJob(this);
        if (addJob.exec()) {
            if (addJob.getCustomerId().isEmpty() || addJob.getFurnaceId().isEmpty() || addJob.getWorkerId().isEmpty()) {
                throw exception();
            }
            ui.jobsList->clearContents();
            ui.jobsList->setRowCount(0);
            ui.jobsList->setSelectionBehavior(QAbstractItemView::SelectRows);

            sql::Driver* driver;
            sql::Connection* con;
            sql::PreparedStatement* addJobQuery;

            driver = get_driver_instance();
            con = driver->connect(db_ip, db_login, db_password);

            sql::Statement* useDB;
            useDB = con->createStatement();
            useDB->execute("USE firma_piece");
            delete useDB;

            // preparing insert statement for the jobs table in database
            addJobQuery = con->prepareStatement("INSERT INTO zlecenia (id_klienta, id_pieca, id_pracownika, opis, status, data_zgloszenia, usuniety) VALUES (?, ?, ?, ?, 'Otwarte', CURDATE(), 0)");

            // set customer id
            addJobQuery->setInt(1, addJob.getCustomerId().toInt());

            // set furnace id
            addJobQuery->setInt(2, addJob.getFurnaceId().toInt());

            // set worker id
            addJobQuery->setInt(3, addJob.getWorkerId().toInt());

            // set description
            string description = addJob.descriptionEdit->text().toStdString();
            addJobQuery->setString(4, description);

            addJobQuery->execute();

            delete addJobQuery;
            delete con;
        }
    }
    catch (sql::SQLException) {
        QMessageBox::information(this, "Błąd", "Wystąpił problem podczas dodawania zlecenia.");
    }
    catch (...) {
        QMessageBox::information(this, "Błąd", "Podano nieprawidłowe dane!");
    }
}

void jobsWidget::on_detailsButton_clicked() {
    try {
        if (!ui.jobsList->currentItem()) {
            throw exception();
        }
        QTableWidgetItem* currentItem = ui.jobsList->currentItem();
        if (currentItem) {
            jobDetailsDialog jobDetails(this);
            jobDetails.setJobId(currentItem->data(Qt::UserRole).toString());
            jobDetails.updateAllData();
            if (jobDetails.exec()) {

            }
        }
    }
    catch (...) {
        QMessageBox::information(this, "Błąd", "Nie wybrano zlecenia!");
    }
}


void jobsWidget::on_reportButton_clicked() {
    reportDialog report(this);
    report.exec();
}