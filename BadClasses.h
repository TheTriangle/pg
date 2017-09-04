#include "TXLib.h"

const COLORREF TRANSPARENTCOLOR = RGB (0, 0, 0);

const int CR_ABILITY = 0;
const int CR_SHOOT = 1;
const int CR_UP = 2;
const int CR_DOWN = 3;
const int CR_LEFT = 4; //ControlResult
const int CR_RIGT = 5;
const int CR_NONE = 6;

const int WPN_NONE = 0;
const int WPN_PISTOL = 1;
const int WPN_BOW = 2;        //WeaPoN
const int WPN_RIFLE = 3;
const int WPN_SPEAR = 4;
const int DIR_UP = 0;
const int DIR_DOWN = 1;       //DIRection
const int DIR_LEFT = 2;
const int DIR_RIGHT = 3;
const int ANM_FISTSTART = 0;
const int ANM_FISTFINISH = 320;
const int ANM_BOWSTART = 832;
const int ANM_BOWFINISH = 1344;
const int ANM_SPEARSTART = 320;   //ANiMation
const int ANM_SPEARFINISH = 544;
const int ANM_RIFLESTART = 544;
const int ANM_RIFLEFINISH = 832;


struct controls
    {
    int Ucontrol;
    int Rcontrol;
    int Dcontrol;
    int Lcontrol;
    int Fwpon;
    int Swpon;
    int Twpon;
    int Shoot;
    int Ability;
    };

class Unit
    {
    protected:
    int LastBowShootTick;
    int LastRifleShootTick;
    int LastSpearKickTick;
    int LastFistKickTick;

    int BowShootCooldownTicks;
    int RifleShootCooldownTicks;
    int SpearKickCooldownTicks;
    int FistKickCooldownTicks;

    controls ThisControl;

    int equpedweapon;
    int firstweapon;
    int secondweapon;
    int thirdweapon;
    double directpoint;
    POINT animationpoint;
    int id;

    double radius;
    HDC dc;
    POINT imgsize;
    int direction;
    POINT cords;
    double hp;

    //int direction;
    //int id;
    //POINT cords;
    //double hp;
    public:
    Unit (double x, double y, double ghp, int gid)
        {
            LastBowShootTick = 0;
        LastRifleShootTick = 0;
        LastSpearKickTick = 0;
        BowShootCooldownTicks = 150;
        SpearKickCooldownTicks = 200;
        RifleShootCooldownTicks = 15;
        ThisControl.Ucontrol = 'W';
        ThisControl.Rcontrol = 'D';
        ThisControl.Dcontrol = 'S';
        ThisControl.Lcontrol = 'A';
        ThisControl.Fwpon = '1';
        ThisControl.Swpon = '2';
        ThisControl.Twpon = '3';
        ThisControl.Shoot = 'E';
        ThisControl.Ability = 'Q';
        equpedweapon = WPN_NONE;
        firstweapon = WPN_NONE;
        secondweapon = WPN_NONE;
        thirdweapon = WPN_NONE;
        direction = 0;

        radius = grad;
        dc = image;
        imgsize = {imgwidth, imgheight};
        cords = {x, y};
        hp = ghp;
        id = gid;
        }
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
    //void setCords(double x, double y) : this->SetCords(x, y);
    void setRadius (double grad)
        {
        radius = grad;
        }
    double getRadius()
        {
        return radius;
        }
    double setImage (HDC image, double imgwidth, double imgheight)
        {
        dc = image;
        imgsize = {imgwidth, imgheight};
        }
    HDC getImage()
        {
        return dc;
        }
    ~CircleUnit()
        {
        txDeleteDC (dc);
        }


    bool TestIfHitted (CircleUnit bullet)
        {
        if (this->getDistanceTo(bullet.getX(), bullet.getY()) <= radius + bullet.getRadius()) return true;
        else return false;
        }

    double getDistanceTo (double xto, double yto)
        {
        return sqrt((cords.x - xto) * (cords.x - xto) + (cords.y - yto) * (cords.y - yto));
        }

    double getAxisAngleTo (double xto, double yto)
        {
        return asin(cords.y - yto / getDistanceTo (xto, yto));
        }

    double getAngle()
        {
        return getAxisAngleTo (txMouseX(), txMouseY());
        }

    double getAngleTo (double xto, double yto)
        {
        return getAngle() - getAxisAngleTo (xto, yto);
        }
    int draw (double lucx, double lucy, double alpha)
        {
        if (!dc) printf ("my picture is not loaded\n");
        //txAlphaBlend (txDC(), cords.x - imgsize.x, cords.y - imgsize.y, imgsize.x, imgsize.y, dc, animationpoint.x, animationpoint.y, alpha);
        txAlphaBlend (txDC(), 100, 100, 64, 64, dc, 0, 0, alpha);
        printf ("x == %f, y == %f\n", cords.x, cords.y);
        printf ("animx == %f, animy == %f", animationpoint.x, animationpoint.y);
        printf ("imgsizex == %f, imgsizey == %f", imgsize.x, imgsize.y);
        getch();
        return 0;
        }
    void Move (int tick)
        { //Внимание! Копипаста! 18+ шок контент! слабонервным не смотреть ниже!
        if (tick < LastBowShootTick + BowShootCooldownTicks)
            {
            directpoint = ANM_BOWSTART + (tick - LastBowShootTick)/BowShootCooldownTicks
                                              *(ANM_BOWFINISH - imgsize.x - ANM_BOWSTART);
            }

        if (tick < LastSpearKickTick + SpearKickCooldownTicks)
            {
            directpoint = ANM_SPEARSTART + (tick - LastSpearKickTick)/SpearKickCooldownTicks
                                              *(ANM_SPEARFINISH - imgsize.x - ANM_SPEARSTART);
            }

        if (tick < LastRifleShootTick + RifleShootCooldownTicks)
            {
            directpoint = ANM_RIFLESTART + (tick - LastRifleShootTick)/RifleShootCooldownTicks
                                                *(ANM_RIFLEFINISH - imgsize.x - ANM_RIFLESTART);
            }

        if (tick < LastFistKickTick + FistKickCooldownTicks)
            {
            directpoint = ANM_FISTSTART + (tick - LastFistKickTick)/FistKickCooldownTicks
                                                *(ANM_FISTFINISH - imgsize.x - ANM_FISTSTART);
            }
        animationpoint = {(double)(directpoint - (int)(directpoint)%(int)(imgsize.x)), (double)(direction * imgsize.y)};
        this->draw (animationpoint.x, animationpoint.y, 1);
        }

    int control (double speed, int tick)
        {
        if (GetAsyncKeyState (ThisControl.Ucontrol))
            {
            cords.y -= speed;
            direction = 0;
            }
        if (GetAsyncKeyState (ThisControl.Rcontrol))
            {
            cords.x += speed;
            direction = 1;
            }
        if (GetAsyncKeyState (ThisControl.Dcontrol))
            {
            cords.y += speed;
            direction = 2;
            }
        if (GetAsyncKeyState (ThisControl.Lcontrol))
            {
            cords.x -= speed;
            direction = 3;
            }
        if (GetAsyncKeyState (ThisControl.Fwpon))    equpedweapon = firstweapon;
        if (GetAsyncKeyState (ThisControl.Swpon))    equpedweapon = secondweapon;
        if (GetAsyncKeyState (ThisControl.Twpon))    equpedweapon = thirdweapon;
        if (GetAsyncKeyState (ThisControl.Shoot))
            {
            if (equpedweapon == WPN_BOW) LastBowShootTick = tick;
            if (equpedweapon == WPN_RIFLE) LastRifleShootTick = tick;
            if (equpedweapon == WPN_SPEAR) LastSpearKickTick = tick;
            if (equpedweapon == WPN_NONE) LastFistKickTick = tick;
            return CR_SHOOT;
            }
        if (GetAsyncKeyState (ThisControl.Ability)) return CR_ABILITY;
        return CR_NONE;
        }
    };




