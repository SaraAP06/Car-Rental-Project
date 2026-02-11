#include "paymentview.h"
#include "ui_paymentview.h"
#include "session.h"

#include <QFile>
#include <QTextStream>
#include "paymentview.h"
#include "ui_paymentview.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QCoreApplication>

paymentView::paymentView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::paymentView)
{
    ui->setupUi(this);
    loadPayments();
}

paymentView::~paymentView()
{
    delete ui;
}

void paymentView::loadPayments()
{
    QString path = QCoreApplication::applicationDirPath()
    + "/payments.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Could not open payments file");
        return;
    }

    QTextStream in(&file);
    int row = 0;

    ui->paymentTableWidget->setRowCount(0);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() != 4)
            continue;

        if (parts[0].toInt() != session::userId)
            continue;

        ui->paymentTableWidget->insertRow(row);

        ui->paymentTableWidget->setItem(row, 0,
                                        new QTableWidgetItem(parts[1]));
        ui->paymentTableWidget->setItem(row, 1,
                                        new QTableWidgetItem(parts[2]));
        ui->paymentTableWidget->setItem(row, 2,
                                        new QTableWidgetItem(parts[3]));

        row++;
    }

    file.close();
}

void paymentView::on_payPushButton_clicked()
{
    int row = ui->paymentTableWidget->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Error",
                             "Select a payment first");
        return;
    }

    QString status = ui->paymentTableWidget
                         ->item(row, 2)->text();

    if (status == "Paid") {
        QMessageBox::information(this, "Info",
                                 "Already paid");
        return;
    }

    QMessageBox::information(this, "Payment",
                             "Payment successful");

    ui->paymentTableWidget->setItem(row, 2,
                                    new QTableWidgetItem("Paid"));
}

void paymentView::on_backPushButton_clicked()
{

}
