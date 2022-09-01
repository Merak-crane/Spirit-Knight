#pragma once

#include <QWidget>
#include "ui_StartInterface.h"
#include "ModeInterface.h"
#include "LoadInterface.h"
#include "Player.h"
#include <QPushButton>
#include <QPainter>

class StartInterface : public QWidget
{
	Q_OBJECT

public:
	StartInterface(Player* local, QWidget *parent = nullptr);
	~StartInterface();
	void OpenLoad();
	void OpenIntroduction();
	void ModeChoose();
private:
	Ui::StartInterfaceClass ui;
	Player* local;
	QPushButton* start = new QPushButton(this);
	QPushButton* continued = new QPushButton(this);
	QPushButton* introduction = new QPushButton(this);
	QPushButton* exit = new QPushButton(this);
};