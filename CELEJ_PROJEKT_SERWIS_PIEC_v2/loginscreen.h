#pragma once

#include <QDialog>
#include "ui_loginscreen.h"

class loginScreen : public QDialog, public Ui::loginScreenClass
{
	Q_OBJECT

public:
	loginScreen(QWidget *parent = nullptr);
	~loginScreen();

private:
	 
private slots:
	void on_loginConfirmButton_clicked();
	void on_loginCancelButton_clicked();
};
