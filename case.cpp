#include "case.h"
#include "insecte.h"
#include <iostream>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>


Case::Direction Case::DIRECTION_OPPOSE(Direction direction)
{
    switch(direction)
    {
    case Direction::HAUT_DROIT:
        return Direction::BAS_GAUCHE;
        break;
    case Direction::DROITE:
        return Direction::GAUCHE;
        break;
    case Direction::BAS_DROIT:
        return Direction::HAUT_GAUCHE;
        break;
    case Direction::HAUT_GAUCHE:
        return Direction::BAS_DROIT;
        break;
    case Direction::GAUCHE:
        return Direction::DROITE;
        break;
    case Direction::BAS_GAUCHE:
        return Direction::HAUT_DROIT;
        break;
    default:
        return Direction::NONE;
    }
}

Position Case::direction_to_position_increment(Direction direction)
{
    switch(direction)
    {
    case Direction::HAUT_DROIT:
        return Position(1, 1);
        break;
    case Direction::DROITE:
        return Position(2, 0);
        break;
    case Direction::BAS_DROIT:
        return Position(1, -1);
        break;
    case Direction::HAUT_GAUCHE:
        return Position(-1, 1);
        break;
    case Direction::GAUCHE:
        return Position(-2, 0);
        break;
    case Direction::BAS_GAUCHE:
        return Position(-1, -1);
        break;
    default:
        return Position(0, 0);
    }
}

Case::Case(Position position, Plateau *plateau, QGraphicsItem* parent) : QGraphicsPolygonItem(parent), position(position), plateau(plateau)
{
    pion = nullptr;

    QVector<QPoint> points;

    points << QPoint(0, 4) * SCALE << QPoint(4, 2) *  SCALE << QPoint(4, -2) *  SCALE << QPoint(0, -4) * SCALE
           << QPoint(0, -4) * SCALE << QPoint(-4, -2) * SCALE << QPoint(-4, 2) * SCALE;

    setPolygon(QPolygonF(points));
    setPolygon(polygon().translated(get_position().x * 4 * Case::SCALE, get_position().y * 6 * Case::SCALE));

    // Create and configure the text item
    textItem = new QGraphicsTextItem("", this);
    textItem->setDefaultTextColor(Qt::white);  // Set text color
    textItem->setFont(QFont("Arial", 30));     // Set font and size

    // Position text in the center of the hexagon
    QRectF bounds = boundingRect();
    textItem->setPos(bounds.center() - textItem->boundingRect().center());
    setAcceptHoverEvents(true);
}

void Case::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (possede_pion()) {
        setBrush(QBrush(Qt::green)); 
    }
    QGraphicsPolygonItem::mousePressEvent(event);
    //*std::cout << "Clicked !" << std::endl;//
}
void Case::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::blue, Qt::Dense4Pattern)); 
    QGraphicsPolygonItem::hoverEnterEvent(event);
}

void Case::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(Qt::NoBrush); // Reset highlight when hover ends
    QGraphicsPolygonItem::hoverLeaveEvent(event);
}

Case* Case::creer_case(Direction direction, Plateau* const plateau)
{
    Case** case_a_creer = case_ptr_from_direction(direction);

    if (!case_a_creer)
    {
        std::cout << "Erreur dans la direction de la case à créer" << std::endl;
        return nullptr;
    }
    if (*case_a_creer)
    {
        std::cout << "La case à créer existe déjà" << std::endl;
        return nullptr;
    }
    *case_a_creer = new Case(position + direction_to_position_increment(direction), plateau);

    if (!*case_a_creer)
    {
        std::cout << "Impossible de créer une nouvelle case." << std::endl;
        return nullptr;
    }
    return *case_a_creer;
}

Case* Case::get_case_from_direction(Direction direction) const
{
    Case* case_cherchee = nullptr;

    switch (direction)
    {
    case Direction::HAUT_DROIT:
        case_cherchee = haut_droit;
        break;
    case Direction::DROITE:
        case_cherchee = droite;
        break;
    case Direction::BAS_DROIT:
        case_cherchee = bas_droit;
        break;
    case Direction::HAUT_GAUCHE:
        case_cherchee = haut_gauche;
        break;
    case Direction::GAUCHE:
        case_cherchee = gauche;
        break;
    case Direction::BAS_GAUCHE:
        case_cherchee = bas_gauche;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

Case** Case::case_ptr_from_direction(Direction direction)
{
    Case** case_cherchee = nullptr;

    switch (direction)
    {
    case Direction::HAUT_DROIT:
        case_cherchee = &haut_droit;
        break;
    case Direction::DROITE:
        case_cherchee = &droite;
        break;
    case Direction::BAS_DROIT:
        case_cherchee = &bas_droit;
        break;
    case Direction::HAUT_GAUCHE:
        case_cherchee = &haut_gauche;
        break;
    case Direction::GAUCHE:
        case_cherchee = &gauche;
        break;
    case Direction::BAS_GAUCHE:
        case_cherchee = &bas_gauche;
        break;
    default:
        case_cherchee = nullptr;
    }

    return case_cherchee;

}

Team Case::get_team() const
{
    if (pion) return pion->get_team(); else return Team::NONE;
}

bool Case::possede_pion() const
{
    return pion != nullptr;
}

void Case::surbrillance(QColor color)
{
    setPen(QPen(color));
    setZValue(0.5);
}

void Case::reset_surbrillance()
{
    setPen(QPen(Qt::red));
    setZValue(0);
}

Case::~Case() = default;

