#pragma once

#include <QDialog>
#include "ui_editjobdialog.h"

class editJobDialog : public QDialog, public Ui::editJobDialogClass
{
	Q_OBJECT

public:
	editJobDialog(QWidget *parent = nullptr);
	~editJobDialog();

private:
	 
};
