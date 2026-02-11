#include "reservationview.h"
#include "ui_reservationview.h"
#include "session.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>

reservationView::reservationView(QString carId,
                                 QString brand,
                                 QWidget *parent)
    : QWidget(parent),
    ui(new Ui::reservationView),
    carId(carId)
{
    ui->setupUi(this);
    ui->carInfoLabel->setText("Selected Car: " + brand);

    ui->startDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate().addDays(1));
}

reservationView::~reservationView()
{
    delete ui;
}

void updateCarStatus(const QString &carId)
{
    QString path = QCoreApplication::applicationDirPath() + "/cars.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;
    QTextStream in(&file);

    while (!in.atEnd())
        lines.append(in.readLine());

    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (int i = 0; i < lines.size(); i++)
    {
        QStringList parts = lines[i].split(",");

        if (parts.size() == 5 && parts[0] == carId)
            parts[4] = "Reserved";

        out << parts.join(",") << "\n";
    }

    file.close();
}

void createPayment(const QString &carId)
{
    QString carPath = QCoreApplication::applicationDirPath() + "/cars.txt";
    QFile carFile(carPath);

    if (!carFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&carFile);
    int price = 0;

    while (!in.atEnd())
    {
        QStringList parts = in.readLine().split(",");
        if (parts.size() == 5 && parts[0] == carId)
        {
            price = parts[3].toInt();
            break;
        }
    }

    carFile.close();

    QString payPath = QCoreApplication::applicationDirPath() + "/payments.txt";
    QFile payFile(payPath);

    if (!payFile.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&payFile);
    out << "1," << carId << "," << price << ",Unpaid\n";

    payFile.close();
}


void reservationView::on_confirmPushButton_clicked()
{
    QDate start = ui->startDateEdit->date();
    QDate end = ui->endDateEdit->date();

    if (end <= start) {
        QMessageBox::warning(this, "Error",
                             "End date must be after start date");
        return;
    }

    QString path = QCoreApplication::applicationDirPath()
                   + "/reservations.txt";
    QFile file(path);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Could not save reservation");
        return;
    }

    QTextStream out(&file);

    out << session::userId << "," << carId << ","
        << start.toString("yyyy-MM-dd") << ","
        << end.toString("yyyy-MM-dd") << ",Pending\n";

    file.close();

    // تغییر وضعیت ماشین
    updateCarStatus(carId);

    // ساخت Payment
    createPayment(carId);

    QMessageBox::information(this, "Done",
                             "Reservation submitted & Car reserved");

    close();
}

void reservationView::on_cancelPushButton_clicked()
{

}

