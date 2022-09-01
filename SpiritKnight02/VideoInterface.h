#pragma once

#include <QWidget>
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
	QMediaPlayer* qtaudioPlayer;
	QVideoWidget* m_videoW;
};
