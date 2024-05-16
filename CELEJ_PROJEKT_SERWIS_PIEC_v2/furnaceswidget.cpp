#include "stdafx.h"
#include "furnaceswidget.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"
#include "yesnodialog.h"
#include "addfurnacedialog.h"
#include "editfurnacedialog.h"
#include <fstream>


furnacesWidget::furnacesWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QMetaObject::invokeMethod(ui.refreshButton, "clicked");
}

furnacesWidget::~furnacesWidget()
{}

void furnacesWidget::on_refreshButton_clicked() {
    // clear the table for new data input
    ui.furnacesList->clearContents();
    ui.furnacesList->setRowCount(0);
    // set the selection behaviour to select entire rows in table
    ui.furnacesList->setSelectionBehavior(QAbstractItemView::SelectRows);

    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* furnacesQuery;

    driver = get_driver_instance();
    con = driver->connect(db_ip, db_login, db_password);

    sql::Statement* useDB;
    useDB = con->createStatement();
    useDB->execute("USE firma_piece");
    delete useDB;

    sql::ResultSet* queryResult;

    // use the furnaces query based on selected sorting method
    if (ui.sortBox->currentIndex() == 1) {  // Model Z - A
        furnacesQuery = con->prepareStatement("SELECT id_pieca, model, producent, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 && czy_wspierany BETWEEN ? AND 1 ORDER BY model DESC");
    }
    else if (ui.sortBox->currentIndex() == 2) { // Manufacturer A - Z
        furnacesQuery = con->prepareStatement("SELECT id_pieca, model, producent, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 && czy_wspierany BETWEEN ? AND 1 ORDER BY producent ASC");
    }
    else if (ui.sortBox->currentIndex() == 3) { // Manufacturer Z - A
        furnacesQuery = con->prepareStatement("SELECT id_pieca, model, producent, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 && czy_wspierany BETWEEN ? AND 1 ORDER BY producent DESC");
    }
    else {  // Model A - Z
        furnacesQuery = con->prepareStatement("SELECT id_pieca, producent, model, czy_wspierany FROM piece WHERE id_pieca NOT LIKE 1 && czy_wspierany BETWEEN ? AND 1 ORDER BY model ASC");
    }

    if (ui.supportCheckBox->checkState() == Qt::Checked) {
        furnacesQuery->setInt(1, 1);
    }
    else {
        furnacesQuery->setInt(1, 0);
    }

    queryResult = furnacesQuery->executeQuery();

    while (queryResult->next()) {
        int furnaceId = queryResult->getInt(1);
        QTableWidgetItem* item;

        ui.furnacesList->insertRow(ui.furnacesList->rowCount());

        //  Manufacturer
        item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(2).asStdString()));
        item->setData(Qt::UserRole, QString::number(furnaceId));
        ui.furnacesList->setItem(ui.furnacesList->rowCount() - 1, 0, item);

        //  Model
        item = new QTableWidgetItem(QString::fromUtf8(queryResult->getString(3).asStdString()));
        item->setData(Qt::UserRole, QString::number(furnaceId));
        ui.furnacesList->setItem(ui.furnacesList->rowCount() - 1, 1, item);

        //  Support
        item = new QTableWidgetItem(QString::number(queryResult->getInt(4)));
        item->setData(Qt::UserRole, QString::number(furnaceId));
        ui.furnacesList->setItem(ui.furnacesList->rowCount() - 1, 2, item);
    }

    delete queryResult;
    delete furnacesQuery;
    delete con;
}

void furnacesWidget::on_deleteButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        customBasicDialog reject(this);
        reject.setMessage("Odmowa dostępu.");
        reject.exec();
    }
    else {
        yesNoDialog confirmation(this);
        confirmation.setMessage("Czy na pewno usunąć piec?");
        if (confirmation.exec()) {
            sql::Driver* driver;
            sql::Connection* con;
            sql::PreparedStatement* deleteFurnace;
            sql::PreparedStatement* replaceFurnace;


            driver = get_driver_instance();
            con = driver->connect(db_ip, db_login, db_password);

            sql::Statement* useDB;
            useDB = con->createStatement();
            useDB->execute("USE firma_piece");
            delete useDB;

            // replace furnace data with a reserved "empty" furnace to prevent database errors
            replaceFurnace = con->prepareStatement("UPDATE zlecenia SET id_pieca=1 WHERE zlecenia.id_pieca=?");
            replaceFurnace->setInt(1, ui.furnacesList->currentItem()->data(Qt::UserRole).toInt());

            replaceFurnace->execute();

            deleteFurnace = con->prepareStatement("DELETE FROM piece WHERE id_pieca=? && id_pieca NOT LIKE 1");
            deleteFurnace->setInt(1, ui.furnacesList->currentItem()->data(Qt::UserRole).toInt());

            deleteFurnace->execute();

            delete replaceFurnace;
            delete deleteFurnace;
            delete con;
            QMetaObject::invokeMethod(ui.refreshButton, "clicked");
        }
    }
}

