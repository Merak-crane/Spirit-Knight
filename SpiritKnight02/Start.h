#pragma once

#include <QWidget>
#include <QPushButton>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QVideoWidget>
#include <QTimer>



class Start : public QWidget
{
	Q_OBJECT

public:
	Start(QWidget *parent = nullptr);
	~Start();
	void paintEvent(QPaintEvent* Event);
    void ModeChoose();
    void OpenLoad();
    void OpenIntroduction();
    void Close();
    int kind;
    QPushButton* start = new QPushButton(this);
    QPushButton* mode_one = new QPushButton(this);
    QPushButton* continued = new QPushButton(this);
    QPushButton* introduction = new QPushButton(this);
    QPushButton* exit = new QPushButton(this);
    QPushButton* returnbtn = new QPushButton(this);
    QPushButton* load1btn = new QPushButton(this);
    QPushButton* load2btn = new QPushButton(this);
    QPushButton* load3btn = new QPushButton(this);
private:
    QMediaPlayer* qtaudioPlayer;
    QVideoWidget* m_videoW;
    QTimer start_time;
};
