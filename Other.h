
bool myAlphaBlend (HDC dest, double xDest, double yDest, double width1, double height1,
                   HDC src,  double xSrc /*= 0*/, double ySrc /*= 0*/, double width2, double height2, double alpha /*= 1.0*/)
    {
    _TX_IF_TXWINDOW_FAILED        return false;
    _TX_IF_ARGUMENT_FAILED (dest) return false;
    _TX_IF_ARGUMENT_FAILED (src)  return false;

    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE) ROUND (alpha * 255), AC_SRC_ALPHA };
    return (Win32::AlphaBlend)?
        txGDI (!!(Win32::AlphaBlend (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
                                     src,  ROUND (xSrc),  ROUND (ySrc),  ROUND (width2), ROUND (height2), blend)))
    :
        txGDI (!!(Win32::BitBlt     (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
                                     src,  ROUND (xSrc),  ROUND (ySrc),  SRCCOPY))), false;
    }

int returndirection (int amount, double gangle)
    {
    double angle = gangle / DEGREEMODIFIER;
    double sector = 360/amount;
    for (int i = 0; i < amount; i++)
        {
        if ((i + 0.5) * sector > 180)
            {
            if (angle >= (i - 0.5) * sector
         && angle < -180 + ((int)((i + 0.5) * sector) % 180)) return i;
            }
        else
            {
            if (angle >= (i - 0.5) * sector
         && angle < (i + 0.5) * sector) return i;
            }
        }
    }

