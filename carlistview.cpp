#include "carlistview.h"
#include "ui_carlistview.h"
#include "reservationview.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QCoreApplication>

carListView::carListView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::carListView)
{
    ui->setupUi(this);

    // تنظیمات ساده جدول
    ui->CarTableWidget->setColumnCount(5);
    ui->CarTableWidget->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Brand" << "Type" << "Price" << "Status"
        );
    ui->CarTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CarTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->CarTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    loadCarsFromFile();
}

carListView::~carListView()
{
    delete ui;
}

void carListView::loadCarsFromFile()
{
    QString path = QCoreApplication::applicationDirPath() + "/cars.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    allCars.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 5)
            allCars.append(parts);
    }
    file.close();

    showCars(allCars);
}

void carListView::showCars(const QList<QStringList>& cars)
{
    ui->CarTableWidget->setRowCount(0);

    for (int i = 0; i < cars.size(); i++) {
        ui->CarTableWidget->insertRow(i);
        for (int j = 0; j < 5; j++) {
            ui->CarTableWidget->setItem(i, j,
                                        new QTableWidgetItem(cars[i][j]));
        }
    }
}

void carListView::on_reservePushButton_clicked()
{
    int row = ui->CarTableWidget->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a car");
        return;
    }

    QString status = ui->CarTableWidget->item(row, 4)->text();
    if (status != "Available") {
        QMessageBox::warning(this, "Error", "Car is not available");
        return;
    }

    QString carId = ui->CarTableWidget->item(row, 0)->text();
    QString brand = ui->CarTableWidget->item(row, 1)->text();

    reservationView *view = new reservationView(carId, brand);
    view->show();
}

void carListView::on_filterPushButton_clicked()
{
    QString brand = ui->brandLineEdit->text().toLower();
    QString type = ui->typeLineEdit->text().toLower();
    QString maxPriceText = ui->maxPriceLineEdit->text();

    QList<QStringList> filtered;

    for (int i = 0; i < allCars.size(); i++) {
        QStringList car = allCars[i];

        if (!brand.isEmpty() &&
            !car[1].toLower().contains(brand))
            continue;

        if (!type.isEmpty() &&
            !car[2].toLower().contains(type))
            continue;

        if (!maxPriceText.isEmpty() &&
            car[3].toInt() > maxPriceText.toInt())
            continue;

        filtered.append(car);
    }

    showCars(filtered);
}
