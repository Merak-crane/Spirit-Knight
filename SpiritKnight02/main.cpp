
#include "Start.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>
#include <QLinearGradient>
int main(int argc, char *argv[])
{

	// 设置媒体
	// 方式一：不推荐使用
	//player->setMedia(QMediaContent(QUrl("../testMusic/你的名字.wav")));	

	// 方式二：推荐使用
	/*player->setMedia(QUrl::fromLocalFile("D:\VS2019\Git\SpiritKnight02\Resource\sound\h_att01.wav"));*/
	//player->setMedia(QUrl::fromLocalFile("D:\\music\\你的名字.mp3"));

	//player->setVolume(50);	// 设置音频播放的初始音量大小
	//player->play();	// 开始播放

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
