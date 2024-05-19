#include "stdafx.h"
#include "workerswidget.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"
#include "addworkerdialog.h"
#include "yesnodialog.h"

workersWidget::workersWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QMetaObject::invokeMethod(ui.refreshButton, "clicked");
}

workersWidget::~workersWidget()
{}


void workersWidget::on_refreshButton_clicked() {
    try {
        // clear the table for new data input
        ui.workersList->clearContents();
        ui.workersList->setRowCount(0);
        // set the selection behaviour to select entire rows in table
        ui.workersList->setSelectionBehavior(QAbstractItemView::SelectRows);


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

        // use the worker query based on selected sorting method
        if (ui.sortBox->currentIndex() == 0 && ui.technicianCheckBox->checkState() == Qt::Checked) {  // Technicians only, Surname A - Z
            queryResult = workersQuery->executeQuery("SELECT id_pracownika, imie, nazwisko, nr_tel, stanowisko FROM pracownicy WHERE stanowisko='Serwisant' && usuniety=0 ORDER BY nazwisko ASC");
        }
        else if (ui.sortBox->currentIndex() == 1 && ui.technicianCheckBox->checkState() == Qt::Unchecked) { //Surname Z - A
            queryResult = workersQuery->executeQuery("SELECT id_pracownika, imie, nazwisko, nr_tel, stanowisko FROM pracownicy WHERE usuniety=0 ORDER BY nazwisko DESC");
        }
        else if (ui.sortBox->currentIndex() == 1 && ui.technicianCheckBox->checkState() == Qt::Checked) { // Technicians only, Surname Z - A
            queryResult = workersQuery->executeQuery("SELECT id_pracownika, imie, nazwisko, nr_tel, stanowisko FROM pracownicy WHERE stanowisko='Serwisant' && usuniety=0 ORDER BY nazwisko DESC");
        }
        else {  // Surname A - Z
            queryResult = workersQuery->executeQuery("SELECT id_pracownika, imie, nazwisko, nr_tel, stanowisko FROM pracownicy WHERE usuniety=0 ORDER BY nazwisko ASC");
        }

        while (queryResult->next()) {
            int workerId = queryResult->getInt(1);
            QTableWidgetItem* item;

            ui.workersList->insertRow(ui.workersList->rowCount());

            // name
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
            item->setData(Qt::UserRole, QString::number(workerId));
            ui.workersList->setItem(ui.workersList->rowCount() - 1, 0, item);

            // surname
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
            item->setData(Qt::UserRole, QString::number(workerId));
            ui.workersList->setItem(ui.workersList->rowCount() - 1, 1, item);

            // phone
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(4).asStdString()));
            item->setData(Qt::UserRole, QString::number(workerId));
            ui.workersList->setItem(ui.workersList->rowCount() - 1, 2, item);

            // position
            item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(5).asStdString()));
            item->setData(Qt::UserRole, QString::number(workerId));
            ui.workersList->setItem(ui.workersList->rowCount() - 1, 3, item);
        }

        delete queryResult;
        delete workersQuery;
        delete con;
    }
    catch (sql::SQLException) {
        QMessageBox::warning(this, "Błąd", "Błąd połączenia z bazą danych.");
    }
}

