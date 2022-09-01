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
	int DeskHeight = w.height() / 2;//��ȡ�豸�ķֱ���
	this->setFixedSize(DeskWidth, DeskHeight);//���ô��ڴ�С
	this->setWindowTitle("Mega Man E");//���ô��ڱ���
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//���ô���logo

	QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");//�������
	data_base.setHostName("175.178.64.219");  //����������ַ
	data_base.setPort(3306);  //mysql���ö˿�
	data_base.setDatabaseName("gametest");  //�������ݿ�����
	if (!data_base.open())//�����ݿ�
	{
		qDebug() << "connect failed";
		qDebug() << data_base.lastError();//.databaseText()  ���������Ϣ
	}
	else
		qDebug() << "success";
	data_base.close();//�ر����ݿ�

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
			username_verify_label2->setText("�������û���");
		}
		else if (username_text.length() >= 3 && username_validator->validate(username_text, pos) == QValidator::Acceptable)
		{
			username_verify_label2->setText("�û���������ȷ");
			username_verify_num = 1;
		}
		else if (username_text.length() < 3 && username_text.length() != 0) {
			username_verify_label2->setText("����3λ��");
		}
	}
	else {
		username_verify_label2->setText("���11λ");
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
			password_verify_label2->setText("����������");
		}
		else if (password_text.length() < 8 && password_text.length() != 0) {
			password_verify_label2->setText("����8λ��");
		}
		else if (password_text.length() >= 8 && password_validator->validate(password_text, pos) == QValidator::Acceptable)
		{
			password_verify_label2->setText("�����ʽ��ȷ");
			password_verify_num = 1;
		}
		else {
			password_verify_label2->setText("Ӣ�������»���");
		}
	}
	else {
		password_verify_label2->setText("���15λ");
	}
}

void LoginInterface::LoginConfirm() {
	QString user_name = username->text();
	QString pass_word = password->text();

	QSqlTableModel* model = new QSqlTableModel;
	model->setTable("test01");
	model->setFilter(QString("name='%1'").arg(user_name));//��ѯ�û���
	model->select();

	int row = model->rowCount();
	if (row > 0) {//��ѯ�ɹ�
		row = 0;
		model->setFilter(QString("name='%1' and password='%2'").arg(user_name).arg(pass_word));//��ѯ�û�������
		model->select();
		row = model->rowCount();
		if (row > 0) {//��ѯ�ɹ�
			QMessageBox::information(this, "��ʾ", "��¼�ɹ�!");
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
			QMessageBox::information(this, "��ʾ", "������󣬵�¼ʧ��!");
			password->clear();
		}
	}
	else {//��ѯʧ��
		QMessageBox::information(this, "��ʾ", "�û�δע��!");
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
