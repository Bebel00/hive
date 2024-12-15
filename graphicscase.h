#ifndef GRAPHICSCASE_H
#define GRAPHICSCASE_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QBrush>

class GraphicsCase : public QGraphicsPolygonItem
{
public:
    GraphicsCase(class Case* case_, QGraphicsItem* parent = nullptr);

    friend class GraphicsPlateau;

    class Case* case_logique;

    // https://doc.qt.io/qt-6/qgraphicsitem.html#type
    // Pour utiliser qgraphicsitem_cast
    enum { Type = UserType + 1 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public:
    void surbrillance(QColor color);
    void reset_surbrillance();
    void setBrush(const QBrush &brush);

private:
    QBrush remplissage;
    bool hovered = false;
    bool wants_hovering = false;

private:
    QGraphicsTextItem* textItem;

    static constexpr float SCALE = 20.0;
};

#endif // GRAPHICSCASE_H
