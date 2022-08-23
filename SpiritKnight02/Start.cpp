#include "Start.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QIcon>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QVideoWidget>

Start::Start(QWidget *parent)
	: QWidget(parent)
{
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
		// 布局界面
	QMediaPlayer qtaudioPlayer;
	QVideoWidget* m_videoW = new QVideoWidget(this);
	m_videoW = new QVideoWidget();
	QString path = QDir::currentPath();
	// 设置视频文件，并播放程序所在目录下的video.mp4
	qtaudioPlayer.setVideoOutput(m_videoW);
	qDebug() << path;
	qtaudioPlayer.setMedia(QUrl::fromLocalFile("./Resource/image/start_animation.mp4"));
	qDebug() << path;
	qtaudioPlayer.play();
	////将QVideoWidget 对象添加到布局
	//m_layout->addWidget(m_videoW);
	////设置页面布局
	//this->setLayout(m_layout);
	////设置媒体文件输出
	//m_player->setVideoOutput(m_videoW);
	////显示m_videoW
	//m_videoW->show();
	//播放视频
	//m_player->play();
	start->resize(240, 80);
	start->move(50, 500);
	QPixmap p1 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	start->setIcon(p1);
	start->setIconSize(QSize(240, 80));
	start->setFlat(true);
	continued->resize(240, 80);
	continued->move(300, 500);
	QPixmap p2 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	continued->setIcon(p2);
	continued->setIconSize(QSize(240, 80));
	continued->setFlat(true);
	help->resize(240, 80);
	help->move(50, 650);
	QPixmap p3 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	help->setIcon(p3);
	help->setIconSize(QSize(240, 80));
	help->setFlat(true);
	exit->resize(240, 80);
	exit->move(300, 650);
	QPixmap p4 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	exit->setIcon(p4);
	exit->setIconSize(QSize(240, 80));
	exit->setFlat(true);
	//connect(exit, &QPushButton::clicked, this, &QWidget::Close);
	//connect(start, &QPushButton::clicked, this, &Start::Modechoose);
	//connect(continued, &QPushButton::clicked, this, &Start::openload);
	//connect(returnbtn, &QPushButton::clicked, this, &Start::returnback);
	//connect(start, &QPushButton::clicked, this, &QWidget::close);
	//connect(load1btn, &QPushButton::clicked, this, &Start::load_1);
	//connect(load2btn, &QPushButton::clicked, this, &Start::load_2);
	//connect(load3btn, &QPushButton::clicked, this, &Start::load_3);
	//connect(help, &QPushButton::clicked, this, &Start::openhelp);
}

Start::~Start()
{}

void Start::paintEvent(QPaintEvent* Event) {
	QPainter painter1(this);
	painter1.drawPixmap(0,0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.png"));
}

//void Start::modechoose(){
//
//}
//
//void Start::close() {
//
//}