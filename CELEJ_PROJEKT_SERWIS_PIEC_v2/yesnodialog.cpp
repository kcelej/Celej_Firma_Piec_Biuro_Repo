#include "stdafx.h"
#include "yesnodialog.h"

yesNoDialog::yesNoDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

yesNoDialog::~yesNoDialog()
{}

void yesNoDialog::setMessage(QString newDialogMessage) {
	this->dialogMessage->setText(newDialogMessage);
}