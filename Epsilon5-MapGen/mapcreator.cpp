#include "mapcreator.h"
#include <stdexcept>
#include <QDebug>
#include "graphicsview.h"
#include "mapitem.h"
#include <QHBoxLayout>


MapCreator::MapCreator(QString name, QSize size, QImage background, QString path, QString objPath, QWidget *parent) :
    QWidget(parent), _name(name), _size(size), _background(background), _path(path), _objPath(objPath)
{
//    // Create map dir
//    if ( !_path.mkdir(_name) || !_path.cd(_name) )
//        throw std::runtime_error("Create dir error");

//    // Create map files
//    _mConfig.setFileName(_path.absoluteFilePath(MAP_CONF_FILE));
//    _mObject.setFileName(_path.absoluteFilePath(MAP_FILE));

//    if ( !_mConfig.open(QIODevice::ReadWrite | QIODevice::Text) ||
//         !_mObject.open(QIODevice::ReadWrite | QIODevice::Text) )
//        throw std::runtime_error("Cannot create map files");

//    // Open objects files
//    _objs.setFileName(_objPath.absoluteFilePath(OBJS_FILE));
//    if ( !_objs.open(QIODevice::ReadOnly | QIODevice::Text) )
//        throw std::runtime_error("Cannot open objects file");

//    // Write config file
//    _mConfig.write(createConfFile());


    _scene = new QGraphicsScene(0, 0, 500, 700);
    GraphicsView *view = new GraphicsView(_scene);


    QGraphicsItem *item = new MapItem(QSize(50, 70));

    _scene->addItem(item);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}

QByteArray MapCreator::createConfFile()
{
    QString str;
    str += "name=" + _name + '\n';
    str += "width=" + QString::number(_size.width()) + '\n';
    str += "height=" + QString::number(_size.height()) + '\n';

    return str.toLocal8Bit();
}
