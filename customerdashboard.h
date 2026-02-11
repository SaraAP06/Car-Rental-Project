#ifndef CUSTOMERDASHBOARD_H
#define CUSTOMERDASHBOARD_H

#include <QMainWindow>

namespace Ui {
class customerdashboard;
}

class customerdashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit customerdashboard(QWidget *parent = nullptr);
    ~customerdashboard();

private slots:
    void on_viewCarPushButton_clicked();

    void on_myReservationPushButton_clicked();

    void on_paymentsPushButton_clicked();

    void on_LogoutPushButton_clicked();

    void on_pmyExtensionsPushButton_clicked();

private:
    Ui::customerdashboard *ui;
};

#endif // CUSTOMERDASHBOARD_H
