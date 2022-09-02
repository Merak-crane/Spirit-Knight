#include "RegisterInterface.h"
#include "OriginInterface.h"
#include "Smtp.h"
#include <QDesktopWidget>
#include <QDebug>

RegisterInterface::RegisterInterface(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	register_kind = 0;
	QDesktopWidget w;
	int DeskWidth = 1280;
	int DeskHeight = 800;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle("Mega Man E");//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo

	identify_code_emit->resize(240, 80);
	identify_code_emit->move(600, 650);
	QPixmap p4 = QPixmap(":/ui/Resource/image/ui/identify.png");
	identify_code_emit->setIcon(p4);
	identify_code_emit->setIconSize(QSize(240, 80));
	identify_code_emit->setFlat(true);

	returnbtn_register->resize(240, 80);
	returnbtn_register->move(800, 650);
	QPixmap p15 = QPixmap(":/ui/Resource/image/ui/return.png");
	returnbtn_register->setIcon(p15);
	returnbtn_register->setIconSize(QSize(240, 80));
	returnbtn_register->setFlat(true);

	confirm2->resize(240, 80);
	confirm2->move(1000, 650);
	QPixmap p2 = QPixmap(":/ui/Resource/image/ui/confirm.png");
	confirm2->setIcon(p2);
	confirm2->setIconSize(QSize(240, 80));
	confirm2->setFlat(true);

	username2->move(300, 550);
	username2->setMaxLength(11);
	email->move(300, 600);
	email->setPlaceholderText("email");
	identify_code->move(300, 750);
	identify_code->setPlaceholderText("6位数字");

	password2->move(300, 650);
	password2->setMaxLength(15);
	password_confirm->move(300, 700);
	password_confirm->setEchoMode(QLineEdit::Password);
	password_confirm->setMaxLength(15);
	password2->setEchoMode(QLineEdit::Password);
	username2->setPlaceholderText("username");
	password2->setPlaceholderText("password");
	password_confirm->setPlaceholderText("password again");
	username_verify_label->setObjectName("infor");
	password_verify_label->setObjectName("infor");
	password_confirm_verify_label->setObjectName("infor");
	email_verify_label->setObjectName("infor");
	identify_verify_label->setObjectName("infor");

	connect(confirm2, &QPushButton::clicked, this, &RegisterInterface::RegisterConfirm);
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
	start_time.setInterval(100);
	start_time.start();
	connect(&start_time, &QTimer::timeout, [=]() {
		RegisterUpdate();
		});
	connect(returnbtn_register, &QPushButton::clicked, this, &RegisterInterface::ReturnOrigin);
}

void RegisterInterface::ReturnOrigin() {
	OriginInterface* back = new OriginInterface;
	back->show();
	this->close();
}

void RegisterInterface::RegisterUpdate() {
	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("gameuser");//选择数据表
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
			email_verify_label->setText("邮箱已注册！");
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
			model->setFilter(QString("username='%1'").arg(username_text));//设置查询过滤选项，此处查询用户名
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
		else if (username_text.length() < 3 && username_text.length() != 0) {
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
	else {
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

void RegisterInterface::RegisterConfirm() {
	if (register_kind == 2) {
		QString cmd = QString("insert into gameuser(username,password,email,level,exp,power) values ('%1','%2','%3','%4','%5','%6')")
			.arg(username2->text()).arg(password2->text()).arg(email->text()).arg(1).arg(0).arg("player");
		QSqlQuery* query = new QSqlQuery;

		if (query->exec(cmd)) {
			QMessageBox::information(this, "提示", "注册成功!");
			this->close();
			LoginInterface* login = new LoginInterface(local);
			login->show();
		}
		else {
			QMessageBox::information(this, "提示", "注册失败!请联系管理员");
		}
		delete query;
	}
	else {
		QMessageBox::critical(this, "无法进入下一阶段", "资料填写不当");
	}
}

void RegisterInterface::paintEvent(QPaintEvent* event) {
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/login.png"));
	painter->end();
}

RegisterInterface::~RegisterInterface()
{}
