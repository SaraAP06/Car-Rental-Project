#include "customerdashboard.h"
#include "ui_customerdashboard.h"
#include "carlistview.h"
#include "myreservationsview.h"
#include "paymentview.h"
#include "myextensionsview.h"

customerdashboard::customerdashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::customerdashboard)
{
    ui->setupUi(this);
}

customerdashboard::~customerdashboard()
{
    delete ui;
}

void customerdashboard::on_viewCarPushButton_clicked()
{
    carListView *view = new carListView();
    view->show();
}


void customerdashboard::on_myReservationPushButton_clicked()
{
    myReservationsView *view = new myReservationsView();
    view->show();
}


void customerdashboard::on_paymentsPushButton_clicked()
{
    paymentView *view = new paymentView();
    view->show();
}


void customerdashboard::on_LogoutPushButton_clicked()
{
    close();
}


void customerdashboard::on_pmyExtensionsPushButton_clicked()
{
    myExtensionsView *view = new myExtensionsView();
    view->show();
}
