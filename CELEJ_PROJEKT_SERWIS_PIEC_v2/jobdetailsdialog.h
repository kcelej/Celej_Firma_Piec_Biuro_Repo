#pragma once

#include <QDialog>
#include "ui_jobdetailsdialog.h"

class jobDetailsDialog : public QDialog, public Ui::jobDetailsDialogClass
{
	Q_OBJECT

public:
	jobDetailsDialog(QWidget *parent = nullptr);
	~jobDetailsDialog();

	void setJobId(QString id);	// set the id for the job details dialog window
	void updateCustomerData();	// update customer data with the most recent version
	void updateWorkerData();	// update worker data with the most recent version
	void updateFurnaceData();	// update furnace data with the most recent version
	void updateJobStatus();	// toggle the current job's status
	void updateJobData();	// update job data with the most recent version
	void updateAllData();	// update all data in the job details dialog window
private:
	QString jobId;
private slots:
	void on_changeStatusButton_clicked();
	void on_workerChangeButton_clicked();
	void on_furnaceChangeButton_clicked();
	void on_customerChangeButton_clicked();
	void on_jobDataChangeButton_clicked();
	void on_deleteButton_clicked();
};
