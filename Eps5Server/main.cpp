/**
 * @file
 * Основной файл приложения
 */
#include <QCoreApplication>
#include "application.h"
#include "../Eps5Proto/Epsilon5.pb.h"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Application app(argc, argv);

    if (!app.init())
        return 1;
    
    return app.exec();
}
