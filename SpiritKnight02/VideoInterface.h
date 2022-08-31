#pragma once

#include <QWidget>
#include "ui_VideoInterface.h"
#include "OriginInterface.h"
#include <QDesktopWidget>
#include <QIcon>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QVideoWidget>

class VideoInterface : public QWidget
{
	Q_OBJECT

public:
	VideoInterface(QWidget *parent = nullptr);
	~VideoInterface();

private:
	Ui::VideoInterfaceClass ui;
	QMediaPlayer* qtaudioPlayer;
	QVideoWidget* m_videoW;
	OriginInterface* origin_interface = new OriginInterface(this);
};
