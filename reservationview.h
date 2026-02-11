#ifndef RESERVATIONVIEW_H
#define RESERVATIONVIEW_H

#include <QWidget>
#include <QString>
namespace Ui {
class reservationView;
}

class reservationView : public QWidget
{
    Q_OBJECT

public:
    explicit reservationView(QString carId, QString brand, QWidget *parent = nullptr);
    ~reservationView();

private slots:
    void on_confirmPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::reservationView *ui;
    QString carId;
};

#endif // RESERVATIONVIEW_H
