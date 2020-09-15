#include "TXLib.h"

bool click(int x1, int y1, int x2, int y2)
{
    if (txMouseX() > x1 &&
        txMouseX() < x2 &&
        txMouseY() < y2)
    {
          return true;

    }
    else
        return false;
}






int main()
{

    txCreateWindow(1280,720);


    HDC kirpich     = txLoadImage("Картинки\\kirpich.bmp");
    HDC zemlya      = txLoadImage("Картинки\\zemlya.bmp");
    HDC truba       = txLoadImage("Картинки\\truba.bmp");

    while (true)

    {
        txBegin();
        txClear();


        txSetColor(TX_WHITE);
        txSetFillColor(TX_WHITE);
        txRectangle(0,0,1280,720);

        txSetColor(TX_BLACK);
        txRectangle(530,340,750,245);
        txDrawText(530,340,750,245, "Играть");

        if (click(530,340,750,245))



        txSetColor(TX_BLACK);
        txRectangle(530,435,750,340);
        txDrawText(530,435,750,340, "Выход");



                    txBitBlt(txDC(),0,0,
                            60, 60,
                            truba);




        txSleep(15);
        txEnd();
    }







    return 0;
    }

