#include "pacman_game.h"
#include "appsettings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //static auto sw = AppSettings::instance().screenWidth();
    //static auto sh = AppSettings::instance().screenHeight();

    QApplication a(argc, argv);
    AppSettings::instance();

    pacman_game app;
    app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    app.setFixedSize(800, 600);

    app.show();
    //app.showFullScreen();

    return a.exec();
}
