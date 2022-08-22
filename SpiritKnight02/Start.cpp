#include "Start.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QIcon>
#include <QString>
#include <QSound>

Start::Start(QWidget *parent)
	: QWidget(parent)
{
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle(QString::fromUtf16(u"Ӣ����ʿ"));//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo
	connect(exit, &QPushButton::clicked, this, &QWidget::close);
	connect(start, &QPushButton::clicked, this, &Start::startmapcreate);
	connect(continued, &QPushButton::clicked, this, &Start::openload);
	connect(returnbtn, &QPushButton::clicked, this, &Start::returnback);
	connect(start, &QPushButton::clicked, this, &QWidget::close);
	connect(load1btn, &QPushButton::clicked, this, &Start::load_1);
	connect(load2btn, &QPushButton::clicked, this, &Start::load_2);
	connect(load3btn, &QPushButton::clicked, this, &Start::load_3);
	connect(help, &QPushButton::clicked, this, &Start::openhelp);
}

Start::~Start()
{}

void Start::paintEvent(QPaintEvent* Event) {
	QPainter painter1(this);
	painter1.drawPixmap(0,0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.jpeg"));
}