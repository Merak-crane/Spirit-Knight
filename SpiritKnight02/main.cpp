#include "MyMainWindow.h"
#include "Start.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 /*   MyMainWindow w;
    w.show();*/
    Start s;
	QFile file(":/css/Resource/stylesheet.css");
	if (file.open(QFile::ReadOnly))
	{
		qApp->setStyleSheet(file.readAll());
		qDebug() << file.readAll();
	}
	else
		QMessageBox::about(NULL, "Test", "Open File Failed");
	file.close();
	s.show();
    return a.exec();
}
