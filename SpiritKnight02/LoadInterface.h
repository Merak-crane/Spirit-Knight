#pragma once

#include <QWidget>
#include "ui_LoadInterface.h"
#include "Player.h"
#include <QPushButton>
#include <QPainter>

class LoadInterface : public QWidget
{
	Q_OBJECT

public:
	LoadInterface(Player* local,QWidget *parent = nullptr);
	~LoadInterface();
	void ReturnBack();
private:
	Ui::LoadInterfaceClass ui;
	Player* local;
	QPushButton* load_one = new QPushButton(this);
	QPushButton* load_two = new QPushButton(this);
	QPushButton* load_three = new QPushButton(this);
	QPushButton* returnbtn_load = new QPushButton(this);
};