void workersWidget::on_addButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        QMessageBox::information(this, "Odmowa dostępu", "Nie posiadasz wystarczających uprawnień!");
    }
    else {
        try {
            sql::Driver* driver;
            sql::Connection* con;
            sql::PreparedStatement* addWorkerQuery;

            driver = get_driver_instance();
            con = driver->connect(db_ip, db_login, db_password);

            sql::Statement* useDB;
            useDB = con->createStatement();
            useDB->execute("USE firma_piece");
            delete useDB;

            addWorkerDialog addWorker(this);

            sql::Statement* getPositions;
            getPositions = con->createStatement();
            sql::ResultSet* positionsResult;
            positionsResult = getPositions->executeQuery("SELECT stanowisko FROM pracownicy WHERE usuniety=0 GROUP BY stanowisko;");  // find all worker positions currently existing in the database

            while (positionsResult->next()) {   // add the job positions to the combo box
                addWorker.positionComboBox->addItem(QString::fromUtf8(positionsResult->getString(1).asStdString()));
            }

            delete positionsResult;
            delete getPositions;

            if (addWorker.exec()) {
                sql::ResultSet* queryResult;
                if (!addWorker.nameEdit->text().isEmpty() && !addWorker.surnameEdit->text().isEmpty() && !addWorker.phoneEdit->text().isEmpty() && !addWorker.passwordEdit->text().isEmpty() && !addWorker.loginEdit->text().isEmpty()) {
                    if (addWorker.name2CheckBox->checkState() == Qt::Unchecked) {
                        if (addWorker.name2Edit->text().isEmpty()) {
                            customBasicDialog error(this);
                            error.setMessage("Podano nieprawidłowe dane.");
                            error.exec();
                        }
                        else {
                            addWorkerQuery = con->prepareStatement("INSERT INTO pracownicy(imie, imie2, nazwisko, nr_tel, stanowisko, login, haslo, usuniety) VALUES (?, ?, ?, ?, ?, ?, ?, 0)");

                            // name
                            addWorkerQuery->setString(1, addWorker.nameEdit->text().toStdString());

                            // name2
                            addWorkerQuery->setString(2, addWorker.name2Edit->text().toStdString());

                            // surname
                            addWorkerQuery->setString(3, addWorker.surnameEdit->text().toStdString());

                            // phone
                            addWorkerQuery->setString(4, addWorker.phoneEdit->text().toStdString());

                            // position
                            addWorkerQuery->setString(5, addWorker.positionComboBox->currentText().toStdString());

                            // login
                            addWorkerQuery->setString(6, addWorker.loginEdit->text().toStdString());

                            // password
                            addWorkerQuery->setString(7, addWorker.passwordEdit->text().toStdString());
                        }

                    }
                    else {
                        addWorkerQuery = con->prepareStatement("INSERT INTO pracownicy(imie, nazwisko, nr_tel, stanowisko, login, haslo, usuniety) VALUES (?, ?, ?, ?, ?, ?, 0)");

                        // name
                        addWorkerQuery->setString(1, addWorker.nameEdit->text().toStdString());

                        // surname
                        addWorkerQuery->setString(2, addWorker.surnameEdit->text().toStdString());

                        // phone
                        addWorkerQuery->setString(3, addWorker.phoneEdit->text().toStdString());

                        // position
                        addWorkerQuery->setString(4, addWorker.positionComboBox->currentText().toStdString());

                        // login
                        addWorkerQuery->setString(5, addWorker.loginEdit->text().toStdString());

                        // password
                        addWorkerQuery->setString(6, addWorker.passwordEdit->text().toStdString());

                    }
                    addWorkerQuery->execute();
                    QMetaObject::invokeMethod(ui.refreshButton, "clicked");
                }
                else {
                    QMessageBox::information(this, "Błąd", "Podano nieprawidłowe dane.");
                }
            }
        }
        catch (sql::SQLException) {
            QMessageBox::information(this, "Błąd", "Wystąpił problem podczas dodawania pracownika.");
        }
    }
}

void workersWidget::on_deleteButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        QMessageBox::information(this, "Odmowa dostępu", "Nie posiadasz wystarczających uprawnień!");
    }
    else {
        try {
            if (!ui.workersList->currentItem()) {
                throw exception();
            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Uwaga!", "Czy na pewno usunąć pracownika?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                sql::Driver* driver;
                sql::Connection* con;
                sql::PreparedStatement* deleteWorker;

                driver = get_driver_instance();
                con = driver->connect(db_ip, db_login, db_password);

                sql::Statement* useDB;
                useDB = con->createStatement();
                useDB->execute("USE firma_piece");
                delete useDB;

                deleteWorker = con->prepareStatement("UPDATE pracownicy SET usuniety=1 WHERE id_pracownika=?");
                deleteWorker->setInt(1, ui.workersList->currentItem()->data(Qt::UserRole).toInt());

                deleteWorker->execute();

                delete deleteWorker;
                delete con;
                QMetaObject::invokeMethod(ui.refreshButton, "clicked");
            }
        }
        catch (sql::SQLException) {
            QMessageBox::information(this, "Błąd", "Wystąpił problem podczas usuwania pracownika.");
        }
        catch (...) {
            QMessageBox::information(this, "Błąd", "Nie wybrano pracownika!");
        }
    }
}


