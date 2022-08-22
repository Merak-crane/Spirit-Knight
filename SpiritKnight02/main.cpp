#include "MyMainWindow.h"
#include "Start.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MyMainWindow w;
    //w.show();
    Start s;
    s.show();
    return a.exec();
}
