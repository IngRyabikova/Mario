#include "TXLib.h"

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
    pic[0] = {1300, 250, 60, 60, txLoadImage ("Картинки/kirpich.bmp"), false};
    pic[1] = {1300, 400, 60, 60, txLoadImage ("Картинки/вопрос.bmp"), false};
    pic[2] = {1300, 550, 60, 120, txLoadImage ("Картинки/truba.bmp"), false};
    pic[3] = {1300, 250, 60, 60, txLoadImage ("Картинки/money.bmp"), false};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();



        txSetColor(TX_WHITE);
        txSetFillColor(TX_WHITE);
        txRectangle(0,0,1280,720);

        txSetColor(TX_BLACK);
        drawButton(1050,1, "Кирпич");
        drawButton(1050,110, "Вопрос");
        drawButton(1050,220, "Труба");
        drawButton(1050,330, "Деньги");



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

