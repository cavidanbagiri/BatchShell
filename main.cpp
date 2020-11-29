#include "BatchShell.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BatchShell w;
    w.show();
    return a.exec();
}
