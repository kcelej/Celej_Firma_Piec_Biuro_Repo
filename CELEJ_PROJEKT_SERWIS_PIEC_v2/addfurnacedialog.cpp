#include "stdafx.h"
#include "addfurnacedialog.h"

addFurnaceDialog::addFurnaceDialog(QWidget *parent)
	: QDialog(parent)
{
    hasManual = false;
	setupUi(this);

    connect(this->uploadFileButton, SIGNAL(clicked()), SLOT(browse()));
}

addFurnaceDialog::~addFurnaceDialog()
{}

void addFurnaceDialog::browse() {
    QFileDialog addFile(this);
    QString filePath = addFile.getOpenFileName(this, tr("Instrukcja"), QDir::currentPath(), tr("Pliki PDF (*.pdf)"));   // browse PDF files on the device
    
    if (!filePath.isEmpty()) {
        this->fileNameLabel->setText(filePath);
        hasManual = true;
    }
}

bool addFurnaceDialog::isManualIncluded() {
    return hasManual;
}