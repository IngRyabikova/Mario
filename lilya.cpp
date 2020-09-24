#include "TXLib.h"

#include "Person.cpp"


struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC object;
    bool visible;
};

struct Button
{
    int x;
    int y;
    const char text[];
};

void drawButton(int x,int y,const char text[])
{
    txSetColour(TX_BLACK);
    txRectangle(x,y,x + 200,y + 100);
    txSelectFont("ARIAL", 40);
    txDrawText(x,y,x + 200,y + 100,text);
}

int main()
{

    txCreateWindow(1280,720);
    txTextCursor (false);

      Picture pic[100];
    pic[0] = {1300, 250, 60, 60, txLoadImage ("Êàðòèíêè/kirpich.bmp"), false};
    pic[1] = {1300, 400, 60, 60, txLoadImage ("Êàðòèíêè/âîïðîñ.bmp"), false};
    pic[2] = {1300, 550, 60, 120, txLoadImage ("Êàðòèíêè/truba.bmp"), false};
    pic[3] = {1300, 250, 60, 60, txLoadImage ("Êàðòèíêè/money.bmp"), false};


    Person pers = {100, 150, 100, 0, txLoadImage("Êàðòèíêè/HeroLeft.bmp"), txLoadImage("Êàðòèíêè/HeroRight.bmp"), txLoadImage("Êàðòèíêè/HeroLeft.bmp")};
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();


            Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
        pers.movePerson();

        txSetColor(TX_BLACK);
        drawButton(1050,1, "Êèðïè÷");
        drawButton(1050,110, "Âîïðîñ");
        drawButton(1050,220, "Òðóáà");
        drawButton(1050,330, "Äåíüãè");



        if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 1 &&  txMouseY() < 110)
        {
        pic[0].visible = true;


         txSleep(50);
         }

         if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 110 &&  txMouseY() < 220)
        {
        pic[1].visible = true;


         txSleep(50);
         }

         if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 220 &&  txMouseY() < 330)
        {
        pic[2].visible = true;
        }

        if (txMouseButtons() == 1 &&
        txMouseX() > 1050 &&  txMouseX() < 1280 &&
        txMouseY() > 330 &&  txMouseY() < 440)
        {
        pic[3].visible = true;


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
      
         for (int i = 0; i <= 3; i++)
            if(pic[i].visible)
                txBitBlt(txDC(),i*200,1,250,160,pic[i].object);


        txSleep(15);
        txEnd();
    }





        for (int i = 0; i <= 3; i++)
        txDeleteDC(pic[i].object);

    return 0;
    }

