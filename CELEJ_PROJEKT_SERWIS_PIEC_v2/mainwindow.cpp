#include "stdafx.h"
#include "mainwindow.h"

#include "loginscreen.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "jobswidget.h"
#include "customerswidget.h"
#include "workerswidget.h"
#include "furnaceswidget.h"
#include "custombasicdialog.h"
#include <fstream>

void mainWindow::login() {
    userSingleton& user = userSingleton::instance();

    do {    // get login and password and search the database for a user with the same credentials
        loginScreen dialog(this);
        if (dialog.exec()) {
            string login = (dialog.loginEdit->text()).toStdString();
            string password = (dialog.passwordEdit->text()).toStdString();

            sql::Driver* driver;
            sql::Connection* con;

            driver = get_driver_instance();
            con = driver->connect(db_ip, db_login, db_password);

            sql::Statement* useDB;
            useDB = con->createStatement();
            useDB->execute("USE firma_piece");
            delete useDB;

            sql::PreparedStatement* checkInfo;
            checkInfo = con->prepareStatement("SELECT login, haslo, imie, nazwisko, stanowisko FROM pracownicy WHERE login=? && haslo=? && id_pracownika NOT LIKE 1;");
            checkInfo->setString(1, login);
            checkInfo->setString(2, password);
            sql::ResultSet* res;
            res = checkInfo->executeQuery();

            if ((!login.empty() && !password.empty())) {
                while (res->next()) {
                    break;
                }
                if (login == res->getString(1) && password == res->getString(2)) {  // if the credentials are correct log the user in
                    user.setLogin(res->getString(1));
                    user.setPassword(res->getString(2));
                    user.setStatus(1);
                    user.setName(res->getString(3));
                    user.setSurname(res->getString(4));
                    user.setPosition(res->getString(5));

                    delete res;
                    delete checkInfo;
                    delete con;
                    break;
                }
            }
            delete res;
            delete checkInfo;
            delete con;
        }
    } while (1);

    ui.stackedWidget->setCurrentIndex(1);
    ui.loggedUserLabel->setText(QString::fromUtf8(user.getName() + " " + user.getSurname()));
}

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    userSingleton &user = userSingleton::instance();

    QWidget* jobs = new jobsWidget();   // create the jobs screen
    QWidget* customers = new customersWidget();   // create the customers screen
    QWidget* workers = new workersWidget();   // create the workers screen
    QWidget* furnaces = new furnacesWidget();   // create the furnaces screen

    ui.stackedWidget->addWidget(jobs);
    ui.stackedWidget->addWidget(customers);
    ui.stackedWidget->addWidget(workers);
    ui.stackedWidget->addWidget(furnaces);

    login();    // display the login dialog
}

mainWindow::~mainWindow()
{
    // delete files created by the program
    ofstream of("manual.pdf");
    of.close();
    remove("manual.pdf");
}


void mainWindow::on_logoutButton_clicked() {
    userSingleton& user = userSingleton::instance();

    ui.stackedWidget->setCurrentIndex(0);

    // clear the data of the previously logged-in user
    user.setLogin("");
    user.setPassword("");
    user.setStatus(0);
    user.setName("");
    user.setSurname("");
    user.setPosition("");

    // clear the label of the logged-in user's full name
    ui.loggedUserLabel->setText("<Dane logowania>");

    login();    // display the login dialog
}


void mainWindow::on_jobButton_clicked() {
    ui.stackedWidget->setCurrentIndex(1);   // display the jobs screen 
}

void mainWindow::on_customerButton_clicked() {
    ui.stackedWidget->setCurrentIndex(2);   // display the customers screen 
}

void mainWindow::on_workerButton_clicked() {
    ui.stackedWidget->setCurrentIndex(3);   // display the workers screen 
}


void mainWindow::on_furnaceButton_clicked() {
    ui.stackedWidget->setCurrentIndex(4);   // display the furnaces screen 
}