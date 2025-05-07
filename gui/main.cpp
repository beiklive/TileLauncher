#include <QApplication>
#include <QWidget>
#include "ui_window/ui_window.h"

using namespace beiklive;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Ui_Window w;
    w.show();
    return a.exec();
}
