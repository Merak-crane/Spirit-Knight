
#include "Start.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>
#include <QLinearGradient>
int main(int argc, char *argv[])
{

	// ����ý��
	// ��ʽһ�����Ƽ�ʹ��
	//player->setMedia(QMediaContent(QUrl("../testMusic/�������.wav")));	

	// ��ʽ�����Ƽ�ʹ��
	/*player->setMedia(QUrl::fromLocalFile("D:\VS2019\Git\SpiritKnight02\Resource\sound\h_att01.wav"));*/
	//player->setMedia(QUrl::fromLocalFile("D:\\music\\�������.mp3"));

	//player->setVolume(50);	// ������Ƶ���ŵĳ�ʼ������С
	//player->play();	// ��ʼ����

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
	Start s;
	s.show();
	/*Player* o = new Player("222", "sss", "ss", 100);
	MyMainWindow w(3,o);
	w.show();*/
    return a.exec();
}
