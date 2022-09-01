#include "OriginInterface.h"
#include <QDesktopWidget>
#include <QDebug>

OriginInterface::OriginInterface(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->parent = parent;
	QDesktopWidget w;
	int DeskWidth = w.width() / 2;
	int DeskHeight = w.height() / 2;//获取设备的分辨率
	this->setFixedSize(DeskWidth, DeskHeight);//设置窗口大小
	this->setWindowTitle(QString::fromUtf16(u"英灵骑士"));//设置窗口标题
	this->setWindowIcon(QIcon(":/icon/Resource/icon/htmlogo.png"));//设置窗口logo
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
	connect(login, &QPushButton::clicked, this, &OriginInterface::Login);
	connect(register_, &QPushButton::clicked, this, &OriginInterface::Register);
}

void OriginInterface::paintEvent(QPaintEvent* event){
	QPainter* painter = new QPainter(this);
	painter->drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Resource/image/background/background.png"));
	painter->end();
}

void OriginInterface::Login() {
	login_interface->show();
	if (parent != nullptr) {
		parent->close();
	}
	else {
		this->close();
	}
}

void OriginInterface::Register() {
	register_interface->show();
	if (parent != nullptr) {
		parent->close();
	}
	else {
		this->close();
	}
}

OriginInterface::~OriginInterface()
{}
