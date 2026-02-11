#ifndef CARLISTVIEW_H
#define CARLISTVIEW_H

#include <QWidget>
#include <QString>
#include <QList>

namespace Ui {
class carListView;
}

class carListView : public QWidget
{
    Q_OBJECT

public:
    explicit carListView(QWidget *parent = nullptr);
    ~carListView();

private slots:
    void on_reservePushButton_clicked();

    void on_filterPushButton_clicked();

private:
    Ui::carListView *ui;
    void loadCars();
    QString selectedCarId;

    QList<QStringList> allCars;
    void loadCarsFromFile();
    void showCars(const QList<QStringList>&cars);
};

#endif // CARLISTVIEW_H
