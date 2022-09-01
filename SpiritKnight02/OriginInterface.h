#pragma once

#include <QWidget>
#include "LoginInterface.h"
#include "RegisterInterface.h"
#include <QPushButton>
#include <QPainter>

class OriginInterface : public QWidget
{
	Q_OBJECT

public:
	OriginInterface(QWidget *parent = nullptr);
	~OriginInterface();
	QPushButton* login = new QPushButton(this);
	QPushButton* register_ = new QPushButton(this);
	void paintEvent(QPaintEvent* event);
	void Login();
	void Register();
private:
	Player* local;
	LoginInterface* login_interface = new LoginInterface(local);
	RegisterInterface* register_interface = new RegisterInterface;
	QWidget* parent;
};
