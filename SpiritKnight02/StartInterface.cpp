#include "StartInterface.h"
#include <QDesktopWidget>
#include <QDebug>

StartInterface::StartInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->local = local;
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle(QString::fromUtf16(u"Ӣ����ʿ"));//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo

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

void StartInterface::OpenLoad(){
	LoadInterface* load = new LoadInterface(local);
	load->show();
	this->close();
}

void StartInterface::OpenIntroduction() {
	//IntroInterface* intro = new IntroInterface;
	//intro->show();
	//this->close();
}

void StartInterface::ModeChoose() {
	ModeInterface* mode = new ModeInterface(local);
	mode->show();
	this->close();
}

StartInterface::~StartInterface()
{}