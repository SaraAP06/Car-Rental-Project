#ifndef PAYMENTVIEW_H
#define PAYMENTVIEW_H

#include <QWidget>

namespace Ui {
class paymentView;
}

class paymentView : public QWidget
{
    Q_OBJECT

public:
    explicit paymentView(QWidget *parent = nullptr);
    ~paymentView();

private slots:
    void on_payPushButton_clicked();

    void on_backPushButton_clicked();

private:
    Ui::paymentView *ui;
    void loadPayments();
};

#endif // PAYMENTVIEW_H
