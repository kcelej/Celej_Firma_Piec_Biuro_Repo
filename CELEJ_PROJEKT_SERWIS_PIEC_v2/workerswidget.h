#pragma once

#include <QWidget>
#include "ui_workerswidget.h"

class workersWidget : public QWidget
{
	Q_OBJECT

public:
	workersWidget(QWidget *parent = nullptr);
	~workersWidget();

private:
	Ui::workersWidgetClass ui;
private slots:
	void on_refreshButton_clicked();
	void on_addButton_clicked();
	void on_deleteButton_clicked();
	void on_editButton_clicked();
};
