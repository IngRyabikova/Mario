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



    HDC object;

    //Хранить еще и картинку

};

void drawButton(int x,int y,const char* text)
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
    int n_pics = 0;
    int active_pic = -1;

    //Хранить сколько картинок (0)
    const int COUNT_BTN = 5;
    Button btn[COUNT_BTN];
    btn[0] = {1050,0,   "Кирпич",   txLoadImage ("Картинки/kirpich.bmp")};
    btn[1] = {1050,110, "Вопрос",   txLoadImage ("Картинки/вопрос.bmp")};
    btn[2] = {1050,220, "Труба",    txLoadImage ("Картинки/truba.bmp")};
    btn[3] = {1050,330, "Деньги",   txLoadImage ("Картинки/money.bmp")};
    btn[4] = {1050,440, "Огонь",    txLoadImage ("Картинки/fire.bmp")};



    Person pers = {100, 150, 100, 0, txLoadImage("Картинки/HeroLeft.bmp"), txLoadImage("Картинки/HeroRight.bmp"), txLoadImage("Картинки/HeroLeft.bmp")};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();

        Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
        pers.movePerson();

        txSetColor(TX_BLACK);
        for (int i = 0; i < COUNT_BTN; i = i + 1)
            drawButton(btn[i].x,btn[i].y, btn[i].text);


        //Если нажал мышкой на кнопку кирпич
         for (int i = 0; i < COUNT_BTN; i = i + 1)
        if (txMouseButtons() == 1 &&
            txMouseX() > btn[i].x &&  txMouseX() < btn[i].x + 230 &&
            txMouseY() > btn[i].y &&  txMouseY() < btn[i].y + 110)
        {
            //Рисовать кирпич
            active_pic = n_pics;
            pic[n_pics] = {300, 250,  60, 60, btn[i].object,true};
            n_pics = n_pics + 1;
            txSleep(50);
            //Создать новую картинку с кирпичом
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


        if (GetAsyncKeyState(VK_SPACE))
        {
            for (int i = 0; i < n_pics; i++)
            {
                pic[active_pic].x = round(pic[active_pic].x/30)*30;
                pic[active_pic].y = round(pic[active_pic].y/30)*30;
            }
        }

        txSleep(15);
        txEnd();
    }





    for (int i = 0; i < n_pics; i++)
        txDeleteDC(pic[i].object);

    return 0;
}
