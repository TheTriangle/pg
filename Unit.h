#if !defined (__UNIT_H_INCLUDED__)
#define       __UNIT_H_INCLUDED
class Unit
    {
    protected:
    int direction;
    int id;
    POINT cords;
    double hp;
    public:
    Unit (double x, double y, double ghp, int gid)
        {
        cords = {x, y};
        hp = ghp;
        id = gid;
        }
    Unit(){}
    Unit (double ghp, int gid)
        {
        cords = {0, 0};
        hp = ghp;
        id = gid;
        }
    void setCords (double x, double y)
        {
        cords = {x, y};
        }
    POINT getCords()
        {
        return cords;
        }
    double getX()
        {
        return cords.x;
        }
    double getY()
        {
        return cords.y;
        }
    void setHp (double ghp)
        {
        hp = ghp;
        }
    double getHp()
        {
        return hp;
        }
    void setDirection(int dir)
        {
        direction = dir;
        }
    int getDirection()
        {
        return direction;
        }
    };
#endif
