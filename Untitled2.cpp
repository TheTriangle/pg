 //{===========================================================================
 //              $Copyright: (C) Ded (Ilya Dedinsky, http://txlib.ru) <mail@txlib.ru> $
 //}===========================================================================

 #include "classes.h"

 int main()
     {
     txCreateWindow (800, 600);

     // Загружаем изображения один раз, в начале программы
    HDC etnodc = txLoadImage ("Etnograph.bmp");
    if (!etnodc) printf ("cannot load etno.bmp");

    RectangleUnit Etno (etnodc, 64, 64, 100, 100, 64, 64, 100);
    if (Etno.draw(0, 0, 1) == 0) printf ("drawing error");
     return 0;
     }
