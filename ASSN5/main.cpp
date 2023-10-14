#include "ui/gameui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameUi gameUi;
    gameUi.show();
    return app.exec();
}
