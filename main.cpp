#include"widget.h"
#include"startwidget.h"
#include"overwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.hide();



    return a.exec();
}
