#pragma once

#pragma execution_character_set("utf-8")  
#include "ui_SetUp.h"
#include "Character.h"
#include "Player.h"
#include <QPushButton>
#include <QWidget>
#include <QLabel>

class SetUp : public QWidget
{
	Q_OBJECT

public:
	SetUp(Hero hero, Player* local, int mode, int mapchoose, QWidget *parent = nullptr);
	~SetUp();
	int mode;
	int mapchoose;
	Hero hero;
	Player* local;
	QLabel* remind = new QLabel(this);
	QWidget* parent;
	QWidget* load_interface = new QWidget(this);
	QWidget* set_interface = new QWidget(this);
	QPushButton* back = new QPushButton(set_interface);
	QPushButton* save = new QPushButton(set_interface);
	QPushButton* close = new QPushButton(set_interface);
	QPushButton* load_one = new QPushButton(load_interface);
	QPushButton* load_two = new QPushButton(load_interface);
	QPushButton* load_three = new QPushButton(load_interface);
	void paintEvent(QPaintEvent* event);
	void Load();
	void LoadOne();
	void LoadTwo();
	void LoadThree();

private:
	Ui::SetUpClass ui;
};
