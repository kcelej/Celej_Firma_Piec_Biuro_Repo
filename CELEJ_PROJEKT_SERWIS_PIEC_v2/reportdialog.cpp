#include "stdafx.h"
#include "reportdialog.h"

#include <QtCharts/qlineseries.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qdatetimeaxis.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qchartview.h>


#include <QtCharts/qbarset.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarcategoryaxis.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "user.h"
#include "dbData.h"
#include "custombasicdialog.h"

reportDialog::reportDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

reportDialog::~reportDialog()
{}


void reportDialog::on_generateButton_clicked() {
	try {
        this->stackedWidget->currentWidget()->deleteLater();    // clear the stacked widget to update with the new one later

    //database connection
        sql::Driver* driver;
        sql::Connection* con;

        driver = get_driver_instance();
        con = driver->connect(db_ip, db_login, db_password);

        sql::Statement* useDB;
        useDB = con->createStatement();
        useDB->execute("USE firma_piece");
        delete useDB;



        // variables containing dates taken from the prompt
        QDate startDate = this->fromDate->date();
        QDate endDate = this->toDate->date();

        QBarSeries* series = new QBarSeries();

        int maxJobs = 0;    // the highest amount of jobs in the month, used for chart creation later

        QString qstringDate;    // used to store month and year numbers as a string containing date formatted as mm-YYYY (where mm is month and YYYY is year)
        QStringList categories; // stores categories (in this chart dates are the categories)

        QBarSet* startedJobs = new QBarSet("Zgłoszone zlecenia");   // chart data sets visualising started jobs
        QBarSet* endedJobs = new QBarSet("Zakończone zlecenia");   // chart data sets visualising ended jobs

        // (added start/end month/year as sepearete variables for readability
        // start date
        int startMonth = startDate.month();
        int startYear = startDate.year();

        //end date
        int endMonth = endDate.month();
        int endYear = endDate.year();

        // create data for both axies for each month between the selected start date and end date
        for (int i = startYear; i <= endYear; i++) {	// years
            int j = 0;
            int end = 0;
            if (i == endYear) {		// months
                if (startYear < endYear) {
                    j = 1;
                }
                else {
                    j = startMonth;
                }
                end = endMonth;
            }
            else {
                if (i == startYear) {
                    j = startMonth;
                }
                else {
                    j = 1;
                }
                end = 12;
            }
            for (j; j <= end; j++) {
                sql::PreparedStatement* jobStartData;
                sql::PreparedStatement* jobEndData;

                jobStartData = con->prepareStatement("SELECT beg.liczba_zlecen, beg.miesiac_zgloszenia, beg.rok_zgloszenia FROM (SELECT COUNT(id_zlecenia) AS liczba_zlecen, MONTH(data_zgloszenia) AS miesiac_zgloszenia, YEAR(data_zgloszenia) AS rok_zgloszenia FROM zlecenia GROUP BY miesiac_zgloszenia) AS beg WHERE beg.miesiac_zgloszenia=? && beg.rok_zgloszenia=? LIMIT 1");

                jobEndData = con->prepareStatement("SELECT end.liczba_zlecen, end.miesiac_zakonczenia, end.rok_zakonczenia FROM (SELECT COUNT(id_zlecenia) AS liczba_zlecen, MONTH(data_zakonczenia) AS miesiac_zakonczenia, YEAR(data_zakonczenia) AS rok_zakonczenia FROM zlecenia GROUP BY miesiac_zakonczenia) AS end WHERE end.miesiac_zakonczenia=? && end.rok_zakonczenia=? LIMIT 1");


                // set month and year for started jobs query
                jobStartData->setInt(1, j);
                jobStartData->setInt(2, i);

                // set month and year for ended jobs query
                jobEndData->setInt(1, j);
                jobEndData->setInt(2, i);

                sql::ResultSet* startResults = jobStartData->executeQuery();   // query result for number of jobs started in 'i' year and 'j' month
                sql::ResultSet* endResults = jobEndData->executeQuery();   // query result for number of jobs ended in 'i' year and 'j' month

                int startNum = 0;   // storage for number of jobs started
                while (startResults->next()) {
                    startNum = startResults->getInt(1);
                    if (startNum > 0) {
                        if (maxJobs < startNum) {
                            maxJobs = startNum;
                        }
                    }
                }
                *startedJobs << startNum;   // add the number of started jobs to set

                int endNum = 0; // storage for number of jobs ended
                while (endResults->next()) {
                    endNum = endResults->getInt(1);
                    if (endNum > 0) {
                        if (maxJobs < endNum) {
                            maxJobs = endNum;
                        }
                    }
                }
                *endedJobs << endNum;   // add the number of ended jobs to set

                qstringDate = QString::number(j) + "-" + QString::number(i);
                categories << qstringDate;  // add queries' date to set

                delete startResults;
                delete endResults;
                delete jobStartData;
                delete jobEndData;
            }
        }
        //#############################################################################################



        series->append(startedJobs);
        series->append(endedJobs);

        // create the chart
        QChart* chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Liczba zleceń");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // create the chart's X axis
        QBarCategoryAxis* axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // create the chart's Y axis
        QValueAxis* axisY = new QValueAxis();
        maxJobs++;  // increase the highest Y axis value for readability
        axisY->setRange(0, maxJobs);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView* chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        this->stackedWidget->addWidget(chartView);  // view the newly created chart widget
	}
    catch (sql::SQLException) {
        QMessageBox::information(this, "Błąd", "Wystąpił problem podczas łączenia z bazą.");
    }
}