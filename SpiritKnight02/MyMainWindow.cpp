#include "MyMainWindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);    
    QDesktopWidget w;
    int DeskWidth = w.width() / 2;
    int DeskHeight = w.height() / 2;//获取设备的分辨率
    this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
    this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
    this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/Resource/image/Desktop.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
