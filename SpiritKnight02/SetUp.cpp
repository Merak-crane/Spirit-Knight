#include "SetUp.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

SetUp::SetUp(Hero hero, Player* local, int mode, int mapchoose, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->parent = parent;
	this->mode = mode;
	this->mapchoose = mapchoose;
	this->hero = hero;
	this->local = local;
	QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");//添加驱动
	data_base.setHostName("175.178.64.219");  //设置主机地址
	data_base.setPort(3306);  //mysql设置端口
	data_base.setDatabaseName("gametest");  //设置数据库名称
	if (!data_base.open())//打开数据库
	{
		qDebug() << "connect failed";
		qDebug() << data_base.lastError();//.databaseText()  输出错误信息
	}
	else
		qDebug() << "success";
	data_base.close();//关闭数据库
	QDesktopWidget* desktop = QApplication::desktop();
	this->setFixedSize(600, 400);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
	this->setWindowFlags(Qt::CustomizeWindowHint);
	this->move((parent->width() - this->width()) / 2, (parent->height() - this->height()) / 2);
	close->resize(120, 40);
	close->move(450, 50);
	QPixmap p12 = QPixmap(":/ui/Resource/image/ui/close.png");
	close->setIcon(p12);
	close->setIconSize(QSize(120, 80));
	close->setFlat(true);

	save->resize(240, 80);
	save->move(100, 300);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/save.png");
	save->setIcon(p15);
	save->setIconSize(QSize(240, 80));
	save->setFlat(true);

	back->resize(240, 80);
	back->move(300, 300);
	QPixmap p16 = QPixmap(":/ui/Resource/image/ui/return.png");
	back->setIcon(p16);
	back->setIconSize(QSize(240, 80));
	back->setFlat(true);

	load_one->resize(240, 80);
	load_one->move(180, 100);
	QPixmap p17 = QPixmap(":/ui/Resource/image/ui/load1.png");
	load_one->setIcon(p17);
	load_one->setIconSize(QSize(240, 80));
	load_one->setFlat(true);

	load_two->resize(240, 80);
	load_two->move(180, 200);
	QPixmap p18 = QPixmap(":/ui/Resource/image/ui/load2.png");
	load_two->setIcon(p18);
	load_two->setIconSize(QSize(240, 80));
	load_two->setFlat(true);

	load_three->resize(240, 80);
	load_three->move(180, 300);
	QPixmap p19 = QPixmap(":/ui/Resource/image/ui/load3.png");
	load_three->setIcon(p19);
	load_three->setIconSize(QSize(240, 80));
	load_three->setFlat(true);

	connect(save, &QPushButton::clicked, this, &SetUp::Load);
	connect(load_one, &QPushButton::clicked, this, &SetUp::LoadOne);
	connect(load_two, &QPushButton::clicked, this, &SetUp::LoadTwo);
	connect(load_three, &QPushButton::clicked, this, &SetUp::LoadThree);
	connect(close, &QPushButton::clicked, this, &SetUp::Close);
	connect(back, &QPushButton::clicked, this, &SetUp::Back);

	remind->setGeometry(190, 50, 400, 50);
	remind->setText("Make your choice");
	remind->setObjectName("remind");
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
	remind->setText("Select archive location");
}

void SetUp::Close() {
	delete set_interface;
	delete this;
}

void SetUp::Back() {
	parent->close();

}

void SetUp::LoadOne() {
	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("gameload");//选择数据表
	QString cmd = QString("insert into gameload(username, load_num, mode, map_choose, hp, mp, exp, level)values ('%1',%2,%3,%4,%5,%6,%7,%8)")
		.arg(local->GetUsername()).arg(1).arg(mode).arg(mapchoose).arg(hero.GetHP()).arg(hero.GetMP()).arg(hero.GetExp()).arg(hero.GetLevel());
	QSqlQuery* query = new QSqlQuery;
	if (query->exec(cmd)) {
		QMessageBox::information(this, "information", "success!");
	}
	else {
		QMessageBox::information(this, "information", "Archiving failed! Please contact the administrator");
	}
	delete query;
}

void SetUp::LoadTwo() {
	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("gameload");//选择数据表
	QString cmd = QString("insert into gameload(username, load_num, mode, map_choose, hp, mp, exp, level)values ('%1',%2,%3,%4,%5,%6,%7,%8)")
		.arg(local->GetUsername()).arg(2).arg(mode).arg(mapchoose).arg(hero.GetHP()).arg(hero.GetMP()).arg(hero.GetExp()).arg(hero.GetLevel());
	QSqlQuery* query = new QSqlQuery;
	if (query->exec(cmd)) {
		QMessageBox::information(this, "information", "success!!");
	}
	else {
		QMessageBox::information(this, "information", "Archiving failed! Please contact the administrator");
	}
	delete query;
}

void SetUp::LoadThree() {
	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("gameload");//选择数据表
	QString cmd = QString("insert into gameload(username, load_num, mode, map_choose, hp, mp, exp, level)values ('%1',%2,%3,%4,%5,%6,%7,%8)")
		.arg(local->GetUsername()).arg(3).arg(mode).arg(mapchoose).arg(hero.GetHP()).arg(hero.GetMP()).arg(hero.GetExp()).arg(hero.GetLevel());
	QSqlQuery* query = new QSqlQuery;
	if (query->exec(cmd)) {
		QMessageBox::information(this, "提示", "存档成功!");
	}
	else {
		QMessageBox::information(this, "提示", "存档失败!请联系管理员");
	}
	delete query;
}


SetUp::~SetUp()
{}
