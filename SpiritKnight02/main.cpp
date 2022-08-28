#include "MyMainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>
int main(int argc, char *argv[])
{
	QFile file(":/css/Resource/stylesheet.css");
	if (file.open(QFile::ReadOnly))
	{
		qApp->setStyleSheet(file.readAll());
	}
	else {
		QMessageBox::about(NULL, "Test", "Open File Failed");
		//file.close();
	}
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();
    return a.exec();
}
