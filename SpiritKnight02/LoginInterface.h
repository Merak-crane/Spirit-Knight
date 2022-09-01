#pragma once

#include <QWidget>
#include "Player.h"
#include "StartInterface.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTimer>
#pragma execution_character_set("utf-8")  
class LoginInterface : public QWidget
{
	Q_OBJECT

public:
	LoginInterface(Player* local, QWidget *parent = nullptr);
	~LoginInterface();
	void LoginConfirm();
	void LoginUpdate();
	void ReturnOrigin();
	void paintEvent(QPaintEvent* event);
private:
	Player* local;
	QLineEdit* username = new QLineEdit(this);
	QLineEdit* password = new QLineEdit(this);
	QPushButton* confirm = new QPushButton(this);
	QPushButton* returnbtn_login = new QPushButton(this);
	QLabel* username_verify_label2 = new QLabel(this);
	QLabel* password_verify_label2 = new QLabel(this);
	QTimer start_time;
};
