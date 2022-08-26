#pragma once
#pragma execution_character_set("utf-8")  
#include <QWidget>
#include <QPushButton>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QVideoWidget>
#include <QTimer>
#include <QLineEdit>


class Start : public QWidget
{
	Q_OBJECT

public:
	Start(QWidget *parent = nullptr);
	~Start();
	void paintEvent(QPaintEvent* Event);
    void Login();
    void Register();
    void ModeChoose();
    void OpenLoad();
    void OpenIntroduction();
    void ReturnBack();
    void Close();
    int kind;
    QWidget* login_interface = new QWidget(this);
    QWidget* register_interface = new QWidget(this);
    QWidget* introduction_interface = new QWidget(this);
    QWidget* load_interface = new QWidget(this);
    QWidget* start_interface = new QWidget(this);
    QWidget* mode_interface = new QWidget(this);
    QWidget* origin_interface = new QWidget(this);
    QLineEdit* username = new QLineEdit(login_interface);
    QLineEdit* password = new QLineEdit(login_interface);
    QLineEdit* username2 = new QLineEdit(register_interface);
    QLineEdit* email = new QLineEdit(register_interface);
    QLineEdit* password2 = new QLineEdit(register_interface);
    QLineEdit* password_confirm = new QLineEdit(register_interface);
    QPushButton* confirm2 = new QPushButton(register_interface);
    QPushButton* start = new QPushButton(start_interface);
    QPushButton* login = new QPushButton(origin_interface);
    QPushButton* register_ = new QPushButton(origin_interface);
    QPushButton* confirm = new QPushButton(login_interface);
    QPushButton* mode_one = new QPushButton(mode_interface);
    QPushButton* mode_two = new QPushButton(mode_interface);
    QPushButton* load_one = new QPushButton(load_interface);
    QPushButton* load_two = new QPushButton(load_interface);
    QPushButton* load_three = new QPushButton(load_interface);
    QPushButton* continued = new QPushButton(start_interface);
    QPushButton* introduction = new QPushButton(start_interface);
    QPushButton* exit = new QPushButton(start_interface);
    QPushButton* returnbtn = new QPushButton(mode_interface);
private:
    QMediaPlayer* qtaudioPlayer;
    QVideoWidget* m_videoW;
    QTimer start_time;
};
