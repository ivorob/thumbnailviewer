#include <QtWidgets>
#include "MainWindow.h"

int
main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow("Thumbnail Viewer");
    mainWindow.show();
    return app.exec();
}
