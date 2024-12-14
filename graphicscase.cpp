#include "graphicscase.h"

#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QVector>
#include <QPen>

#include "case.h"

GraphicsCase::GraphicsCase(Case* case_, QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent), case_logique(case_)
{
    QVector<QPoint> points;

    points << QPoint(0, 4) * SCALE << QPoint(4, 2) *  SCALE << QPoint(4, -2) *  SCALE << QPoint(0, -4) * SCALE
           << QPoint(0, -4) * SCALE << QPoint(-4, -2) * SCALE << QPoint(-4, 2) * SCALE;

    setPolygon(QPolygonF(points));
    setPolygon(polygon().translated(case_->get_position().x() * 4 * SCALE, case_->get_position().y() * 6 * SCALE));

    // Create and configure the text item
    textItem = new QGraphicsTextItem("", this);
    textItem->setDefaultTextColor(Qt::white);  // Set text color
    textItem->setFont(QFont("Arial", 30));     // Set font and size

    // Position text in the center of the hexagon
    QRectF bounds = boundingRect();
    textItem->setPos(bounds.center() - textItem->boundingRect().center());

    setAcceptHoverEvents(true);
}

void GraphicsCase::surbrillance(QColor color)
{
    setPen(QPen(color));
    setZValue(0.5);
}

void GraphicsCase::reset_surbrillance()
{
    setPen(QPen(Qt::red));
    setZValue(0);
}

void GraphicsCase::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    wants_hovering = true;

    setBrush(QBrush(Qt::blue, Qt::Dense4Pattern));
    QGraphicsPolygonItem::hoverEnterEvent(event);

    hovered = true;
    wants_hovering = false;
}

void GraphicsCase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

    hovered = false;

    setBrush(QBrush(remplissage)); // Reset highlight when hover ends
    QGraphicsPolygonItem::hoverLeaveEvent(event);
}

void GraphicsCase::setBrush(const QBrush &brush)
{
    if (wants_hovering)
        remplissage = QGraphicsPolygonItem::brush();

    if (!hovered)
        QGraphicsPolygonItem::setBrush(brush);
}
