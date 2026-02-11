#include "extensionview.h"
#include "ui_extensionview.h"
#include "session.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDate>

extensionView::extensionView(QString carId,
                             QString oldEndDate,
                             QWidget *parent)
    : QWidget(parent),
    ui(new Ui::extensionView),
    carId(carId),
    oldEndDate(oldEndDate)
{
    ui->setupUi(this);
    ui->infoLabel->setText(
        "Car ID: " + carId + "\nCurrent End: " + oldEndDate
        );

    ui->newEndDateEdit->setDate(
        QDate::fromString(oldEndDate, "yyyy-MM-dd").addDays(1)
        );
}

extensionView::~extensionView()
{
    delete ui;
}

void extensionView::on_submitPushButton_clicked()
{
    QDate newDate = ui->newEndDateEdit->date();
    QDate oldDate = QDate::fromString(oldEndDate, "yyyy-MM-dd");

    if (newDate <= oldDate) {
        QMessageBox::warning(this, "Error",
                             "New date must be after current end date");
        return;
    }

    QString path = QCoreApplication::applicationDirPath()
                   + "/extensions.txt";
    QFile file(path);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error",
                             "Could not save extension request");
        return;
    }

    QTextStream out(&file);

    out << session::userId << "," << carId << ","
        << oldEndDate << ","
        << newDate.toString("yyyy-MM-dd")
        << ",Pending\n";

    file.close();

    QMessageBox::information(this, "Done",
                             "Extension request submitted");

    close();
}

void extensionView::on_cancelPushButton_clicked()
{
    close();
}
