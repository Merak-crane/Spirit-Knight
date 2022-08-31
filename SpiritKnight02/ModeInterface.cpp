#include "ModeInterface.h"
#include "StartInterface.h"
#include "MyMainWindow.h"
#include <QDesktopWidget>
#include <QDebug>

ModeInterface::ModeInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo

	mode_one->resize(240, 80);
	mode_one->move(300, 650);
	QPixmap p7 = QPixmap(":/ui/Resource/image/ui/modeone.png");
	mode_one->setIcon(p7);
	mode_one->setIconSize(QSize(240, 80));
	mode_one->setFlat(true);

	mode_two->resize(240, 80);
	mode_two->move(700, 650);
	QPixmap p8 = QPixmap(":/ui/Resource/image/ui/modetwo.png");
	mode_two->setIcon(p8);
	mode_two->setIconSize(QSize(240, 80));
	mode_two->setFlat(true);

	returnbtn_mode->resize(240, 80);
	returnbtn_mode->move(1000, 650);
	QPixmap p12 = QPixmap(":/ui/Resource/image/ui/returnback.png");
	returnbtn_mode->setIcon(p12);
	returnbtn_mode->setIconSize(QSize(240, 80));
	returnbtn_mode->setFlat(true);

	connect(mode_one, &QPushButton::clicked, [=]() {
		MyMainWindow* gamewindow = new MyMainWindow(1, local, this);
		gamewindow->show();
		});
	connect(mode_two, &QPushButton::clicked, [=]() {
		MyMainWindow* gamewindow = new MyMainWindow(2, local, this);
		});
	connect(returnbtn_mode, &QPushButton::clicked, this, &ModeInterface::ReturnBack);
}

void ModeInterface::ReturnBack() {
	StartInterface* intro = new StartInterface(local);
	intro->show();
	this->close();
}

ModeInterface::~ModeInterface()
{}
