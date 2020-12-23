#include <ui/main/MainWindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setObjectName("Main");
    w.show();
    return QApplication::exec();
}
