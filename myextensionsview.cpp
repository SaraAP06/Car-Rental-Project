#include "myextensionsview.h"
#include "ui_myextensionsview.h"
#include "session.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QCoreApplication>

myExtensionsView::myExtensionsView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::myExtensionsView)
{
    ui->setupUi(this);
    loadExtensions();
}

myExtensionsView::~myExtensionsView()
{
    delete ui;
}

void myExtensionsView::loadExtensions()
{
    QString path = QCoreApplication::applicationDirPath()
    + "/extensions.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Could not open extensions file");
        return;
    }

    QTextStream in(&file);
    int row = 0;

    ui->extensionTableWidget->setRowCount(0);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() < 5)
            continue;

        if (parts[0].toInt() != session::userId)
            continue;

        ui->extensionTableWidget->insertRow(row);

        ui->extensionTableWidget->setItem(row, 0,
                                          new QTableWidgetItem(parts[1]));
        ui->extensionTableWidget->setItem(row, 1,
                                          new QTableWidgetItem(parts[2]));
        ui->extensionTableWidget->setItem(row, 2,
                                          new QTableWidgetItem(parts[3]));
        ui->extensionTableWidget->setItem(row, 3,
                                          new QTableWidgetItem(parts[4]));

        row++;
    }

    file.close();
}
