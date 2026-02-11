#ifndef MYEXTENSIONSVIEW_H
#define MYEXTENSIONSVIEW_H

#include <QWidget>

namespace Ui {
class myExtensionsView;
}

class myExtensionsView : public QWidget
{
    Q_OBJECT

public:
    explicit myExtensionsView(QWidget *parent = nullptr);
    ~myExtensionsView();

private:
    Ui::myExtensionsView *ui;
    void loadExtensions();
};

#endif // MYEXTENSIONSVIEW_H
