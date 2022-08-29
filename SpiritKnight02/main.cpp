#include "MyMainWindow.h"
#include "Start.h"
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
	/*Start s;
	s.show();*/
	MyMainWindow w(3);
	w.show();
    return a.exec();
}
