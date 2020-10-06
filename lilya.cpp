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
    const char* text;
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

    int active_pic = -1;

    int n_pics = 0;
    Picture pic[100];
    HDC kirp = txLoadImage ("Картинки/kirpich.bmp");
    HDC quest = txLoadImage ("Картинки/вопрос.bmp");
    HDC truba = txLoadImage ("Картинки/truba.bmp");
    HDC money = txLoadImage ("Картинки/money.bmp");

    Button btn1 = {1050,0, "Кирпич"};
    Button btn2 = {1050,110, "Кирпич"};
    Button btn3 = {1050,220, "Кирпич"};
    Button btn4 = {1050,330, "Кирпич"};

    Person pers = {100, 150, 100, 0, txLoadImage("Картинки/HeroLeft.bmp"), txLoadImage("Картинки/HeroRight.bmp"), txLoadImage("Картинки/HeroLeft.bmp")};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
        pers.movePerson();

        txSetColor(TX_BLACK);
        drawButton(1050,1, "Кирпич");
        drawButton(1050,110, "Вопрос");
        drawButton(1050,220, "Труба");
        drawButton(1050,330, "Деньги");



        if (txMouseButtons() == 1 &&
            txMouseX() > btn1.x &&  txMouseX() < btn1.x + 230 &&
            txMouseY() > 1 &&  txMouseY() < 110)
        {
            active_pic = n_pics;
            pic[n_pics] = {300, 250, 60, 60, kirp, true};
            n_pics = n_pics + 1;
            txSleep(50);
        }

        if (txMouseButtons() == 1 &&
            txMouseX() > btn1.x &&  txMouseX() < btn1.x + 230 &&
            txMouseY() > 110 &&  txMouseY() < 220)
        {
            active_pic = n_pics;
            pic[n_pics] = {300, 250, 60, 60, quest, true};
            n_pics = n_pics + 1;
            txSleep(50);
        }

        if (txMouseButtons() == 1 &&
            txMouseX() > btn1.x &&  txMouseX() < btn1.x + 230 &&
            txMouseY() > 220 &&  txMouseY() < 330)
        {
            active_pic = n_pics;
            pic[n_pics] = {300, 250, 60, 60, truba, true};
            n_pics = n_pics + 1;
            txSleep(50);
        }

        if (txMouseButtons() == 1 &&
            txMouseX() > btn1.x &&  txMouseX() < btn1.x + 230 &&
            txMouseY() > 330 &&  txMouseY() < 440)
        {
            active_pic = n_pics;
            pic[n_pics] = {300, 250, 60, 60, money, true};
            n_pics = n_pics + 1;
            txSleep(50);


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

        for (int i = 0; i < n_pics; i++)
            if(pic[i].visible)
                txBitBlt(txDC(), pic[i].x, pic[i].y, 250, 160, pic[i].object);


        if (GetAsyncKeyState(VK_LEFT)  and active_pic >= 0)
            pic[active_pic].x = pic[active_pic].x - 2;
        if (GetAsyncKeyState(VK_RIGHT) and active_pic >= 0)
            pic[active_pic].x = pic[active_pic].x + 2;
        if (GetAsyncKeyState(VK_UP)    and active_pic >= 0)
            pic[active_pic].y = pic[active_pic].y - 2;
        if (GetAsyncKeyState(VK_DOWN)  and active_pic >= 0)
            pic[active_pic].y = pic[active_pic].y + 2;





        txSleep(15);
        txEnd();
    }





    for (int i = 0; i <= 3; i++)
        txDeleteDC(pic[i].object);

    return 0;
}
