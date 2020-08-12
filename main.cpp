#include "serverwidget.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serverWidget w;
    w.show();
    //clientwidget w1;
    //w1.show();
    return a.exec();
}
