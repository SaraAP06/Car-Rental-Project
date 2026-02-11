#ifndef MYRESERVATIONSVIEW_H
#define MYRESERVATIONSVIEW_H

#include <QWidget>

namespace Ui {
class myReservationsView;
}

class myReservationsView : public QWidget
{
    Q_OBJECT

public:
    explicit myReservationsView(QWidget *parent = nullptr);
    ~myReservationsView();

private slots:
    void on_extensionPushButton_clicked();

private:
    Ui::myReservationsView *ui;
    void loadReservations();
};

#endif // MYRESERVATIONSVIEW_H
