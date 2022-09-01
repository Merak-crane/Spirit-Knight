#include "VideoInterface.h"

VideoInterface::VideoInterface(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	QDesktopWidget w;
	int DeskWidth = 1280;
	int DeskHeight = 800;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
	qtaudioPlayer = new QMediaPlayer;
	m_videoW = new QVideoWidget(this);
	m_videoW->resize(1280, 800);
	QString path = QDir::currentPath();
	// 设置视频文件，并播放程序所在目录下的video.mp4
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
