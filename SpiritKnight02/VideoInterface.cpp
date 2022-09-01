#include "VideoInterface.h"

VideoInterface::VideoInterface(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	QDesktopWidget w;
	int DeskWidth = 1280;
	int DeskHeight = 800;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle("Mega Man E");//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo
	qtaudioPlayer = new QMediaPlayer;
	m_videoW = new QVideoWidget(this);
	m_videoW->resize(1280, 800);
	QString path = QDir::currentPath();
	// ������Ƶ�ļ��������ų�������Ŀ¼�µ�video.mp4
	qtaudioPlayer->setVideoOutput(m_videoW);
	qtaudioPlayer->setVolume(40);
	m_videoW->setAspectRatioMode(Qt::IgnoreAspectRatio);
	m_videoW->show();
	qtaudioPlayer->setMedia(QUrl::fromLocalFile("./Resource/image/start_animation.mp4"));
	qtaudioPlayer->play();
	connect(qtaudioPlayer, &QMediaPlayer::mediaStatusChanged, [=]() {
		if (qtaudioPlayer->mediaStatus() == 7) {
			m_videoW->close();
			OriginInterface* mode = new OriginInterface;
			mode->show();
			this->close();
		}
		});
}

VideoInterface::~VideoInterface()
{}
