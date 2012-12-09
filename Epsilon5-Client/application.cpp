#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QApplication(argc, argv)
    , MainDisplay(this)
    , Network(new TNetwork(this))
    , Settings(new TSettings(this))
{
    connect(Network, SIGNAL(WorldReceived()), &MainDisplay, SLOT(RedrawWorld()));
}

bool TApplication::Init() {
    MainDisplay.Init();
    MainDisplay.show();
    Network->Start();
    MainDisplay.toggleFullscreen();
    return true; // TODO: normal initialisation
}
