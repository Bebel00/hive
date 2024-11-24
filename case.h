#ifndef CASE_H
#define CASE_H

#include "teams.h"
#include <QGraphicsPolygonItem>

class Insecte;

class Position
{
    /*
     * Structure qui sert à compter la position d'un hexagone
     * Utile pour retrouver un hexagone juste en connaissant sa position
     *
     * La première case devrait être en (0; 0)
     * Aller en Haut Droit fait bouger de 1 en x et en y
     * Aller en Haut Gauche fait avancer de -1 en x, 1 en y
     * Aller à Droite fait avancer de 2 en x
     * Aller à Gauche fait bouger de -2 en x
     * Aller en Bas Droit fait avancer de 1 en x et -1 en y
     * Enfin, aller en Bas Gauche
     */

public:
    Position() { }
    Position(int x, int y) : x(x), y(y) { }

    int x = 0;
    int y = 0;


    // Fonctions qui permettent d'aditionner / de soustraire des positions entre elles

    Position operator+(const Position& a)
    {
        return Position(x + a.x, y + a.y);
    }

    Position& operator+=(const Position& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    Position operator-(const Position& a)
    {
        return Position(x - a.x, y - a.y);
    }

    bool operator==(const Position& a)
    {
        return (x == a.x && y == a.y);
    }
};

class Case : public QGraphicsPolygonItem
{

    friend class Plateau;
    friend class Insecte;

public:
    enum class Direction
    {
        HAUT_DROIT,
        DROITE,
        BAS_DROIT,
        HAUT_GAUCHE,
        GAUCHE,
        BAS_GAUCHE,
        NONE
    };

    static constexpr Direction DIRECTIONS_ALL[] =
        { Direction::HAUT_DROIT, Direction::DROITE, Direction::BAS_DROIT, Direction::HAUT_GAUCHE, Direction::GAUCHE, Direction::BAS_GAUCHE };

    // Fonction qui renvoie la direction opposée à une direction
    static Direction DIRECTION_OPPOSE(Direction direction);

    // Fonction qui renvoie un incrément de position pour une direction donnée
    // Par exemple Direction::HAUT_DROIT renvoie (+1, +1)
    // Direction::GAUCHE renvoie (-2, 0).
    static Position direction_to_position_increment(Direction direction);

public:
    /*
     *  Fonction qui sert à vérifier si une case est nulle
     *  On utilise une fonction statique pour l'utiliser même on a une case nullptr
     *  Par exemple pour faire Case::is_empty(case->droite).
     *  Ce qui ne marcherait pas avec case->droite->is_empty().
     */
    static bool is_empty(const class Case* const c)
    {
        // Si la case n'est pas nullptr on regarde si son pion n'est pas nullptr
        if (c)
            // Pas de pion (pion nullptr) <=> case vide
            return !(c->pion);

        // Si la case est nullptr, on considère que c'est comme si c'était une case vide
        return true;
    }

    /*
     *  Fonction qui crée une  nouvelle case.
     * Elle vérifie que la création de case se passe bien,
     * et qu'il n'y a pas déjà une case à l'endroit souhaité.
     *
     * Renvoie le pointeur si tout s'est bien passé.
     */
    Case* creer_case(Direction direction, class Plateau* const plateau);

    // Fonction qui renvoie le pointeur vers la case dans la direction en paramètre
    Case* get_case_from_direction(Direction direction) const;

    // getter pour l'équipe de la case
    Team get_team() const;

    // getter pour si la case a un pion
    bool possede_pion() const { return pion != nullptr; }
    class Insecte* get_pion() const { return pion.get(); }

    // getter pour la position de la case
    Position get_position() const { return position; }

    // getter plateau
    const class Plateau* get_plateau() const { return plateau; }

    // https://doc.qt.io/qt-6/qgraphicsitem.html#type
    // Pour utiliser qgraphicsitem_cast
    enum { Type = UserType + 1 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    ~Case();

private:
    // Fonction qui renvoie un pointeur le pointeur vers la case dans la direction en paramètre
    // C'est un peu complexe mais c'est juste pour changer la valeur des variables juste en dessous
    class Case** case_ptr_from_direction(Direction direction);

    /*
     * Les 6 côtés de l'hexagone
     * La classe est une sorte de liste chaînée
     */
    class Case* haut_droit = nullptr;
    class Case* haut_gauche = nullptr;
    class Case* droite = nullptr;
    class Case* gauche = nullptr;
    class Case* bas_droit = nullptr;
    class Case* bas_gauche = nullptr;

    // Pion qui occupe la case
    std::unique_ptr<class Insecte> pion;

    // Fonction récusrive qui renvoie la liste des cases créées en mémoire
    // void get_toutes_cases_recursif(std::vector<Case *> &cases, Case* case_a_visiter);
    // Pour plus tard si on en a besoin

    // Position (coordonnées) de la case
    Position position;

    // Pointeur vers le plateau qui gère la case
    class Plateau* const plateau;

    bool visite = false;

    // Constructeur en privé car seul plateau peut créer une case
    Case(Position position, class Plateau* plateau, QGraphicsItem* parent = nullptr);

    QGraphicsTextItem* textItem;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static constexpr float SCALE = 20.0;
};

#endif // CASE_H
