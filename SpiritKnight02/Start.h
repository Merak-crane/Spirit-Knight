#pragma once

#include <QWidget>
#include <QPushButton>


class Start : public QWidget
{
	Q_OBJECT

public:
	Start(QWidget *parent = nullptr);
	~Start();
	void paintEvent(QPaintEvent* Event);
    QPushButton* start = new QPushButton(this);
    QPushButton* continued = new QPushButton(this);
    QPushButton* help = new QPushButton(this);
    QPushButton* exit = new QPushButton(this);
    QPushButton* returnbtn = new QPushButton(this);
    QPushButton* load1btn = new QPushButton(this);
    QPushButton* load2btn = new QPushButton(this);
    QPushButton* load3btn = new QPushButton(this);
private:
};
