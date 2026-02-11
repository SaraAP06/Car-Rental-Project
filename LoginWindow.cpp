#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "customerdashboard.h"
#include <QMessageBox>

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
    QString username =
        ui->usernameLineEdit->text();
    QString password =
        ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        ui->messageLabel->setText("Please fill all fields.");
        return;
    }
    //فعلا فیک بعدا وصل میشه به manager
    if (username == "test" && password == "1234")
    {
        QMessageBox::information(this, "Login", "Login successful");
        customerdashboard *dashboard = new customerdashboard();
        dashboard->show();
        this->close();
    }
    else
    {
        ui->messageLabel->setText("Invalid username or password.");
    }
}

void LoginWindow::on_registerPushButton_clicked()
{
    QMessageBox::information(this, "Register", "Register page not implemented yet");
}



