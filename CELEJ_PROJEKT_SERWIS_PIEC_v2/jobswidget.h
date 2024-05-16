#pragma once

#include <QWidget>
#include "ui_jobswidget.h"

class jobsWidget : public QWidget
{
	Q_OBJECT

public:
	jobsWidget(QWidget *parent = nullptr);
	~jobsWidget();

private:
	Ui::jobsWidgetClass ui;
private slots:
	void on_refreshButton_clicked();
	void on_detailsButton_clicked();
	void on_addButton_clicked();
	void on_reportButton_clicked();
};
