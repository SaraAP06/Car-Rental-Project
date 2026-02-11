#ifndef EXTENSIONVIEW_H
#define EXTENSIONVIEW_H

#include <QWidget>
#include <QString>

namespace Ui {
class extensionView;
}

class extensionView : public QWidget
{
    Q_OBJECT

public:
    explicit extensionView(QString carId, QString oldEndDate, QWidget *parent = nullptr);
    ~extensionView();

private slots:
    void on_submitPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::extensionView *ui;
    QString carId;
    QString oldEndDate;
};

#endif // EXTENSIONVIEW_H
