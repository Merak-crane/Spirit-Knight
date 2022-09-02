#include "StartInterface.h"
#include "Tutorial.h"
#include <QDesktopWidget>
#include <QDebug>

StartInterface::StartInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->local = local;
	qDebug() << local->GetUsername();
	QDesktopWidget w;
	int DeskWidth = 1280;
	int DeskHeight = 800;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo

	start->resize(240, 80);
	start->move(50, 500);
	QPixmap p1 = QPixmap(":/ui/Resource/image/ui/start.png");
	start->setIcon(p1);
	start->setIconSize(QSize(240, 80));
	start->setFlat(true);

	continued->resize(240, 80);
	continued->move(300, 500);
	QPixmap p100 = QPixmap(":/ui/Resource/image/ui/continue.png");
	continued->setIcon(p100);
	continued->setIconSize(QSize(240, 80));
	continued->setFlat(true);

	introduction->resize(240, 80);
	introduction->move(50, 650);
	QPixmap p5 = QPixmap(":/ui/Resource/image/ui/introduction.png");
	introduction->setIcon(p5);
	introduction->setIconSize(QSize(240, 80));
	introduction->setFlat(true);

	exit->resize(240, 80);
	exit->move(300, 650);
	QPixmap p6 = QPixmap(":/ui/Resource/image/ui/exit.png");
	exit->setIcon(p6);
	exit->setIconSize(QSize(240, 80));
	exit->setFlat(true);

	connect(introduction, &QPushButton::clicked, this, &StartInterface::OpenIntroduction);
	connect(exit, &QPushButton::clicked, this, &QWidget::close);
	connect(start, &QPushButton::clicked, this, &StartInterface::ModeChoose);
	connect(continued, &QPushButton::clicked, this, &StartInterface::OpenLoad);
}

void StartInterface::paintEvent(QPaintEvent* event) {
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.jpeg"));
	painter->end();
}

void StartInterface::OpenLoad(){
	LoadInterface* load = new LoadInterface(local);
	load->show();
	this->close();
}

void StartInterface::OpenIntroduction() {
	Tutorial* o = new Tutorial(local);
	o->show();
	this->close();
}

void StartInterface::ModeChoose() {
	ModeInterface* mode = new ModeInterface(local);
	mode->show();
	this->close();
}

StartInterface::~StartInterface()
{}
