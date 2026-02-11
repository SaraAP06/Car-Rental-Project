#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "customerdashboard.h"
#include "session.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QCoreApplication>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginPushButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->messageLabel->setText("Fill all fields");
        return;
    }

    QString path = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->messageLabel->setText("users file error");
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() != 3) continue;

        if (parts[1] == username && parts[2] == password) {
            session::userId = parts[0].toInt();
            session::username = username;

            QMessageBox::information(this, "Login", "Login successful");

            customerdashboard *d = new customerdashboard();
            d->show();
            this->close();
            return;
        }
    }

    ui->messageLabel->setText("Wrong username or password");
}

int LoginWindow::getNextUserId()
{
    QString path = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QTextStream in(&file);
    int lastId = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 1)
            lastId = parts[0].toInt();
    }

    file.close();
    return lastId + 1;
}

bool LoginWindow::usernameExists(const QString &username)
{
    QString path = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 2 && parts[1] == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void LoginWindow::on_registerPushButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        ui->messageLabel->setText("Fill all fields");
        return;
    }

    if (usernameExists(username))
    {
        ui->messageLabel->setText("Username already exists");
        return;
    }

    int newId = getNextUserId();

    QString path = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(path);

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        ui->messageLabel->setText("Error saving user");
        return;
    }

    QTextStream out(&file);
    out << newId << "," << username << "," << password << "\n";

    file.close();

    ui->messageLabel->setText("Register successful");
}
