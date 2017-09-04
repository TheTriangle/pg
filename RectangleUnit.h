

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

