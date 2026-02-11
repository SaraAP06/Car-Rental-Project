#include "myreservationsview.h"
#include "ui_myreservationsview.h"
#include "extensionview.h"
#include "session.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QCoreApplication>

myReservationsView::myReservationsView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::myReservationsView)
{
    ui->setupUi(this);
    loadReservations();
}

myReservationsView::~myReservationsView()
{
    delete ui;
}

void myReservationsView::loadReservations()
{
    QString path = QCoreApplication::applicationDirPath()
    + "/reservations.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Could not open reservations file");
        return;
    }

    QTextStream in(&file);
    int row = 0;

    ui->reservationTableWidget->setRowCount(0);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() != 5)
            continue;

        // فقط رزروهای customer فعلی
        if (parts[0].toInt() != session::userId)
            continue;

        ui->reservationTableWidget->insertRow(row);

        for (int col = 0; col < 5; col++) {
            ui->reservationTableWidget->setItem(
                row, col,
                new QTableWidgetItem(parts[col])
                );
        }
        row++;
    }

    file.close();
}

void myReservationsView::on_extensionPushButton_clicked()
{
    int row = ui->reservationTableWidget->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Error",
                             "Select a reservation first");
        return;
    }

    QString carId =
        ui->reservationTableWidget->item(row, 1)->text();
    QString endDate =
        ui->reservationTableWidget->item(row, 3)->text();

    extensionView *view =
        new extensionView(carId, endDate);
    view->show();
}
