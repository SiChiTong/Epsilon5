#pragma once
#include <QWidget>
#include <QImage>
#include <QQueue>
#include "../Epslion5-Proto/Epsilon5.pb.h"
#include "imagestorage.h"
#include "map.h"

class TApplication;

class TMainDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit TMainDisplay(TApplication* application, QWidget *parent = 0);
    ~TMainDisplay();

    inline const Epsilon5::Control& GetControl() { return Control; }
public slots:
    void RedrawWorld();
private:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    TApplication* Application;
    QImage* Frame;
    TImageStorage* Images;
    QQueue<Epsilon5::World> PacketsQueue;
    Epsilon5::Control Control;
    TMap* Map;
};
