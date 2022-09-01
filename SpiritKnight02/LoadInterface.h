#pragma once

#include <QWidget>
#include "Player.h"
#include <QPushButton>
#include <QPainter>

class LoadInterface : public QWidget
{
	Q_OBJECT

public:
	LoadInterface(Player* local,QWidget *parent = nullptr);
	~LoadInterface();
	void paintEvent(QPaintEvent* event);
	void ReturnBack();
	void LoadOne();
	void LoadTwo();
	void LoadThree();
private:
	Player* local;
	QPushButton* load_one = new QPushButton(this);
	QPushButton* load_two = new QPushButton(this);
	QPushButton* load_three = new QPushButton(this);
	QPushButton* returnbtn_load = new QPushButton(this);
};
