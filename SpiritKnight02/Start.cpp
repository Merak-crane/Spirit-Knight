#include "Start.h"
#include "Smtp.h"
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
#include <QSqlError>
#include <QRegExpValidator>
#include <QSqlTableModel>
Start::Start(QWidget *parent)
	: QWidget(parent)
{
	kind = 0;
	QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");//添加驱动
	data_base.setHostName("175.178.64.219");  //设置主机地址
	data_base.setPort(3306);  //mysql设置端口
	data_base.setDatabaseName("gametest");  //设置数据库名称
	if (!data_base.open())//打开数据库
	{
		qDebug() << "connect failed";
		qDebug() << data_base.lastError();//.databaseText()  输出错误信息
	}
	else
		qDebug() << "success";
	data_base.close();//关闭数据库
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

	identify_code_emit->resize(240, 80);
	identify_code_emit->move(600, 650);
	QPixmap p4= QPixmap(":/ui/Resource/image/ui/identify.png");
	identify_code_emit->setIcon(p4);
	identify_code_emit->setIconSize(QSize(240, 80));
	identify_code_emit->setFlat(true);

	continued->resize(240, 80);
	continued->move(300, 500);
	QPixmap p100 = QPixmap(":/ui/Resource/image/ui/continue.png");
	continued->setIcon(p100);
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
	load_one->move(200, 600);
	QPixmap p9 = QPixmap(":/ui/Resource/image/ui/load1.png");
	load_one->setIcon(p9);
	load_one->setIconSize(QSize(240, 80));
	load_one->setFlat(true);

	load_two->resize(240, 80);
	load_two->move(500, 600);
	QPixmap p10 = QPixmap(":/ui/Resource/image/ui/load2.png");
	load_two->setIcon(p10);
	load_two->setIconSize(QSize(240, 80));
	load_two->setFlat(true);

	load_three->resize(240, 80);
	load_three->move(800, 600);
	QPixmap p11 = QPixmap(":/ui/Resource/image/ui/load2.png");
	load_three->setIcon(p11);
	load_three->setIconSize(QSize(240, 80));
	load_three->setFlat(true);

	returnbtn->resize(240, 80);
	returnbtn->move(1000, 650);
	QPixmap p12 = QPixmap(":/ui/Resource/image/ui/returnback.png");
	returnbtn->setIcon(p12);
	returnbtn->setIconSize(QSize(240, 80));
	returnbtn->setFlat(true);

	returnbtn_login->resize(240, 80);
	returnbtn_login->move(800, 650);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/return.png");
	returnbtn_login->setIcon(p15);
	returnbtn_login->setIconSize(QSize(240, 80));
	returnbtn_login->setFlat(true);

	returnbtn_register->resize(240, 80);
	returnbtn_register->move(800, 650);
	returnbtn_register->setIcon(p15);
	returnbtn_register->setIconSize(QSize(240, 80));
	returnbtn_register->setFlat(true);

	returnbtn_load->resize(240, 80);
	returnbtn_load->move(800, 650);
	returnbtn_load->setIcon(p15);
	returnbtn_load->setIconSize(QSize(240, 80));
	returnbtn_load->setFlat(true);

	confirm->resize(240, 80);
	confirm->move(1000, 650);
	QPixmap p14 = QPixmap(":/ui/Resource/image/ui/confirm.png");
	confirm->setIcon(p14);
	confirm->setIconSize(QSize(240, 80));
	confirm->setFlat(true);

	confirm2->resize(240, 80);
	confirm2->move(1000, 650);
	confirm2->setIcon(p14);
	confirm2->setIconSize(QSize(240, 80));
	confirm2->setFlat(true);

	username->move(200, 600);
	password->move(200, 700);
	password->setEchoMode(QLineEdit::Password);	
    username->setPlaceholderText("username");
	password->setPlaceholderText("password");
	username->setMaxLength(11);
	password->setMaxLength(15);

	username2->move(200, 550);
	username2->setMaxLength(11);
	email->move(200, 600);
	email->setPlaceholderText("email");
	identify_code->move(200, 750);
	identify_code->setPlaceholderText("6位数字");

	password2->move(200, 650);
	password2->setMaxLength(15);
	password_confirm->move(200, 700);
	password_confirm->setEchoMode(QLineEdit::Password);
	password_confirm->setMaxLength(15);
	password2->setEchoMode(QLineEdit::Password);
	username2->setPlaceholderText("username");
	password2->setPlaceholderText("password");
	password_confirm->setPlaceholderText("password again");

	connect(login, &QPushButton::clicked, this, &Start::Login);
	connect(register_, &QPushButton::clicked, this, &Start::Register);
	connect(exit, &QPushButton::clicked, this, &QWidget::close);
	connect(start, &QPushButton::clicked, this, &Start::ModeChoose);
	connect(identify_code_emit, &QPushButton::clicked, [=] {
		if (register_kind == 1) {
			srand((int)time(0));
			identify.clear();
			int temp = 0;
			for (int i = 0; i < 6; i++)
			{
				temp = rand() % 10 + 0;
				identify += QString::number(temp, 10);
			}
			//int m = rand() % 100000 + 100000;
			//identify = QString::number(m, 10);
			QString emaill = email->text();
			QString content = QString("注册验证码：%1").arg(identify);
			QByteArray emailll = emaill.toUtf8();
			qDebug() << emailll << content;
			Smtp smtp("lazyreborn@163.com", "AIVUBLNWPFHPZEMC"); //邮箱和密码都要用自己的
			smtp.send(emailll, "Mega man E 账户注册验证码", content);
		}
		else
		{
			QMessageBox::information(this, "提示", "请完整填写表单!");
		}
	});
	connect(confirm, &QPushButton::clicked, this, &Start::LoginConfirm);
	connect(confirm2, &QPushButton::clicked, this, &Start::RegisterConfirm);
	connect(continued, &QPushButton::clicked, this, &Start::OpenLoad);
	connect(returnbtn, &QPushButton::clicked, this, &Start::ReturnBack);
	connect(returnbtn_login, &QPushButton::clicked, this, &Start::ReturnOrigin);
	connect(returnbtn_register, &QPushButton::clicked, this, &Start::ReturnOrigin);
	connect(returnbtn_load, &QPushButton::clicked, this, &Start::ReturnBack);
	//connect(load1btn, &QPushButton::clicked, this, &Start::load_1);
	//connect(load2btn, &QPushButton::clicked, this, &Start::load_2);
	//connect(load3btn, &QPushButton::clicked, this, &Start::load_3);
	connect(introduction, &QPushButton::clicked, this, &Start::OpenIntroduction);
	start_time.setInterval(1);
	start_time.start();
	connect(&start_time, &QTimer::timeout, [=]() {
		update();
		if (kind == 5) {
			RegisterUpdate();
		}
		else if (kind == 6) {
			LoginUpdate();
		}
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
	if (kind == 5 || kind == 6) {
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

void Start::ReturnOrigin() {
	kind = 0;
	login_interface->hide();
	register_interface->hide();
	origin_interface->show();
}

void Start::Login() {
	kind = 6;
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

void Start::LoginUpdate() {
	int pos = 0;
	QRegExp username_verify("^[0-9a-zA-Z_]+$");
	QRegExpValidator* username_validator = new QRegExpValidator(username_verify);
	username->setValidator(username_validator);
	QString username_text = username->text();
	int username_verify_num = 0;
	username_verify_label2->setGeometry(50, 600, 200, 30);
	if (username_text.length() < 11) {
		if (username_text.length() == 0)
		{
			username_verify_label2->setText("请输入用户名");
		}
		else if (username_text.length() >= 3 && username_validator->validate(username_text, pos) == QValidator::Acceptable)
		{
			username_verify_label2->setText("用户名输入正确");
			username_verify_num = 1;
		}
		else if (username_text.length() < 3 && username_text.length() != 0) {
			username_verify_label2->setText("至少3位哈"); 
		}
	}
	else {
		username_verify_label2->setText("最多11位");
	}
	QRegExp password_verify("^[0-9a-zA-Z_]+$");
	QRegExpValidator* password_validator = new QRegExpValidator(username_verify);
	password->setValidator(password_validator);
	QString password_text = password->text();
	int password_verify_num = 0;
	password_verify_label2->setGeometry(50, 700, 200, 30);
	if (password_text.length() <= 15) {
		if (password_text.length() == 0)
		{
			password_verify_label2->setText("请输入密码");
		}
		else if (password_text.length() < 8 && password_text.length() != 0) {
			password_verify_label2->setText("至少8位哈");
		}
		else if (password_text.length() >= 8 && password_validator->validate(password_text, pos) == QValidator::Acceptable)
		{
			password_verify_label->setText("密码格式正确");
			password_verify_num = 1;
		}
		else {
			password_verify_label2->setText("英文数字下划线");
		}
	}
	else {
		password_verify_label2->setText("最多15位");
	}
}

void Start::LoginConfirm(){
	QString user_name = username->text();
	QString pass_word = password->text();

	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("test01");
	model->setFilter(QString("name='%1'").arg(user_name));//查询用户名
	model->select();

	int row = model->rowCount();
	if (row > 0) {//查询成功
		row = 0;
		model->setFilter(QString("name='%1' and password='%2'").arg(user_name).arg(pass_word));//查询用户与密码
		model->select();
		row = model->rowCount();
		if (row > 0) {//查询成功
			QMessageBox::information(this,"提示","登录成功!");
			load_interface->hide();
			login_interface->hide();
			start_interface->hide();
			mode_interface->hide();
			kind = 4;
			start_interface->show();
		}
		else {
		   QMessageBox::information(this,"提示","密码错误，登录失败!");
		   password->clear();
		}
	}
	else {//查询失败
	   QMessageBox::information(this,"提示","用户未注册!");
	}
	delete model;
}

void Start::RegisterUpdate() {
	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("test01");//选择数据表
	int pos = 0;

	QRegExp email_verify("[a-zA-Z0-9-_]+@[a-zA-Z0-9_]+\\.[a-zA-Z]+");
	QRegExpValidator* email_validator = new QRegExpValidator(email_verify);
	email->setValidator(email_validator);
	QString emaill = email->text();
	email_verify_label->setGeometry(50, 600, 200, 30);
	int email_verify_num = 0;
	if (email_validator->validate(emaill, pos) != QValidator::Acceptable)
	{
		if (emaill.length() < 8) {
			email_verify_label->setText("请输入邮箱");
		}
		else
		{
			email_verify_label->setText("邮箱格式不正确");
		}
	}
	else {
		model->setFilter(QString("email='%1'").arg(emaill));//设置查询过滤选项，此处查询用户名
		model->select();//获取查询数据
		int row_email = model->rowCount();
		if (row_email > 0) {//查询到用户名已在数据库中
			email_verify_label->setText( "邮箱已注册！");
		}
		else {
			email_verify_label->setText("邮箱未被注册");
			email_verify_num = 1;
		}
	}

	QRegExp username_verify("^[0-9a-zA-Z_]+$");
	QRegExpValidator* username_validator = new QRegExpValidator(username_verify);
	username2->setValidator(username_validator);
	QString username_text = username2->text();
	int username_verify_num = 0;
	username_verify_label->setGeometry(50, 550, 200, 30);
	if (username_text.length() < 11) {
		if (username_text.length() == 0)
		{
			username_verify_label->setText("请输入用户名");
		}
		else if (username_text.length() >= 3 && username_validator->validate(username_text, pos) == QValidator::Acceptable)
		{
			model->setFilter(QString("name='%1'").arg(username_text));//设置查询过滤选项，此处查询用户名
			model->select();//获取查询数据
			int row_username = model->rowCount();
			if (row_username > 0) {//查询到用户名已在数据库中
				username_verify_label->setText("用户名已注册！");
			}
			else {
				username_verify_label->setText("用户名未被注册");
				username_verify_num = 1;
			}
		}
		else if (username_text.length() < 3 && username_text.length() != 0){
			username_verify_label->setText("至少3位哈");
		}
	}
	else {
		username_verify_label->setText("最多11位");
	}

	QRegExp password_verify("^[0-9a-zA-Z_]+$");
	QRegExpValidator* password_validator = new QRegExpValidator(username_verify);
	password2->setValidator(password_validator);
	QString password_text = password2->text();
	int password_verify_num = 0;
	password_verify_label->setGeometry(50, 650, 200, 30);
	if (password_text.length() <= 15) {
		if (password_text.length() == 0)
		{
			password_verify_label->setText("请输入密码");
		}
		else if (password_text.length() < 8 && password_text.length() != 0) {
			password_verify_label->setText("至少8位哈");
		}
		else if (password_text.length() >= 8 && password_validator->validate(password_text, pos) == QValidator::Acceptable)
		{
			password_verify_label->setText("密码格式正确");
			password_verify_num = 1;
		}
		else {
			password_verify_label->setText("英文数字下划线");
		}
	}
	else {
		password_verify_label->setText("最多15位");
	}
	password_confirm_verify_label->setGeometry(50, 700, 200, 30);
	int password_confirm_verify_num = 0;
	QString password_confirm_text = password_confirm->text();
	if (password_confirm_text.length() >= 8 && password_confirm_text == password_text) {
		password_confirm_verify_label->setText("两次输入密码相同");
		password_confirm_verify_num = 1;
	}
	else{
		password_confirm_verify_label->setText("请再次输入密码");
	}
	identify_verify_label->setGeometry(50, 750, 200, 30);
	int identify_verify_num = 0;
	QString identify_confirm_text = identify_code->text();
	if (identify_confirm_text.length() == 6 && identify == identify_confirm_text) {
		identify_verify_label->setText("输入正确");
		identify_verify_num = 1;
	}
	else if (identify_confirm_text.length() == 6) {
		identify_verify_label->setText("输入错误");
	}
	else {
		identify_verify_label->setText("请输入验证码");
	}
	if (password_confirm_verify_num == 1 && username_verify_num == 1 &&
		email_verify_num == 1 && password_verify_num == 1 && identify_verify_num != 1) {
		register_kind = 1;
	}
	else if (password_confirm_verify_num == 1 && username_verify_num == 1 &&
		email_verify_num == 1 && password_verify_num == 1 && identify_verify_num == 1) {
		register_kind = 2;
	}
	else {
		register_kind = 0;
	}
	delete model;
}

void Start::RegisterConfirm(){
 	if (register_kind == 2) {
		QString cmd = QString("insert into test01 values ('%1','%2','%3','%4','%5','%6')")
			.arg(3).arg(username2->text()).arg(password2->text()).arg(1).arg("player").arg(email->text());
		QSqlQuery* query = new QSqlQuery;

		if (query->exec(cmd)) {
			QMessageBox::information(this, "提示", "注册成功!");
			load_interface->hide();
			login_interface->hide();
			register_interface->hide();
			start_interface->hide();
			mode_interface->hide();
			kind = 4;
			start_interface->show();
		}
		else {
			QMessageBox::information(this, "提示", "注册失败!请联系管理员");
		}
		delete query;
	}
	else {
	QMessageBox::critical(register_interface, "无法进入下一阶段", "资料填写不当");
	}
}