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
	kind = 0;
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle(QString::fromUtf16(u"Ӣ����ʿ"));//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo
		// ���ֽ���
	qtaudioPlayer = new QMediaPlayer;
	m_videoW = new QVideoWidget(this);
	m_videoW->resize(1280, 800);
	QString path = QDir::currentPath();
	// ������Ƶ�ļ��������ų�������Ŀ¼�µ�video.mp4
	qtaudioPlayer->setVideoOutput(m_videoW);
	m_videoW->setAspectRatioMode(Qt::IgnoreAspectRatio);
	m_videoW->show();
	qDebug() << path;
	qtaudioPlayer->setMedia(QUrl::fromLocalFile("./Resource/image/start_animation.mp4"));
	qDebug() << path;
	qtaudioPlayer->play();
	connect(qtaudioPlayer, &QMediaPlayer::mediaStatusChanged, [=]() {
		if (qtaudioPlayer->mediaStatus() == 7 ) {
			m_videoW->close();
		}
		});
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
	introduction->resize(240, 80);
	introduction->move(50, 650);
	QPixmap p3 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	introduction->setIcon(p3);
	introduction->setIconSize(QSize(240, 80));
	introduction->setFlat(true);
	exit->resize(240, 80);
	exit->move(300, 650);
	QPixmap p4 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	exit->setIcon(p4);
	exit->setIconSize(QSize(240, 80));
	exit->setFlat(true);
	mode_one->resize(240, 80);
	mode_one->move(300, 650);
	QPixmap p5 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	mode_one->setIcon(p4);
	mode_one->setIconSize(QSize(240, 80));
	mode_one->setFlat(true);
	connect(exit, &QPushButton::clicked, this, &QWidget::close);
	connect(start, &QPushButton::clicked, this, &Start::ModeChoose);
	connect(continued, &QPushButton::clicked, this, &Start::OpenLoad);
	//connect(returnbtn, &QPushButton::clicked, this, &Start::returnback);
	//connect(start, &QPushButton::clicked, this, &QWidget::close);
	//connect(load1btn, &QPushButton::clicked, this, &Start::load_1);
	//connect(load2btn, &QPushButton::clicked, this, &Start::load_2);
	//connect(load3btn, &QPushButton::clicked, this, &Start::load_3);
	connect(introduction, &QPushButton::clicked, this, &Start::OpenIntroduction);
	start_time.setInterval(1);
	start_time.start();
	connect(&start_time, &QTimer::timeout, [=]() {
		update();
	});
}

Start::~Start()
{}

void Start::paintEvent(QPaintEvent* Event) {
	QPainter painter1(this);
	if (kind == 0) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.png"));
	}
	if (kind == 1) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background2.jpg"));
	}
	if (kind == 2) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/modechoose.jpg"));
	}
	if (kind == 4) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.jpeg"));
	}
}

void Start::ModeChoose(){
	kind = 1;
}

void Start::OpenLoad() {
	kind = 2;
}

void Start::OpenIntroduction() {
	kind = 4;
}
//void Start::close() {
//
//}