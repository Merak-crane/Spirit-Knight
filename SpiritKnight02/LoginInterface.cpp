#include "LoginInterface.h"
#include "OriginInterface.h"
#include <QDesktopWidget>
#include <QDebug>

LoginInterface::LoginInterface(Player* local, QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo

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

	username->move(200, 600);
	password->move(200, 700);
	password->setEchoMode(QLineEdit::Password);
	username->setPlaceholderText("username");
	password->setPlaceholderText("password");
	username->setMaxLength(11);
	password->setMaxLength(15);

	confirm->resize(240, 80);
	confirm->move(1000, 650);
	QPixmap p14 = QPixmap(":/ui/Resource/image/ui/confirm.png");
	confirm->setIcon(p14);
	confirm->setIconSize(QSize(240, 80));
	confirm->setFlat(true);

	returnbtn_login->resize(240, 80);
	returnbtn_login->move(800, 650);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/return.png");
	returnbtn_login->setIcon(p15);
	returnbtn_login->setIconSize(QSize(240, 80));
	returnbtn_login->setFlat(true);
	connect(confirm, &QPushButton::clicked, this, &LoginInterface::LoginConfirm);
	connect(returnbtn_login, &QPushButton::clicked, this, &LoginInterface::ReturnOrigin);

	start_time.setInterval(10);
	start_time.start();
	connect(&start_time, &QTimer::timeout, [=]() {
			LoginUpdate();
		});
}

void LoginInterface::LoginUpdate() {
	int pos = 0;
	username->editingFinished();
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
			password_verify_label2->setText("密码格式正确");
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

void LoginInterface::LoginConfirm() {
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
			QMessageBox::information(this, "提示", "登录成功!");
			model->setFilter(QString("name='%1'").arg(user_name));
			model->select();
			QSqlRecord record = model->record(0);
			QString name = record.value("name").toString();
			local = new Player(record.value("name").toString(), record.value("email").toString(), record.value("power").toString()
				, record.value("level").toInt());
			this->close();
			StartInterface* login = new StartInterface(local);
			login->show();
		}
		else {
			QMessageBox::information(this, "提示", "密码错误，登录失败!");
			password->clear();
		}
	}
	else {//查询失败
		QMessageBox::information(this, "提示", "用户未注册!");
	}
	delete model;
}

void LoginInterface::ReturnOrigin() {
	OriginInterface* back = new OriginInterface;
	back->show();
	this->close();
}

void LoginInterface::paintEvent(QPaintEvent* event) {
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/login.png"));
	painter->end();
}

LoginInterface::~LoginInterface()
{}
