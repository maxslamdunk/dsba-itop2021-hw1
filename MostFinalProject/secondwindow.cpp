#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void paint(QPainter* painter)
{
    painter->setBrush(Qt::black);
    QPointF points[4];
    points[0] = QPointF(120, 100);
    points[1] = QPointF(280, 130);
    points[2] = QPointF(280, 370);
    points[3] = QPointF(120, 340);
    painter->drawPolygon(points, 4);
    QPen myPenG;
    myPenG.setColor(Qt::lightGray);
    QPen myPenW;
    myPenW.setWidth(3);
    QPen myPenR;
    myPenR.setColor(Qt::red);
    painter->setPen(myPenG);
    painter->drawLine(285, 125, 125, 95);
    painter->drawLine(290, 120, 130, 90);
    painter->drawLine(295, 115, 135, 85);
    painter->drawLine(300, 110, 140, 80);
    painter->drawLine(285, 365, 285, 125);
    painter->drawLine(290, 360, 290, 120);
    painter->drawLine(295, 355, 295, 115);
    painter->drawLine(300, 350, 300, 110);

    painter->setPen(myPenW);
    painter->drawLine(121, 102, 146, 76);
    painter->drawLine(305, 105, 145, 75);
    painter->eraseRect(119, 101, 1, 2);
    painter->eraseRect(143, 72, 2, 2);
    painter->eraseRect(143, 74, 1, 1);
    painter->eraseRect(143, 74, 2, 2);
    painter->eraseRect(144, 75, 1, 1);
    painter->eraseRect(143, 76, 1, 1);
    painter->eraseRect(142, 77, 1, 1);
    painter->drawLine(305, 345, 305, 105);

    painter->setPen(myPenG);
    painter->setFont(QFont("PHOSPHATE", 37));
    QRect rect = QRect(62, 375, 300, 50);
    painter->drawText(rect, "Cook");
    painter->setBrush(Qt::darkRed);
    painter->drawRect(rect);
    painter->drawText(rect, "MyRecipe");
}

void SecondWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    paint(&painter);
}
