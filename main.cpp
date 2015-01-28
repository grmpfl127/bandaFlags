#include "bandaflags.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bandaFlags w;
    w.setWindowIcon(QIcon(":/cfg/res/worldFlag.png"));
    w.setWindowTitle("bandaFlags");
    w.show();
    return a.exec();
}
