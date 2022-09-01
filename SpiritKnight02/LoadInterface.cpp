#include "LoadInterface.h"
#include "StartInterface.h"
#include "MyMainWindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

LoadInterface::LoadInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->local = local;
	QDesktopWidget w;
	int DeskWidth = 1280;
	int DeskHeight = 800;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
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
	connect(load_one, &QPushButton::clicked, this, &LoadInterface::LoadOne);
	connect(load_two, &QPushButton::clicked, this, &LoadInterface::LoadTwo);
	connect(load_three, &QPushButton::clicked, this, &LoadInterface::LoadThree);
}

void LoadInterface::ReturnBack() {
	StartInterface* load = new StartInterface(local);
	load->show();
	this->close();
}

void LoadInterface::paintEvent(QPaintEvent* event) {
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/modechoose.jpg"));
	painter->end();
}

void LoadInterface::LoadOne() {
	QSqlTableModel* model = new QSqlTableModel;
	QString user = local->GetUsername();
	model->setTable("gameload");
	model->setFilter(QString("username='%1' and load_num=1").arg(user));//查询存档
	model->select();
	QSqlRecord record = model->record(0);
	QString username = record.value("username").toString();
	int mode = record.value("mode").toInt();
	int hp = record.value("hp").toInt();
	int mp = record.value("mp").toInt();
	int exp = record.value("exp").toInt();
	int level = record.value("level").toInt();
	local = new Player(username, hp, mp, exp, level);
	MyMainWindow* w = new MyMainWindow(mode, local, record.value("map_choose").toInt());
	w->show();
	this->close();
}

void LoadInterface::LoadTwo() {
	QSqlTableModel* model = new QSqlTableModel;
	QString user = local->GetUsername();
	model->setTable("gameload");
	model->setFilter(QString("username='%1' and load_num=2").arg(user));//查询存档
	model->select();
	QSqlRecord record = model->record(0);
	QString username = record.value("username").toString();
	int mode = record.value("mode").toInt();
	int hp = record.value("hp").toInt();
	int mp = record.value("mp").toInt();
	int exp = record.value("exp").toInt();
	int level = record.value("level").toInt();
	local = new Player(username, hp, mp, exp, level);
	MyMainWindow* w = new MyMainWindow(mode, local, record.value("map_choose").toInt());
	w->show();
	this->close();
}

void LoadInterface::LoadThree() {
	QSqlTableModel* model = new QSqlTableModel;
	QString user = local->GetUsername();
	model->setTable("gameload");
	model->setFilter(QString("username='%1' and load_num=3").arg(user));//查询存档
	model->select();
	QSqlRecord record = model->record(0);
	QString username = record.value("username").toString();
	int mode = record.value("mode").toInt();
	int hp = record.value("hp").toInt();
	int mp = record.value("mp").toInt();
	int exp = record.value("exp").toInt();
	int level = record.value("level").toInt();
	local = new Player(username, hp, mp, exp, level);
	MyMainWindow* w = new MyMainWindow(mode, local, record.value("map_choose").toInt());
	w->show();
	this->close();
}

LoadInterface::~LoadInterface()
{}
