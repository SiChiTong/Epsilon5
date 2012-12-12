#include <QDebug>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include "sceneview.h"
//------------------------------------------------------------------------------
TSceneView::TSceneView(TScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , mFixedPoint(QPoint())
    , mPx(new QPixmap())
{
}
//------------------------------------------------------------------------------
void TSceneView::paintEvent(QPaintEvent* event)
{
    QGraphicsView::paintEvent(event);
}
//------------------------------------------------------------------------------
void TSceneView::setBackground(const QPixmap& pixmap)
{
    setBackground(pixmap, pixmap.size());
}
//------------------------------------------------------------------------------
void TSceneView::setBackground(const QPixmap& pixmap, const QSize& sceneSize)
{
    *mPx = pixmap.copy(0, 0, sceneSize.width(), sceneSize.height());
    setSceneRect(-mPx->width() / 2, -mPx->height() / 2, mPx->width(), mPx->height());
}
//------------------------------------------------------------------------------
void TSceneView::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);
    const quint8 SCENE_BORDER_SIZE = 10;
    QRect backgroundRect(-mPx->width() / 2, -mPx->height() / 2,
        mPx->width(), mPx->height());
    painter->drawPixmap(backgroundRect, *mPx);
    QPen oldPen = painter->pen();
    painter->setPen(QPen(QBrush(Qt::black), SCENE_BORDER_SIZE));
    painter->drawRect(backgroundRect);
    painter->setPen(oldPen);
}
//------------------------------------------------------------------------------
void TSceneView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    mButton = event->button();
    mFixedPoint = event->pos();
}
//------------------------------------------------------------------------------
void TSceneView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    mButton = Qt::NoButton;
    mFixedPoint = event->pos();
}
//------------------------------------------------------------------------------
void TSceneView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(!mFixedPoint.isNull() && items(event->pos()).size() <= 0 &&
        mButton == Qt::LeftButton && event->modifiers() != Qt::ShiftModifier &&
        event->modifiers() != Qt::ControlModifier)
    {
        QPointF offset = mapToScene(mFixedPoint) - mapToScene(event->pos());
        mFixedPoint = event->pos();
        setCenter(center() + offset);
    }
}
//------------------------------------------------------------------------------
void TSceneView::wheelEvent(QWheelEvent *event)
{
    QPointF pointBeforeScale(mapToScene(event->pos()));
    QPointF visibleCenter = center();

    double scaleFactor = 1.2;
    if(event->delta() > 0 )
        scale(scaleFactor, scaleFactor);
    else
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);

    QPointF pointAfterScale(mapToScene(event->pos()));
    QPointF offset = pointBeforeScale - pointAfterScale;
    QPointF newCenter = visibleCenter + offset;
    setCenter(newCenter);
}
//------------------------------------------------------------------------------
void TSceneView::setCenter(const QPointF &centerPoint)
{
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    QRectF sceneBounds = sceneRect();

    qreal boundX = visibleArea.width() / 2.0;
    qreal boundY = visibleArea.height() / 2.0;
    qreal boundWidth = sceneBounds.width() - visibleArea.width();
    qreal boundHeight = sceneBounds.height() - visibleArea.height();
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    mCenterPoint = centerPoint;

    if(!bounds.contains(centerPoint)) {
        if(visibleArea.contains(sceneBounds)) {
            mCenterPoint = sceneBounds.center();
        } else {
            if(centerPoint.x() > bounds.x() + bounds.width() / 2)
                mCenterPoint.setX(bounds.x() + bounds.width() / 2);
            else if(centerPoint.x() < bounds.x() - bounds.width())
                mCenterPoint.setX(bounds.x() - bounds.width() );

            if(centerPoint.y() > bounds.y() + bounds.height() / 2)
                mCenterPoint.setY(bounds.y() + bounds.height() / 2);
            else if(centerPoint.y() < bounds.y() - bounds.height())
                mCenterPoint.setY(bounds.y() - bounds.height());
        }
    }
    centerOn(mCenterPoint);
}
//------------------------------------------------------------------------------
QPointF TSceneView::center()
{
    return mCenterPoint;
}
//------------------------------------------------------------------------------
void TSceneView::resizeEvent(QResizeEvent* event)  {
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    setCenter(visibleArea.center());
    QGraphicsView::resizeEvent(event);
}
//------------------------------------------------------------------------------
