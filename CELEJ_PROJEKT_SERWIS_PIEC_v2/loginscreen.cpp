#include "stdafx.h"
#include "loginscreen.h"
#include <iostream>
#include <fstream>

using namespace std;

loginScreen::loginScreen(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

loginScreen::~loginScreen()
{}

void loginScreen::on_loginConfirmButton_clicked() {

}

void loginScreen::on_loginCancelButton_clicked() {
	// delete files created by the program
	ofstream of("manual.pdf");
	of.close();
	remove("manual.pdf");
	// exit the program after the login is cancelled
	exit(0);
}