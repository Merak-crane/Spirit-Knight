#include "Start.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QIcon>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QVideoWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegExpValidator>
Start::Start(QWidget *parent)
	: QWidget(parent)
{
	kind = 0;
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
		// 布局界面
	qtaudioPlayer = new QMediaPlayer;
	m_videoW = new QVideoWidget(this);
	m_videoW->resize(1280, 800);
	QString path = QDir::currentPath();
	// 设置视频文件，并播放程序所在目录下的video.mp4
	qtaudioPlayer->setVideoOutput(m_videoW);
	qtaudioPlayer->setVolume(40);
	m_videoW->setAspectRatioMode(Qt::IgnoreAspectRatio);
	m_videoW->show();
	qDebug() << path;
	qtaudioPlayer->setMedia(QUrl::fromLocalFile("./Resource/image/start_animation.mp4"));
	qDebug() << path;
	qtaudioPlayer->play();
	connect(qtaudioPlayer, &QMediaPlayer::mediaStatusChanged, [=]() {
		if (qtaudioPlayer->mediaStatus() == 7 ) {
			m_videoW->close();
			origin_interface->show();
		}
		});

	login_interface->resize(1280, 800);
	login_interface->hide();
	register_interface->resize(1280, 800);
	register_interface->hide();
	load_interface->resize(1280, 800);
	load_interface->hide();
	start_interface->resize(1280, 800);
	start_interface->hide();
	introduction_interface->resize(1280, 800);
	introduction_interface->hide();
	mode_interface->resize(1280, 800);
	mode_interface->hide();
	origin_interface->resize(1280, 800);
	origin_interface->hide();

	start->resize(240, 80);
	start->move(50,500);
	QPixmap p1 = QPixmap(":/ui/Resource/image/ui/start.png");
	start->setIcon(p1);
	start->setIconSize(QSize(240, 80));
	start->setFlat(true);

	login->resize(240, 80);
	login->move(300, 650);
	QPixmap p2 = QPixmap(":/ui/Resource/image/ui/login.png");
	login->setIcon(p2);
	login->setIconSize(QSize(240, 80));
	login->setFlat(true);

	register_->resize(240, 80);
	register_->move(700, 650);
	QPixmap p3 = QPixmap(":/ui/Resource/image/ui/register.png");
	register_->setIcon(p3);
	register_->setIconSize(QSize(240, 80));
	register_->setFlat(true);

	continued->resize(240, 80);
	continued->move(300, 500);
	QPixmap p4 = QPixmap(":/ui/Resource/image/ui/continue.png");
	continued->setIcon(p4);
	continued->setIconSize(QSize(240, 80));
	continued->setFlat(true);

	introduction->resize(240, 80);
	introduction->move(50, 650);
	QPixmap p5 = QPixmap(":/ui/Resource/image/ui/introduction.png");
	introduction->setIcon(p5);
	introduction->setIconSize(QSize(240, 80));
	introduction->setFlat(true);

	exit->resize(240, 80);
	exit->move(300, 650);
	QPixmap p6 = QPixmap(":/ui/Resource/image/ui/exit.png");
	exit->setIcon(p6);
	exit->setIconSize(QSize(240, 80));
	exit->setFlat(true);

	mode_one->resize(240, 80);
	mode_one->move(300, 650);
	QPixmap p7 = QPixmap(":/ui/Resource/image/ui/modeone.png");
	mode_one->setIcon(p7);
	mode_one->setIconSize(QSize(240, 80));
	mode_one->setFlat(true);

	mode_two->resize(240, 80);
	mode_two->move(700, 650);
	QPixmap p8 = QPixmap(":/ui/Resource/image/ui/modetwo.png");
	mode_two->setIcon(p8);
	mode_two->setIconSize(QSize(240, 80));
	mode_two->setFlat(true);

	load_one->resize(240, 80);
	load_one->move(400, 600);
	QPixmap p9 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	load_one->setIcon(p4);
	load_one->setIconSize(QSize(240, 80));
	load_one->setFlat(true);

	load_two->resize(240, 80);
	load_two->move(600, 600);
	QPixmap p10 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	load_two->setIcon(p4);
	load_two->setIconSize(QSize(240, 80));
	load_two->setFlat(true);

	load_three->resize(240, 80);
	load_three->move(800, 600);
	QPixmap p11 = QPixmap(":/icon/Resource/icon/htmlogo.png");
	load_three->setIcon(p4);
	load_three->setIconSize(QSize(240, 80));
	load_three->setFlat(true);

	returnbtn->resize(240, 80);
	returnbtn->move(1000, 650);
	QPixmap p12 = QPixmap(":/ui/Resource/image/ui/returnback.png");
	returnbtn->setIcon(p12);
	returnbtn->setIconSize(QSize(240, 80));
	returnbtn->setFlat(true);

	confirm->resize(240, 80);
	confirm->move(1000, 650);
	QPixmap p13= QPixmap(":/ui/Resource/image/ui/confirm.png");
	confirm->setIcon(p13);
	confirm->setIconSize(QSize(240, 80));
	confirm->setFlat(true);

	confirm2->resize(240, 80);
	confirm2->move(1000, 650);
	QPixmap p14 = QPixmap(":/ui/Resource/image/ui/confirm.png");
	confirm2->setIcon(p14);
	confirm2->setIconSize(QSize(240, 80));
	confirm2->setFlat(true);

	username->move(200, 600);
	password->move(200, 700);
	password->setEchoMode(QLineEdit::Password);	
    username->setPlaceholderText("username");
	password->setPlaceholderText("password");

	username2->move(200, 550);
	email->move(200, 600);
	password2->move(200, 650);
	password_confirm->move(200, 700);
	password_confirm->setEchoMode(QLineEdit::Password);
	password2->setEchoMode(QLineEdit::Password);
	username2->setPlaceholderText("username");
	password2->setPlaceholderText("password");
	email->setPlaceholderText("email");
	password_confirm->setPlaceholderText("password again");

	connect(login, &QPushButton::clicked, this, &Start::Login);
	connect(register_, &QPushButton::clicked, this, &Start::Register);
	connect(exit, &QPushButton::clicked, this, &QWidget::close);
	connect(start, &QPushButton::clicked, this, &Start::ModeChoose);
	connect(confirm, &QPushButton::clicked, [=] {
		QString user_name = username->text();
		QString pass_word = password->text();
		load_interface->hide();
		login_interface->hide();
		start_interface->hide();
		mode_interface->hide();
		qDebug() << user_name << pass_word;
		kind = 4;
		start_interface->show();
	});
	connect(confirm2, &QPushButton::clicked, [=] {
		QString user_name2 = username2->text();
		QString pass_word2 = password2->text();
		QString emaill= email->text();
		QString pass_word_confirm = password_confirm->text();
		QRegExp email_verify("[a-zA-Z0-9-_]+@[a-zA-Z0-9_]+\\.[a-zA-Z]+");
		QRegExpValidator* Email_Validator = new QRegExpValidator(email_verify, this);
		email->setValidator(Email_Validator);
		bool isNumber = email_verify.exactMatch(emaill);
		if (!isNumber) {
			QMessageBox::critical(this, "错误", "请填写规范的邮箱格式");
		}
		else {
			load_interface->hide();
			login_interface->hide();
			register_interface->hide();
			start_interface->hide();
			mode_interface->hide();
			qDebug() << user_name2 << pass_word2 << emaill;
			kind = 4;
			start_interface->show();
		}
		});
	connect(continued, &QPushButton::clicked, this, &Start::OpenLoad);
	connect(returnbtn, &QPushButton::clicked, this, &Start::ReturnBack);
	//connect(load1btn, &QPushButton::clicked, this, &Start::load_1);
	//connect(load2btn, &QPushButton::clicked, this, &Start::load_2);
	//connect(load3btn, &QPushButton::clicked, this, &Start::load_3);
	connect(introduction, &QPushButton::clicked, this, &Start::OpenIntroduction);
	start_time.setInterval(1);
	start_time.start();
	connect(&start_time, &QTimer::timeout, [=]() {
		update();
	});
}

