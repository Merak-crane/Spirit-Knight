#pragma once

#include <QWidget>
#include "ui_ModeInterface.h"
#include "Player.h"
#include <QPushButton>
#include <QPainter>

class ModeInterface : public QWidget
{
	Q_OBJECT

public:
	ModeInterface(Player* local, QWidget *parent = nullptr);
	~ModeInterface();
	void paintEvent(QPaintEvent* event);
	void ReturnBack();
private:
	Ui::ModeInterfaceClass ui;
	Player* local;
	QPushButton* mode_one = new QPushButton(this);
	QPushButton* mode_two = new QPushButton(this);
	QPushButton* returnbtn_mode = new QPushButton(this);
};
