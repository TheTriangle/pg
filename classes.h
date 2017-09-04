#define DEGREEMODIFIER  0.0175
#define PI 3.1415
double GLOBALSIZE = 2;
const int DIR_UP = 0;
const int DIR_DOWN = 2;       //DIRection
const int DIR_LEFT = 3;
const int DIR_RIGHT = 1;
const int DIR_URIGHT = 4;
const int DIR_DRIGHT = 5;
const int DIR_DLEFT = 6;
const int DIR_ULEFT = 7;
//const int DIR_UURIGHT = 8;
//const int DIR_DDRIGHT = 9;
//const int DIR_DDLEFT = 10;
//const int DIR_UULEFT = 11;

const int BDIR_UP = 0;
const int BDIR_UURIGHT = 1;
const int BDIR_URIGHT = 2;
const int BDIR_RIGHT = 3;
const int BDIR_DRIGHT = 4;
const int BDIR_DDRIGHT = 5;
const int BDIR_DOWN = 6;       //DIRection
const int BDIR_DDLEFT = 7;
const int BDIR_DLEFT = 8;
const int BDIR_LEFT = 9;
const int BDIR_ULEFT = 10;
const int BDIR_UULEFT = 11;

const int BULLETSPEED = 14;
const int ARROWWIDTH = 16;
const int ARROWHEIGHT = 16;
const int BULLETWIDTH = 16;
const int BULLETHEIGHT = 16;
const int ARROWRADIUS = 4;
const int BULLETRADIUS = 1;
const double ARROWDAMAGE = 1;
const double BULLETDAMAGE = 1;
const double ARROWSPEED = 10;
#include "TXLib.h"
HDC GARROWDC;
HDC GBULLETDC;
#include "Other.h"
#include "Unit.h"
//#include "Bullet.h"
#include "Bullet.h"
#include "CircleUnit.h"
#include "Player.h"
#include "RectangleUnit.h"