void furnacesWidget::on_addButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        customBasicDialog reject(this);
        reject.setMessage("Odmowa dostępu.");
        reject.exec();
    }
    else {
        addFurnaceDialog addFurnace(this);

        if (addFurnace.exec()) {
            if (!addFurnace.fileNameLabel->text().isEmpty()) {
                if(!addFurnace.fileNameLabel->text().isEmpty()){
                    sql::Driver* driver;
                    sql::Connection* con;
                    sql::PreparedStatement* addFurnaceQuery;


                    driver = get_driver_instance();
                    con = driver->connect(db_ip, db_login, db_password);

                    sql::Statement* useDB;
                    useDB = con->createStatement();
                    useDB->execute("USE firma_piece");
                    delete useDB;

                    // preparing insert statement for the furnaces table in database
                    addFurnaceQuery = con->prepareStatement("INSERT INTO piece (model, producent, instrukcja, czy_wspierany) VALUES (?, ?, ?, 1)");

                    // set furnace model
                    addFurnaceQuery->setString(1, addFurnace.modelEdit->text().toStdString());

                    // set furnace manufacturer
                    addFurnaceQuery->setString(2, addFurnace.manufacturerEdit->text().toStdString());

                    // set PDF file as blob
                    ifstream ifs;
                    ifs.open(addFurnace.fileNameLabel->text().toStdString(), ios_base::binary);
                    istream& is = ifs;
                    addFurnaceQuery->setBlob(3, &is);

                    addFurnaceQuery->execute();

                    delete addFurnaceQuery;
                    delete con;

                    QMetaObject::invokeMethod(ui.refreshButton, "clicked");
                }
            }
            else {
                customBasicDialog fileError(this);
                fileError.setMessage("Wystąpił problem z przesłaniem pliku.");
                fileError.exec();
            }
        }
    }
}


void furnacesWidget::on_manualButton_clicked() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* getManualQuery;
    sql::ResultSet* queryResult;


    driver = get_driver_instance();
    con = driver->connect(db_ip, db_login, db_password);

    sql::Statement* useDB;
    useDB = con->createStatement();
    useDB->execute("USE firma_piece");
    delete useDB;

    // get blob containing the manual PDF file from database
    getManualQuery = con->prepareStatement("SELECT instrukcja, model FROM piece WHERE id_pieca=?");
    getManualQuery->setInt(1, ui.furnacesList->currentItem()->data(Qt::UserRole).toInt());

    queryResult = getManualQuery->executeQuery();
    while (queryResult->next()){
        break;
    }

    istream* is(queryResult->getBlob(1));

    ofstream of(("manual.pdf"), ios::binary);

    copy(istreambuf_iterator<char>(*is), istreambuf_iterator<char>(), ostreambuf_iterator<char>(of));

    QDesktopServices::openUrl(QUrl("manual.pdf"));

    delete queryResult;
    delete getManualQuery;
    delete con;
}

void furnacesWidget::on_editButton_clicked() {
    userSingleton& user = userSingleton::instance();

    // check the user's privileges
    if (user.getPosition() != "Kierownik") {
        customBasicDialog reject(this);
        reject.setMessage("Odmowa dostępu.");
        reject.exec();
    }
    else {
        editFurnaceDialog editFurnace(this);
        editFurnace.setFurnaceId(ui.furnacesList->currentItem()->data(Qt::UserRole).toInt());

        sql::Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* furnaceDataQuery;


        driver = get_driver_instance();
        con = driver->connect(db_ip, db_login, db_password);

        sql::Statement* useDB;
        useDB = con->createStatement();
        useDB->execute("USE firma_piece");
        delete useDB;

        // get furnace data into the line edit fields
        furnaceDataQuery = con->prepareStatement("SELECT model, producent, czy_wspierany FROM piece WHERE id_pieca = ?");
        furnaceDataQuery->setInt(1, editFurnace.getFurnaceId());
        sql::ResultSet* furnaceDataResult = furnaceDataQuery->executeQuery();
        while (furnaceDataResult->next()) {
            break;
        }

        // get model
        editFurnace.modelEdit->setText(QString::fromUtf8(furnaceDataResult->getString(1).asStdString()));

        // get manufacturer
        editFurnace.manufacturerEdit->setText(QString::fromUtf8(furnaceDataResult->getString(2).asStdString()));

        // get support
        if (furnaceDataResult->getInt(3) == 1) {
            editFurnace.supportLabel->setText("Tak");
        }
        else {
            editFurnace.supportLabel->setText("Nie");
        }

        if (editFurnace.exec()) {
            if (!editFurnace.fileNameLabel->text().isEmpty()) {
                if (!editFurnace.fileNameLabel->text().isEmpty()) {
                    
                    sql::PreparedStatement* editFurnaceQuery;
                    // preparing update statement for the furnaces table in database
                    editFurnaceQuery = con->prepareStatement("UPDATE piece SET model=?, producent=? WHERE id_pieca=?");

                    // set furnace model
                    editFurnaceQuery->setString(1, editFurnace.modelEdit->text().toStdString());

                    // set furnace manufacturer
                    editFurnaceQuery->setString(2, editFurnace.manufacturerEdit->text().toStdString());

                    // set furnace id for query
                    editFurnaceQuery->setInt(3, editFurnace.getFurnaceId());

                    editFurnaceQuery->execute();

                    delete editFurnaceQuery;
                }
            }
            else {
                customBasicDialog fileError(this);
                fileError.setMessage("Wystąpił problem z edytowaniem danych pieca.");
                fileError.exec();
            }
        }

        delete furnaceDataResult;
        delete furnaceDataQuery;
        delete con;

        QMetaObject::invokeMethod(ui.refreshButton, "clicked");
    }
}