#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
    , World(new TWorld(this))
    , Server(new TServer(this))
    , Objects(new TObjects(this))
    , Maps(new TMaps(this))
{
    connect(Server, SIGNAL(NewPlayer(size_t)),
            World, SLOT(PlayerSpawn(size_t)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(PlayerKill(size_t)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(NeedFullPacket()));

    connect(Maps, SIGNAL(SpawnObject(size_t, int, int, double)),
            World, SLOT(SpawnObject(size_t, int, int, double)));

    connect(Maps, SIGNAL(SpawnBorders(QSize)),
            World, SLOT(SpawnBorders(QSize)));

    connect(Maps, SIGNAL(ClearObjects()),
            World, SLOT(ClearObjects()));

    connect(Maps, SIGNAL(ClearBorders()),
            World, SLOT(ClearBorders()));

    connect(Maps, SIGNAL(MapLoaded()),
            World, SLOT(NeedFullPacket()));
}

bool TApplication::Init() {
    Objects->LoadObjects("objects/objects.txt");
    Maps->LoadMaplist("maplist.txt");
    Maps->LoadNextMap();
    if (Server->Start()) {
        World->Start();
        return true;
    }
    return false;
}