Start::~Start()
{}

void Start::paintEvent(QPaintEvent* Event) {
	QPainter painter1(this);
	if (kind == 0) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.png"));
	}
	if (kind == 1) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background2.jpg"));
	}
	if (kind == 2) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/modechoose.jpg"));
	}
	if (kind == 4) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.jpeg"));
	}
	if (kind == 5) {
		painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/login.png"));
	}
}

void Start::ModeChoose(){
	kind = 1;
	origin_interface->hide();
	load_interface->hide();
	introduction_interface->hide();
	login_interface->hide();
	start_interface->hide();
	mode_interface->show();
}

void Start::OpenLoad() {
	kind = 2;
	origin_interface->hide();
	introduction_interface->hide();
	login_interface->hide();
	start_interface->hide();
	mode_interface->hide();
	load_interface->show();
}

void Start::OpenIntroduction() {
	kind = 4;
	origin_interface->hide();
	load_interface->hide();
	login_interface->hide();
	start_interface->hide();
	mode_interface->hide();
	introduction_interface->show();
}

void Start::ReturnBack() {
	kind = 4;
	origin_interface->hide();
	load_interface->hide();
	login_interface->hide();
	start_interface->hide();
	mode_interface->hide();
	start_interface->show();
}

void Start::Login() {
	kind = 5;
	origin_interface->hide();
	load_interface->hide();
	introduction_interface->hide();
	start_interface->hide();
	mode_interface->hide();
	login_interface->show();
}

void Start::Register() {
	kind = 5;
	origin_interface->hide();
	register_interface->show();
}