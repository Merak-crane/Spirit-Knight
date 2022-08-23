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
	int DeskHeight = w.height() / 2;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle(QString::fromUtf16(u"Ӣ����ʿ"));//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo
		// ���ֽ���
	QMediaPlayer qtaudioPlayer;
	QVideoWidget* m_videoW = new QVideoWidget(this);
	m_videoW = new QVideoWidget();
	QString path = QDir::currentPath();
	// ������Ƶ�ļ��������ų�������Ŀ¼�µ�video.mp4
	qtaudioPlayer.setVideoOutput(m_videoW);
	qDebug() << path;
	qtaudioPlayer.setMedia(QUrl::fromLocalFile("./Resource/image/start_animation.mp4"));
	qDebug() << path;
	qtaudioPlayer.play();
	////��QVideoWidget ������ӵ�����
	//m_layout->addWidget(m_videoW);
	////����ҳ�沼��
	//this->setLayout(m_layout);
	////����ý���ļ����
	//m_player->setVideoOutput(m_videoW);
	////��ʾm_videoW
	//m_videoW->show();
	//������Ƶ
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