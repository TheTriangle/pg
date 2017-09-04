//#include "CircleUnit.h"
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


const double ANM_FISTSTART = 0;
const double ANM_FISTFINISH = 320;
const double ANM_BOWSTART = 832;
const double ANM_BOWFINISH = 1344;
const double ANM_SPEARSTART = 320;   //ANiMation
const double ANM_SPEARFINISH = 576;
const double ANM_RIFLESTART = 576;
const double ANM_RIFLEFINISH = 832;



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


class Player : CircleUnit
    {
    protected:
    int LastBowShootTick;
    int LastRifleShootTick;
    int LastSpearKickTick;
    int LastFistKickTick;

    double BowShootCooldownTicks;
    double RifleShootCooldownTicks;
    double SpearKickCooldownTicks;
    double FistKickCooldownTicks;


    controls ThisControl;

    int equpedweapon;
    int firstweapon;
    int secondweapon;
    int thirdweapon;
    double directpoint;
    POINT animationpoint;
    int direction;
    int id;
    double hp;
    public:
    void setPlayerCords (double x, double y)
        {
        this->setCUnitCords(x, y);
        cords = {x, y};
        }
    POINT getPlayerCords ()
        {
        return this->getCUnitCords();
        }

    void Move (int tick)
        { //Внимание! Копипаста! 18+ шок контент! слабонервным не смотреть ниже!
        MoveBullets();
        DrawBullets();
        if (equpedweapon == WPN_NONE) directpoint = ANM_FISTSTART;
        if (equpedweapon == WPN_RIFLE) directpoint = ANM_RIFLESTART;
        if (equpedweapon == WPN_SPEAR) directpoint = ANM_SPEARSTART;
        if (equpedweapon == WPN_BOW) directpoint = ANM_BOWSTART;

        if (fabs (this->getAngle()/DEGREEMODIFIER) < 22.5) direction = DIR_RIGHT;
        if (this->getAngle()/DEGREEMODIFIER >= 22.5 && this->getAngle()/DEGREEMODIFIER < 67.5) direction = DIR_DRIGHT;
        if (this->getAngle()/DEGREEMODIFIER >= 67.5 && this->getAngle()/DEGREEMODIFIER < 112.5) direction = DIR_DOWN;
        if (this->getAngle()/DEGREEMODIFIER >= 112.5 && this->getAngle()/DEGREEMODIFIER < 157.5) direction = DIR_DLEFT;
        if (fabs (this->getAngle()/DEGREEMODIFIER) > 157.5) direction = DIR_LEFT;

        if (this->getAngle()/DEGREEMODIFIER <= -112.5 && this->getAngle()/DEGREEMODIFIER > -157.5) direction = DIR_ULEFT;
        if (this->getAngle()/DEGREEMODIFIER <= -67.5 && this->getAngle()/DEGREEMODIFIER > -112.5) direction = DIR_UP;
        if (this->getAngle()/DEGREEMODIFIER <= -22.5 && this->getAngle()/DEGREEMODIFIER > -67.5) direction = DIR_URIGHT;

        printf ("%f\n", this->getAngle()/DEGREEMODIFIER);


        if (tick < LastBowShootTick + BowShootCooldownTicks)
            {
            directpoint = ANM_BOWSTART + (tick - LastBowShootTick)/BowShootCooldownTicks
                                              *(ANM_BOWFINISH - ANM_BOWSTART);
            printf ("bow");
            }

        if (tick < LastSpearKickTick + SpearKickCooldownTicks)
            {
            directpoint = ANM_SPEARSTART + (tick - LastSpearKickTick)/SpearKickCooldownTicks
                                              *(ANM_SPEARFINISH - ANM_SPEARSTART);
            printf ("spear");
            }

        if (tick < LastRifleShootTick + RifleShootCooldownTicks)
            {
            directpoint = ANM_RIFLESTART + (tick - LastRifleShootTick)/RifleShootCooldownTicks
                                              *(ANM_RIFLEFINISH - ANM_RIFLESTART);
            printf ("rifle");
            }

        if (tick < LastFistKickTick + FistKickCooldownTicks)
            {
            directpoint = ANM_FISTSTART + (tick - LastFistKickTick)/FistKickCooldownTicks
                                              *(ANM_FISTFINISH - ANM_FISTSTART);
            printf ("fist");
            }
        animationpoint = {directpoint - (int)(directpoint) % (int)(imgsize.x), direction * imgsize.y};
        //animationpoint = {directpoint, direction * 64};
        printf ("\n%f\n", directpoint);
        this->draw (animationpoint.x, animationpoint.y, 1);
        }


    Player (HDC image, double imgwidth, double imgheight, double x, double y, double grad, double ghp, int id) : CircleUnit (image, imgwidth, imgheight, x, y, grad, ghp, id)
        {
        BowShootCooldownTicks = 60;
        SpearKickCooldownTicks = 40;
        RifleShootCooldownTicks = 10;
        FistKickCooldownTicks = 20;
        LastBowShootTick = -BowShootCooldownTicks;
        LastRifleShootTick = -RifleShootCooldownTicks;
        LastSpearKickTick = -SpearKickCooldownTicks;
        LastFistKickTick = -FistKickCooldownTicks;
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
        firstweapon = WPN_BOW;
        secondweapon = WPN_SPEAR;
        thirdweapon = WPN_RIFLE;
        direction = 0;
        directpoint = 0;
        animationpoint = {0, 0};
        }

    int control (double speed, int tick)
        {
        POINT helpcords = this->getPlayerCords();
        if (GetAsyncKeyState (ThisControl.Ucontrol))
            {
            this->setPlayerCords (helpcords.x, helpcords.y - speed);
            //direction = 0;
            printf ("GoUp\n");
            }
        if (GetAsyncKeyState (ThisControl.Rcontrol))
            {
            //printf ("IGoRight\n");
            this->setPlayerCords (helpcords.x + speed, helpcords.y);
            //direction = 1;
            printf ("GoRight\n");
            }
        if (GetAsyncKeyState (ThisControl.Dcontrol))
            {
            this->setPlayerCords (helpcords.x, helpcords.y + speed);
            //direction = 2;
            printf ("GoDown\n");
            }
        if (GetAsyncKeyState (ThisControl.Lcontrol))
            {
            this->setPlayerCords (helpcords.x - speed, helpcords.y);
            //direction = 3;
            printf ("GoLeft\n");
            }
        if (GetAsyncKeyState (ThisControl.Fwpon))    equpedweapon = firstweapon;
        if (GetAsyncKeyState (ThisControl.Swpon))    equpedweapon = secondweapon;
        if (GetAsyncKeyState (ThisControl.Twpon))    equpedweapon = thirdweapon;
        if (GetAsyncKeyState (ThisControl.Shoot))
            {
            if (equpedweapon == WPN_BOW && tick > LastBowShootTick + BowShootCooldownTicks)
                {
                LastBowShootTick = tick;
                this->Shoot(GARROWDC, ARROWWIDTH, ARROWHEIGHT, ARROWRADIUS, ARROWSPEED, ARROWDAMAGE, this->getAngle());
                }
            if (equpedweapon == WPN_RIFLE && tick > LastRifleShootTick + RifleShootCooldownTicks)
                {
                this->Shoot(GBULLETDC, BULLETWIDTH, BULLETHEIGHT, BULLETRADIUS, BULLETSPEED, BULLETDAMAGE, this->getAngle());
                LastRifleShootTick = tick;
                }
            if (equpedweapon == WPN_SPEAR && tick > LastSpearKickTick + SpearKickCooldownTicks) LastSpearKickTick = tick;
            if (equpedweapon == WPN_NONE && tick > LastFistKickTick + FistKickCooldownTicks) LastFistKickTick = tick;

            return CR_SHOOT;
            }
        if (GetAsyncKeyState (ThisControl.Ability)) return CR_ABILITY;
        return CR_NONE;
        }
    };

