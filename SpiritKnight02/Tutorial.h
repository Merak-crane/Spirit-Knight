#pragma once

#include <QWidget>
#include "ui_Tutorial.h"
#include "config.h"
#include "Character.h"
#include "Player.h"
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QMediaPlaylist>
#include <QMediaPlayer>
class Tutorial : public QWidget
{
	Q_OBJECT

public:
	Tutorial(Player* local, QWidget *parent = nullptr);
	~Tutorial();
	void paintEvent(QPaintEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void UpdateOne();
	void ReturnBack();
private:
	Ui::TutorialClass ui;
	int map_choose;
	int mode;
	Hero hero_one;
	ProfessorLong* Long;
	QLabel* hp;
	QLabel* mp;
	QLabel* exp;
	QLabel* tutorial;
	QLabel* user_information_label;
	Player* local;
	QTimer map_time;
	QPushButton* returnbtn_tutorial = new QPushButton(this);
	QMediaPlaylist* playlist = new QMediaPlaylist(this);
	QMediaPlayer* player = new QMediaPlayer(this);
};
