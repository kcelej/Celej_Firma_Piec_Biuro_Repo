#include "stdafx.h"
#include "editfurnacedialog.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "dbData.h"
#include <iostream>
#include <fstream>

using namespace std;

editFurnaceDialog::editFurnaceDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	connect(this->uploadFileButton, SIGNAL(clicked()), SLOT(browse()));
}

editFurnaceDialog::~editFurnaceDialog()
{}

void editFurnaceDialog::browse() {
    QFileDialog addFile(this);
    addFile.setWindowTitle("Dodaj instrukcję");
    QString filePath = addFile.getOpenFileName(this, tr("Instrukcja"), QDir::currentPath(), tr("Pliki PDF (*.pdf)"));   // browse PDF files on the device

    if (!filePath.isEmpty()) {
        this->fileNameLabel->setText(filePath);
    }
}

void editFurnaceDialog::setFurnaceId(int i) {
    furnaceId = i;
}

int editFurnaceDialog::getFurnaceId() {
    return furnaceId;
}

void editFurnaceDialog::on_switchSupportButton_clicked() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* switchFurnaceSupport;


    driver = get_driver_instance();
    con = driver->connect(db_ip, db_login, db_password);

    sql::Statement* useDB;
    useDB = con->createStatement();
    useDB->execute("USE firma_piece");
    delete useDB;

    if (this->supportLabel->text() == "Tak") {
        switchFurnaceSupport = con->prepareStatement("UPDATE piece SET czy_wspierany=0 WHERE id_pieca=?");
        this->supportLabel->setText("Nie");
    }
    else {
        switchFurnaceSupport = con->prepareStatement("UPDATE piece SET czy_wspierany=1 WHERE id_pieca=?");
        this->supportLabel->setText("Tak");
    }
    switchFurnaceSupport->setInt(1, furnaceId);

    switchFurnaceSupport->execute();

    delete switchFurnaceSupport;
    delete con;
}

void editFurnaceDialog::on_confirmManualButton_clicked() {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* addFileQuery;


        driver = get_driver_instance();
        con = driver->connect(db_ip, db_login, db_password);

        sql::Statement* useDB;
        useDB = con->createStatement();
        useDB->execute("USE firma_piece");
        delete useDB;

        // preparing insert statement for the furnaces table in database
        addFileQuery = con->prepareStatement("UPDATE piece SET instrukcja=? WHERE id_pieca=?");

        // set PDF file as blob
        ifstream ifs;
        ifs.open(fileNameLabel->text().toStdString(), ios_base::binary);
        istream& is = ifs;
        addFileQuery->setBlob(1, &is);

        // set furnace id
        addFileQuery->setInt(2, furnaceId);

        addFileQuery->execute();

        QMessageBox::information(this, "Dodano instrukcję", "Instrukcja pieca została pomyślnie zmieniona.");

        delete addFileQuery;
        delete con;
    }
    catch (sql::SQLException) {
        QMessageBox::warning(this, "Błąd", "Wystąpił błąd z podanym plikiem.");
    }
}