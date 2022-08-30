#include "SetUp.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>

SetUp::SetUp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QDesktopWidget* desktop = QApplication::desktop();
	this->setFixedSize(600, 400);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"设置"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
	this->setWindowFlags(Qt::CustomizeWindowHint);
	this->move((parent->width() - this->width()) / 2, (parent->height() - this->height()) / 2);
	close->resize(240, 80);
	close->move(300, 50);
	QPixmap p12 = QPixmap(":/ui/Resource/image/ui/returnback.png");
	close->setIcon(p12);
	close->setIconSize(QSize(240, 80));
	close->setFlat(true);

	save->resize(240, 80);
	save->move(100, 300);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/return.png");
	save->setIcon(p15);
	save->setIconSize(QSize(240, 80));
	save->setFlat(true);

	back->resize(240, 80);
	back->move(300, 300);
	QPixmap p16 = QPixmap(":/ui/Resource/image/ui/return.png");
	back->setIcon(p15);
	back->setIconSize(QSize(240, 80));
	back->setFlat(true);

	load_one->resize(240, 80);
	load_one->move(200, 50);
	QPixmap p17 = QPixmap(":/ui/Resource/image/ui/return.png");
	load_one->setIcon(p15);
	load_one->setIconSize(QSize(240, 80));
	load_one->setFlat(true);

	load_two->resize(240, 80);
	load_two->move(200, 150);
	QPixmap p18 = QPixmap(":/ui/Resource/image/ui/return.png");
	load_two->setIcon(p15);
	load_two->setIconSize(QSize(240, 80));
	load_two->setFlat(true);

	load_three->resize(240, 80);
	load_three->move(200, 250);
	QPixmap p19 = QPixmap(":/ui/Resource/image/ui/return.png");
	load_three->setIcon(p15);
	load_three->setIconSize(QSize(240, 80));
	load_three->setFlat(true);

	connect(save, &QPushButton::clicked, this, &SetUp::Load);
	connect(load_one, &QPushButton::clicked, this, &SetUp::LoadOne);
	connect(load_two, &QPushButton::clicked, this, &SetUp::LoadTwo);
	connect(load_three, &QPushButton::clicked, this, &SetUp::LoadThree);

	remind->setGeometry(200, 100, 400, 50);
	remind->setText("自选");
	load_interface->hide();
	set_interface->show();
}

void SetUp::paintEvent(QPaintEvent* event) {
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/setbackground.png"));
	painter->end();
}

void SetUp::Load() {
	delete set_interface;
	load_interface->show();
	remind->setText("存档");
}

void SetUp::LoadOne() {

}

SetUp::~SetUp()
{}
