// maprespawncontainer.cpp
#include <QFile>
#include <QTextStream>
#include "containers/maprespawncontainer.h"
#include "../utils/uexception.h"
//------------------------------------------------------------------------------
TMapRespawnContainer::TMapRespawnContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
TMapRespawnContainer::TMapRespawnContainer(const TMapRespawnContainer &container)
    : TContainer(container.parent())
{
}
//------------------------------------------------------------------------------
TMapRespawnContainer::~TMapRespawnContainer()
{
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::addRespawn(const TMapRespawnInfo& info)
{
    QStandardItem* item = new QStandardItem;
    TMapRespawnItem *respawn = new TMapRespawnItem(info, this);
    item->setData(QVariant::fromValue(*respawn));
    item->setText(respawn->serialize());
    item->setSelectable(false);
    mModel->appendRow(item);
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::removeRespawn(const QModelIndex &index)
{
    mModel->removeRow(index.row());
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::loadFromFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::ReadOnly | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    TMapRespawnInfo info;
    while( !stream.atEnd() )
    {
        if( !info.unpack(stream.readLine()) )
        {
            qDebug( "%s :: Ingonring...", Q_FUNC_INFO );
            continue;
        }

        addRespawn(info);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::saveToFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    for( int i = 0; i < mModel->rowCount(); ++i ) {
        stream << mModel->item(i)->data()
            .value<TMapRespawnItem>().serialize() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