class RectangleUnit : public Unit
    {
    protected:
    POINT width;
    HDC dc;
    POINT imgsize;
    public:
    int draw (double lucx, double lucy, double alpha)
        {
        txAlphaBlend(txDC(), cords.x - imgsize.x/2, cords.y - imgsize.y/2, imgsize.x, imgsize.y, dc, lucx, lucy, alpha);
        return 0;
        }
    RectangleUnit (HDC image, double imwidth, double imheight, double x, double y, double xwid, double ywid, double ghp, int id) : Unit (x, y, ghp, id)
        {
        dc = image;
        width = {xwid, ywid};
        }

    //RectangleUnit (HDC image, double imwidth, double imheight, double xwid, double ywid, double ghp, int id) : Unit (ghp, id)
    //    {
    //    dc = image;
    //    width = {xwid, ywid};
    //    }

    void setWidth(POINT gwidth)
        {
        width = gwidth;
        }

    POINT getWidth()
        {
        return width;
        }

    double setImage (HDC image, double imwidth, double imheight)
        {
        dc = image;
        imgsize = {imwidth, imheight};
        }

    HDC getImage()
        {
        return dc;
        }

    ~RectangleUnit()
        {
        txDeleteDC (dc);
        }


    bool TestIfHitted (CircleUnit bullet)
        {
        if (bullet.getX() + bullet.getRadius() >= cords.x
         && bullet.getX() - bullet.getRadius() <= cords.x + width.x
         && bullet.getY() + bullet.getRadius() >= cords.y
         && bullet.getY() - bullet.getRadius() <= cords.y + width.y) return true;
        else return false;
        }
    };

class Bullet : CircleUnit
    {
    protected:
    double angle;
    double speed;
    public:
    Bullet (HDC image, double imgwidth, double imgheight, double x, double y, double grad, double sangle, double sspeed, double ghp, int id) : CircleUnit (image, imgwidth, imgheight, x, y, grad, ghp, id)
        {
        angle = sangle;
        speed = sspeed;
        }
    void move (double dt)
        {
        cords.y += speed * sin (angle) * dt;
        }
    };



