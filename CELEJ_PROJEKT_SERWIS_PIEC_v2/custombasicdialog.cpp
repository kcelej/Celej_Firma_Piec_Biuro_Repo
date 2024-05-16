#include "stdafx.h"
#include "custombasicdialog.h"

void customBasicDialog::setMessage(QString newDialogMessage) {
	this->dialogMessage->setText(newDialogMessage);
}


customBasicDialog::customBasicDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	
}

customBasicDialog::~customBasicDialog()
{}

