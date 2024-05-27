#include "stdafx.h"
#include "customerswidget.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "addcustomerdialog.h"

customersWidget::customersWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.customersList->horizontalHeader()->setStretchLastSection(true);
    QMetaObject::invokeMethod(ui.refreshButton, "clicked");
}

customersWidget::~customersWidget()
{}


void customersWidget::on_refreshButton_clicked() {
    try {
        // clear the table for new data input
        ui.customersList->clearContents();
        ui.customersList->setRowCount(0);
        // set the selection behaviour to select entire rows in table
        ui.customersList->setSelectionBehavior(QAbstractItemView::SelectRows);

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
        if (ui.sortBox->currentIndex() == 1) {  // Surname Z - A
            queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE usuniety=0 ORDER BY nazwisko DESC");
        }
        else if (ui.sortBox->currentIndex() == 2) { // Customer ID - from lowest
            queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE usuniety=0 ORDER BY id_klienta ASC");
        }
        else if (ui.sortBox->currentIndex() == 3) {  // Customer ID - from highest
            queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE usuniety=0 ORDER BY id_klienta DESC");
        }
        else {  // Surname A - Z
            queryResult = customersQuery->executeQuery("SELECT id_klienta, imie, nazwisko, nr_tel, adres FROM klienci WHERE usuniety=0 ORDER BY nazwisko ASC");
        }

        while (queryResult->next()) {
            int customerId = queryResult->getInt(1);
            QTableWidgetItem* item;

            ui.customersList->insertRow(ui.customersList->rowCount());

            // customer id
            item = new QTableWidgetItem(QString::number(customerId));
            item->setData(Qt::UserRole, QString::number(customerId));
            ui.customersList->setItem(ui.customersList->rowCount() - 1, 0, item);

            // customer name
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
            item->setData(Qt::UserRole, QString::number(customerId));
            ui.customersList->setItem(ui.customersList->rowCount() - 1, 1, item);

            // customer surename
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
            item->setData(Qt::UserRole, QString::number(customerId));
            ui.customersList->setItem(ui.customersList->rowCount() - 1, 2, item);

            // customer phone
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(4).asStdString()));
            item->setData(Qt::UserRole, QString::number(customerId));
            ui.customersList->setItem(ui.customersList->rowCount() - 1, 3, item);

            // customer address
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(5).asStdString()));
            item->setData(Qt::UserRole, QString::number(customerId));
            ui.customersList->setItem(ui.customersList->rowCount() - 1, 4, item);

        }

        delete queryResult;
        delete customersQuery;
        delete con;
    }
    catch (sql::SQLException) {
        QMessageBox::warning(this, "Błąd", "Błąd połączenia z bazą danych.");
    }
}

void customersWidget::on_addButton_clicked() {
    try {
        addCustomerDialog addCustomer(this);
        addCustomer.setWindowTitle("Dodaj klienta");
        if (addCustomer.exec()) {
            if (!addCustomer.nameEdit->text().isEmpty() && !addCustomer.surnameEdit->text().isEmpty() && !addCustomer.phoneEdit->text().isEmpty() && !addCustomer.addressEdit->text().isEmpty() && addCustomer.phoneEdit->text().length() == 9) {
                sql::Driver* driver;
                sql::Connection* con;
                sql::PreparedStatement* addCustomerQuery;


                driver = get_driver_instance();
                con = driver->connect(db_ip, db_login, db_password);

                sql::Statement* useDB;
                useDB = con->createStatement();
                useDB->execute("USE firma_piece");
                delete useDB;

                // preparing insert statement for the customers table in database
                addCustomerQuery = con->prepareStatement("INSERT INTO klienci (imie, nazwisko, nr_tel, adres, usuniety) VALUES (?, ?, ?, ?, 0)");

                // set name
                addCustomerQuery->setString(1, addCustomer.nameEdit->text().toStdString());

                // set surname
                addCustomerQuery->setString(2, addCustomer.surnameEdit->text().toStdString());

                // set phone
                addCustomerQuery->setString(3, addCustomer.phoneEdit->text().toStdString());

                // set address
                addCustomerQuery->setString(4, addCustomer.addressEdit->text().toStdString());

                addCustomerQuery->execute();

                delete addCustomerQuery;
                delete con;
                QMetaObject::invokeMethod(ui.refreshButton, "clicked");
            }
            else {
                QMessageBox::information(this, "Błąd", "Podano nieprawidłowe dane.");
            }
        }
    }
    catch (sql::SQLException) {
        QMessageBox::information(this, "Błąd", "Wystąpił problem podczas dodawania klienta.");
    }
}

