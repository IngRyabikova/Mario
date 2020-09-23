#include "TXLib.h"

#include "Person.cpp"







int main()
{

    txCreateWindow(1280,720);

//    player
    HDC kirpich     = txLoadImage("Картинки\\kirpich.bmp");
    HDC zemlya      = txLoadImage("Картинки\\zemlya.bmp");
    HDC truba       = txLoadImage("Картинки\\truba.bmp");
    bool drawkirpich = false;
    bool drawzemlya = false;
    bool drawtruba = false;


    Person pers = {100, 150, 100, 0, txLoadImage("Картинки/HeroLeft.bmp"), txLoadImage("Картинки/HeroRight.bmp"), txLoadImage("Картинки/HeroLeft.bmp")};
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();


            Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
        pers.movePerson();

        txSetColor(TX_BLACK);
        txRectangle(1050,1,1280,110);
        txDrawText(1050,1,1280,110, "Кирпич");

        txSetColor(TX_BLACK);
        txRectangle(1050,110,1280,220);
        txDrawText(1050,110,1280,220, "Земля");

        txSetColor(TX_BLACK);
        txRectangle(1050,220,1280,330);
        txDrawText(1050,220,1280,330, "Труба");

        if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 1 &&  txMouseY() < 110)
        {
        drawkirpich = true;


         txSleep(50);
         }

         if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 110 &&  txMouseY() < 220)
        {
        drawzemlya = true;


         txSleep(50);
         }

         if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 220 &&  txMouseY() < 330)
        {
        drawtruba = true;


         txSleep(50);
         }




        if (txMouseButtons() == 1 &&
        txMouseX() > 1 &&  txMouseX() < 250 &&
        txMouseY() > 1 &&  txMouseY() < 160)
        {


         txSleep(50);
         }


        if (txMouseButtons() == 1 &&
        txMouseX() > 270 &&  txMouseX() < 400 &&
        txMouseY() > 1 &&  txMouseY() < 160)
        {



         txSleep(50);
         }

        if (txMouseButtons() == 1 &&
        txMouseX() > 530 &&  txMouseX() < 550 &&
        txMouseY() > 1 &&  txMouseY() < 160)
        {



         txSleep(50);
         }

         if(drawkirpich)
         txBitBlt(txDC(),1,1,250, 160,kirpich);

         if(drawzemlya)
         txBitBlt(txDC(),270,1, 400,160,zemlya);

         if(drawtruba)
         txBitBlt(txDC(),530,1,550, 160,truba);


//

        txSleep(15);
        txEnd();
    }







    return 0;
    }

