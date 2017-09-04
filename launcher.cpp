#include "classes.h"
#include "Button.h"
int main()
    {
    txCreateWindow (GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));

    // Загружаем изображения один раз, в начале программы
    txSetFillColor (TX_BLACK);
    HDC etnodc = txLoadImage ("hero.bmp");
    HDC grounddc = txLoadImage ("ground.bmp");
    GARROWDC = txLoadImage ("arrow.bmp");
    GBULLETDC = txLoadImage ("bullet.bmp");
    tx_auto_func (txDeleteDC(GARROWDC));
    tx_auto_func (txDeleteDC(GBULLETDC));
    if (!etnodc) printf ("cannot load etno.bmp");
    if (!grounddc) txMessageBox ("cannot load ground dc");
    Player Etno (etnodc, 64, 64, 100, 100, 20, 100, 1);
    Etno.setPlayerCords (100, 100);
    txSetFillColor (RGB (51, 200, 26));
    for (int i = 0; !GetAsyncKeyState (VK_ESCAPE); i++)
        {
        //if (!myAlphaBlend (txDC(),
        //GetSystemMetrics(SM_CXFULLSCREEN)/2 - GetSystemMetrics(SM_CXFULLSCREEN)/2 * GLOBALSIZE,
        //GetSystemMetrics(SM_CYFULLSCREEN)/2 - GetSystemMetrics(SM_CYFULLSCREEN)/2 * GLOBALSIZE,
        //GetSystemMetrics(SM_CXFULLSCREEN) * GLOBALSIZE,
        //GetSystemMetrics(SM_CYFULLSCREEN) * GLOBALSIZE,
        //grounddc, 0, 0, 1366, 693, 1)) printf ("drawing error\n");
        //Etno.draw(1);
        txClear();
        Etno.Move(i);
        Etno.control(4, i);
        txSleep(10);
        if (GetAsyncKeyState (VK_PRIOR)) GLOBALSIZE += 0.1;
        if (GetAsyncKeyState (VK_NEXT))  GLOBALSIZE -= 0.1;
        printf ("x %d y %d\n", ROUND(txGetExtentX()), ROUND(txGetExtentY()));
        }
    txDeleteDC(grounddc);
    return 0;
    }



void StartMenu()
    {
    }

