#include "LoadInterface.h"
#include "StartInterface.h"
#include <QDesktopWidget>
#include <QDebug>

LoadInterface::LoadInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->local = local;
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo

	load_one->resize(240, 80);
	load_one->move(200, 600);
	QPixmap p9 = QPixmap(":/ui/Resource/image/ui/load1.png");
	load_one->setIcon(p9);
	load_one->setIconSize(QSize(240, 80));
	load_one->setFlat(true);

	load_two->resize(240, 80);
	load_two->move(500, 600);
	QPixmap p10 = QPixmap(":/ui/Resource/image/ui/load2.png");
	load_two->setIcon(p10);
	load_two->setIconSize(QSize(240, 80));
	load_two->setFlat(true);

	load_three->resize(240, 80);
	load_three->move(800, 600);
	QPixmap p11 = QPixmap(":/ui/Resource/image/ui/load2.png");
	load_three->setIcon(p11);
	load_three->setIconSize(QSize(240, 80));
	load_three->setFlat(true);

	returnbtn_load->resize(240, 80);
	returnbtn_load->move(800, 650);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/returnback.png");
	returnbtn_load->setIcon(p15);
	returnbtn_load->setIconSize(QSize(240, 80));
	returnbtn_load->setFlat(true);

	connect(returnbtn_load, &QPushButton::clicked, this, &LoadInterface::ReturnBack);
	//connect(load_one, &QPushButton::clicked, this, &LoadInterface::load_1);
	//connect(load_two, &QPushButton::clicked, this, &LoadInterface::load_2);
	//connect(load_three, &QPushButton::clicked, this, &LoadInterface::load_3);
}

void LoadInterface::ReturnBack() {
	StartInterface* load = new StartInterface(local);
	load->show();
	this->close();
}

LoadInterface::~LoadInterface()
{}
