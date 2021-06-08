#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui
{
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private:
    Ui::SecondWindow *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // SECONDWINDOW_H
