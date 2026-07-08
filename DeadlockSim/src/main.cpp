#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Deadlock Simulator");
    app.setOrganizationName("NASTP IIT - BS Cyber Security");

    MainWindow window;
    window.show();

    return app.exec();
}