void customersWidget::on_deleteButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        QMessageBox::information(this, "Odmowa dostępu", "Nie posiadasz wystarczających uprawnień!");
    }
    else {
        try {
            if (!ui.customersList->currentItem()) {
                throw exception();
            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Uwaga!", "Czy na pewno usunąć klienta?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                sql::Driver* driver;
                sql::Connection* con;
                sql::PreparedStatement* deleteCustomer;


                driver = get_driver_instance();
                con = driver->connect(db_ip, db_login, db_password);

                sql::Statement* useDB;
                useDB = con->createStatement();
                useDB->execute("USE firma_piece");
                delete useDB;

                // delete the customer
                deleteCustomer = con->prepareStatement("UPDATE klienci SET usuniety=1 WHERE id_klienta=?");
                deleteCustomer->setInt(1, ui.customersList->currentItem()->data(Qt::UserRole).toInt());

                deleteCustomer->execute();

                delete deleteCustomer;
                delete con;
                QMetaObject::invokeMethod(ui.refreshButton, "clicked");
            }
        }
        catch (sql::SQLException) {
            QMessageBox::information(this, "Błąd", "Wystąpił problem podczas usuwania klienta.");
        }
        catch (...) {
            QMessageBox::information(this, "Błąd", "Nie wybrano klienta!");
        }
    }
}

void customersWidget::on_editButton_clicked() {
    try {
        if (!ui.customersList->currentItem()) {
            throw exception();
        }
        sql::Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* getCustomerDataQuery;
        sql::ResultSet* customerDataResults;


        driver = get_driver_instance();
        con = driver->connect(db_ip, db_login, db_password);

        sql::Statement* useDB;
        useDB = con->createStatement();
        useDB->execute("USE firma_piece");
        delete useDB;

        // get customer's data from database
        getCustomerDataQuery = con->prepareStatement("SELECT imie, nazwisko, nr_tel, adres FROM klienci WHERE id_klienta=?");
        getCustomerDataQuery->setInt(1, ui.customersList->currentItem()->data(Qt::UserRole).toInt());

        customerDataResults = getCustomerDataQuery->executeQuery();

        while (customerDataResults->next()) {
            break;
        }

        // get customer's data into the line edit fields
        addCustomerDialog editCustomer(this);
        editCustomer.setWindowTitle("Edytuj klienta");
        // get customer name
        editCustomer.nameEdit->setText(QString::fromUtf8(customerDataResults->getString(1).asStdString()));

        // get customer surname
        editCustomer.surnameEdit->setText(QString::fromUtf8(customerDataResults->getString(2).asStdString()));

        // get customer phone
        editCustomer.phoneEdit->setText(QString::fromUtf8(customerDataResults->getString(3).asStdString()));

        // get customer address
        editCustomer.addressEdit->setText(QString::fromUtf8(customerDataResults->getString(4).asStdString()));



        if (editCustomer.exec()) {
            sql::PreparedStatement* updateCustomerQuery;
            updateCustomerQuery = con->prepareStatement("UPDATE klienci SET imie=?, nazwisko=?, nr_tel=?, adres=? WHERE id_klienta=?");

            // set name
            updateCustomerQuery->setString(1, editCustomer.nameEdit->text().toStdString());

            // set surname
            updateCustomerQuery->setString(2, editCustomer.surnameEdit->text().toStdString());

            // set phone
            updateCustomerQuery->setString(3, editCustomer.phoneEdit->text().toStdString());

            // set address
            updateCustomerQuery->setString(4, editCustomer.addressEdit->text().toStdString());

            // set id
            updateCustomerQuery->setInt(5, ui.customersList->currentItem()->data(Qt::UserRole).toInt());

            updateCustomerQuery->execute();

            QMetaObject::invokeMethod(ui.refreshButton, "clicked");
            delete updateCustomerQuery;
        }
        delete customerDataResults;
        delete getCustomerDataQuery;
    }
    catch (sql::SQLException) {
        QMessageBox::information(this, "Błąd", "Wystąpił problem podczas edytowania klienta.");
    }
    catch (...) {
        QMessageBox::information(this, "Błąd", "Nie wybrano klienta!");
    }
}