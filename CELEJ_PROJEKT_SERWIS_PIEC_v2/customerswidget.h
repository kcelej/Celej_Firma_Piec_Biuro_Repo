#pragma once

#include <QWidget>
#include "ui_customerswidget.h"

class customersWidget : public QWidget
{
	Q_OBJECT

public:
	customersWidget(QWidget *parent = nullptr);
	~customersWidget();

private:
	Ui::customersWidgetClass ui;
private slots:
	void on_refreshButton_clicked();
	void on_deleteButton_clicked();
	void on_addButton_clicked();
	void on_editButton_clicked();
};
