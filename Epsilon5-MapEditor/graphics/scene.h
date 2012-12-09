#pragma once
#include <QGraphicsScene>
//------------------------------------------------------------------------------
class TScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TScene(QObject* parent = 0);

    void init();
    void setBackground(const QPixmap& pixmap);

signals:
    void viewportMoved(const QPointF& pos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
    Qt::MouseButton mButton;
    QPointF mOriginPos;
};
//------------------------------------------------------------------------------
