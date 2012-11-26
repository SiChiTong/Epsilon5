#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "objects.h"

TObjects::TObjects(QObject *parent) :
    QObject(parent)
{
}

void TObjects::LoadObjects(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening file " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList objParams = line.split(":");
        if (objParams.size() != 5) {
            throw UException("Error loading objects from " + fileName);
        }
        bool ok = true;
        size_t id = objParams[0].toInt(&ok);
        if (!ok) {
            throw UException("Error loading objects from " + fileName);
        }
        QPoint pos;
        pos.setX(objParams[1].toInt(&ok));
        if (!ok) {
            throw UException("Error loading objects from " + fileName);
        }
        pos.setY(objParams[2].toInt(&ok));
        if (!ok) {
            throw UException("Error loading objects from " + fileName);
        }
        bool isDynamic = objParams[3] == "1" ? true : false;
        Objects.insert(id, pos);
        ObjectsIsDyn.insert(id, isDynamic);
    }
}

QPointF TObjects::GetObjectSize(size_t id) {
    if (Objects.find(id) == Objects.end()) {
        throw UException("Object not found!");
    }
    return Objects[id];
}

bool TObjects::IsDynamicObject(size_t id) {
    if (ObjectsIsDyn.find(id) == ObjectsIsDyn.end()) {
        throw UException("Object not found!");
    }
    return ObjectsIsDyn[id];
}
