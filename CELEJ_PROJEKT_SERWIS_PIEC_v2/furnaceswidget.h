#pragma once

#include <QWidget>
#include "ui_furnaceswidget.h"

class furnacesWidget : public QWidget
{
	Q_OBJECT

public:
	furnacesWidget(QWidget *parent = nullptr);
	~furnacesWidget();

private:
	Ui::furnacesWidgetClass ui;
private slots:
	void on_refreshButton_clicked();
	void on_deleteButton_clicked();
	void on_addButton_clicked();
	void on_manualButton_clicked();
	void on_editButton_clicked();
};
