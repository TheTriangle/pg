
const int BTR_MOUSEON = 0;       //ButtonTestResult
const int BTR_PRESSED = 1;
const int BTR_NOTHING = 2;

class button
    {
    private:
    HDC nothingdc;
    HDC mouseondc;
    HDC activedc;
    POINT cords;
    POINT size;
    void (*bfunction)();
    public:
    int getBtrMon()
        {
        return BTR_MOUSEON;
        }
    int getBtrPrs()
        {
        return BTR_PRESSED;
        }
    int getBtrNot()
        {
        return BTR_NOTHING;
        }
    int testButton ()
        {
        if (txMouseX() > cords.x && txMouseX() < cords.x + size.x &&
            txMouseY() > cords.y && txMouseY() < cords.y + size.y)
            {
            if (GetAsyncKeyState (VK_LBUTTON))
                {
                bfunction;
                return BTR_PRESSED;
                }
            else
                {
                activedc = mouseondc;
                return BTR_MOUSEON;
                }
            }
        else
            {
            activedc = nothingdc;
            return BTR_NOTHING;
            }
        }
    void drawbutton (double alpha)
        {
        txAlphaBlend (txDC(), cords.x, cords.y, size.x, size.y, activedc, 0, 0, alpha);
        }
    button (double x, double y, double x1, double y1, void (*gfunction)(), HDC gndc, HDC modc)
        {
        double lowerx = (x <= x1)? x:x1;
        double higherx = (x < x1)? x1:x;
        double lowery = (y <= y1)? y:y;
        double highery = (y < y1)? y1:y;
        cords = {lowerx, lowery};
        size = {higherx - lowerx, highery - lowery};
        bfunction = gfunction;
        nothingdc = gndc;
        mouseondc = modc;
        activedc = gndc;
        }
    };

void DoNothing()
    {}
