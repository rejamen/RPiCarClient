#include "rpicarclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPiCarClient w;
    w.show();

    return a.exec();
}
