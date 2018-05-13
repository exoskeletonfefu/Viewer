#include "viewer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Viewer viewer;
    viewer.show();
    app.exec();
//    for (int i = 0; i < 1000000000; i++) {}
    return 0;
}
