#include "MapForm.h"
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow window;
//    window.show();
    MapForm* mapw = new MapForm();
    mapw->show();
    return a.exec();
}
