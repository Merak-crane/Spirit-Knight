#pragma once
#pragma execution_character_set("utf-8")  
#include <QMainWindow>
#include "ui_SetUp.h"
#include <QPushButton>
#include <QLabel>

class SetUp : public QMainWindow
{
	Q_OBJECT

public:
	SetUp(QWidget *parent = nullptr);
	~SetUp();
	QLabel* remind = new QLabel(this);
	QWidget* load_interface = new QWidget(this);
	QPushButton* back = new QPushButton(this);
	QPushButton* save = new QPushButton(this);
	QPushButton* close = new QPushButton(this);
	QPushButton* load_one = new QPushButton(load_interface);
	QPushButton* load_two = new QPushButton(load_interface);
	QPushButton* load_three = new QPushButton(load_interface);
	void paintEvent(QPaintEvent* event);
	void Load();

private:
	Ui::SetUpClass ui;
};
