#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginPushButton_clicked();

    void on_registerPushButton_clicked();

private:
    Ui::LoginWindow *ui;
    int getNextUserId();
    bool usernameExists(const QString &username);
};
#endif // LOGINWINDOW_H
