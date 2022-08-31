 #pragma once

#include <QWidget>
#include "ui_RegisterInterface.h"
#include "Player.h"
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

class RegisterInterface : public QWidget
{
	Q_OBJECT

public:
	RegisterInterface(QWidget *parent = nullptr);
	~RegisterInterface();
    void paintEvent(QPaintEvent* event);
    void ReturnOrigin();
    void RegisterUpdate();
    void RegisterConfirm();

private:
	Ui::RegisterInterfaceClass ui;
    int register_kind;
    QString identify;
    Player* local;
    QLineEdit* username2 = new QLineEdit(this);
    QLineEdit* email = new QLineEdit(this);
    QLineEdit* password2 = new QLineEdit(this);
    QLineEdit* password_confirm = new QLineEdit(this);
    QLineEdit* identify_code = new QLineEdit(this);
    QPushButton* identify_code_emit = new QPushButton(this);
    QPushButton* confirm2 = new QPushButton(this);
    QPushButton* returnbtn_register = new QPushButton(this);
    QLabel* username_verify_label = new QLabel(this);
    QLabel* password_verify_label = new QLabel(this);
    QLabel* password_confirm_verify_label = new QLabel(this);
    QLabel* email_verify_label = new QLabel(this);
    QLabel* identify_verify_label = new QLabel(this);
    QTimer start_time;
};
