#include "TXLib.h"

class Unit
    {
    protected:
    POINT cords;
    double hp;
    public:
    Unit (double ghp)
        {
        cords = {0, 0};
        hp = ghp;
        }
    void setCords (double x, double y)
        {
        cords = {x, y};
        }
    POINT getCords()
        {
        return cords;
        }
    void setHp (double ghp)
        {
        hp = ghp;
        }
    double getHp()
        {
        return hp;
        }
    };

class CircleUnit : public Unit
    {
    protected:
    double radius;
    public:
    CircleUnit (double grad, double ghp) : Unit (ghp)
        {
        radius = grad;
        }
    void setRadius (double grad)
        {
        radius = grad;
        }
    double getRadius ()
        {
        return radius;
        }
    };
