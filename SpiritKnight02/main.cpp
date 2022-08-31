
#include "Start.h"
#include "VideoInterface.h"
#include "OriginInterface.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>
#include <QLinearGradient>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFile file(":/css/Resource/stylesheet.css");
	if (file.open(QFile::ReadOnly))
	{
		qApp->setStyleSheet(file.readAll());
	}
	else {
		QMessageBox::about(NULL, "Test", "Open File Failed");
		//file.close();
	}
	//Start s;
	//s.show();
	//Player* o = new Player("222", "sss", "ss", 100);
	//MyMainWindow w(3,o);
	//w.show();
	OriginInterface v;
	v.show();
    return a.exec();
}
