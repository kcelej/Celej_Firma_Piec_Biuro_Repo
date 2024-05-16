#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private:
    Ui::mainWindowClass ui;
    void login();   // show the login dialog window
private slots:
    void on_logoutButton_clicked();
    void on_jobButton_clicked();
    void on_customerButton_clicked();
    void on_workerButton_clicked();
    void on_furnaceButton_clicked();
};