void workersWidget::on_editButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        QMessageBox::information(this, "Odmowa dostępu", "Nie posiadasz wystarczających uprawnień!");
    }
    else {
        try {
            if (!ui.workersList->currentItem()) {
                throw exception();
            }
            sql::Driver* driver;
            sql::Connection* con;
            sql::PreparedStatement* getWorkerDataQuery;
            sql::ResultSet* workerDataResults;

            driver = get_driver_instance();
            con = driver->connect(db_ip, db_login, db_password);

            sql::Statement* useDB;
            useDB = con->createStatement();
            useDB->execute("USE firma_piece");
            delete useDB;

            // get worker's data from database
            getWorkerDataQuery = con->prepareStatement("SELECT imie, imie2, nazwisko, nr_tel, stanowisko, login, haslo FROM pracownicy WHERE id_pracownika=?");
            getWorkerDataQuery->setInt(1, ui.workersList->currentItem()->data(Qt::UserRole).toInt());

            workerDataResults = getWorkerDataQuery->executeQuery();

            while (workerDataResults->next()) {
                break;
            }

            // get worker's data into the line edit fields
            addWorkerDialog editWorker(this);

            // get worker's name
            editWorker.nameEdit->setText(QString::fromUtf8(workerDataResults->getString(1).asStdString()));

            // get worker's second name
            if (!workerDataResults->getString(2).asStdString().empty()) {
                editWorker.name2Edit->setText(QString::fromUtf8(workerDataResults->getString(2).asStdString()));
                editWorker.name2CheckBox->setCheckState(Qt::Unchecked);
            }
            else {
                editWorker.name2CheckBox->setCheckState(Qt::Checked);
            }

            // get worker's surname
            editWorker.surnameEdit->setText(QString::fromUtf8(workerDataResults->getString(3).asStdString()));

            // get worker's phone
            editWorker.phoneEdit->setText(QString::fromUtf8(workerDataResults->getString(4).asStdString()));

            // get worker's position
            sql::Statement* getPositions;
            getPositions = con->createStatement();
            sql::ResultSet* positionsResult;
            positionsResult = getPositions->executeQuery("SELECT stanowisko FROM pracownicy WHERE usuniety=0 GROUP BY stanowisko;");  // find all worker positions currently existing in the database


            int comboBoxIndex = 0, i = 0;
            while (positionsResult->next()) {   // add the job positions to the combo box
                editWorker.positionComboBox->addItem(QString::fromUtf8(positionsResult->getString(1).asStdString()));
                if (positionsResult->getString(1).asStdString() == workerDataResults->getString(5).asStdString()) comboBoxIndex = i;
                i++;
            }

            editWorker.positionComboBox->setCurrentIndex(comboBoxIndex);
            delete positionsResult;
            delete getPositions;

            // get worker's login
            editWorker.loginEdit->setText(QString::fromUtf8(workerDataResults->getString(6).asStdString()));

            // get worker's password
            editWorker.passwordEdit->setText(QString::fromUtf8(workerDataResults->getString(7).asStdString()));


            if (editWorker.exec()) {
                sql::PreparedStatement* updateWorkerQuery;
                updateWorkerQuery = con->prepareStatement("UPDATE pracownicy SET imie=?, imie2=?, nazwisko=?, nr_tel=?, stanowisko=?, login=?, haslo=? WHERE id_pracownika=?");

                // set name
                updateWorkerQuery->setString(1, editWorker.nameEdit->text().toStdString());

                // set second name
                if (editWorker.name2CheckBox->checkState() == Qt::Checked) {
                    updateWorkerQuery->setNull(2, 0);
                }
                else {
                    updateWorkerQuery->setString(2, editWorker.name2Edit->text().toStdString());
                }

                // set surname
                updateWorkerQuery->setString(3, editWorker.surnameEdit->text().toStdString());

                // set phone
                updateWorkerQuery->setString(4, editWorker.phoneEdit->text().toStdString());

                // set position
                updateWorkerQuery->setString(5, editWorker.positionComboBox->currentText().toStdString());

                // set login
                updateWorkerQuery->setString(6, editWorker.loginEdit->text().toStdString());

                // set password
                updateWorkerQuery->setString(7, editWorker.passwordEdit->text().toStdString());

                // set id
                updateWorkerQuery->setInt(8, ui.workersList->currentItem()->data(Qt::UserRole).toInt());

                updateWorkerQuery->execute();

                QMetaObject::invokeMethod(ui.refreshButton, "clicked");
                delete updateWorkerQuery;
            }
            delete workerDataResults;
            delete getWorkerDataQuery;
        }
        catch (sql::SQLException) {
            QMessageBox::information(this, "Błąd", "Wystąpił problem podczas edytowania pracownika.");
        }
        catch (...) {
            QMessageBox::information(this, "Błąd", "Nie wybrano pracownika!");
        }
    }
}