#include "TXLib.h"
#include "Person.cpp"
#include <fstream>
using namespace std;

struct Picture
{
    int x;
    int y;
    int width;
    int height;
    string address;
    HDC object;
    bool visible;
};

struct Button
{
    int x;
    int y;
    const char* text;


    string address;
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
    const char* PAGE = "Режим игры";
    int points = 0;


    //Хранить сколько картинок (0)
    const int COUNT_BTN = 5;
    Button btn[COUNT_BTN];
    btn[0] = {1050,0,   "Кирпич",   "Картинки/kirpich.bmp", txLoadImage ("Картинки/kirpich.bmp")};
    btn[1] = {1050,110, "Вопрос",   "Картинки/вопрос.bmp", txLoadImage ("Картинки/вопрос.bmp")};
    btn[2] = {1050,220, "Труба",    "Картинки/truba.bmp", txLoadImage ("Картинки/truba.bmp")};
    btn[3] = {1050,330, "Деньги",   "Картинки/money.bmp", txLoadImage ("Картинки/money.bmp")};
    btn[4] = {1050,440, "Огонь",    "Картинки/fire.bmp", txLoadImage ("Картинки/fire.bmp")};



    Person pers = {100, 150, -10, 100, 0, txLoadImage("Картинки/HeroLeft.bmp"), txLoadImage("Картинки/HeroRight.bmp"), txLoadImage("Картинки/HeroLeft.bmp")};


    Picture gamePics[100];
    int n_gamePicss = 0;
    string strokaX;
    string strokaY;
    string address;

    //Прочитал первую строку
    ifstream file("2.txt");
    while (file.good())
    {
        //Строка1 (x)
        getline(file, strokaX);
        gamePics[n_gamePicss].x = atoi(strokaX.c_str());


        //Строка2 (y)
        getline(file, strokaY);
        gamePics[n_gamePicss].y = atoi(strokaY.c_str());


        //Строка3 (адрес)
        getline(file, address);
        gamePics[n_gamePicss].address = address;
        gamePics[n_gamePicss].object = txLoadImage(address.c_str());

        gamePics[n_gamePicss].width = 60;
        gamePics[n_gamePicss].height = 60;
        gamePics[n_gamePicss].visible = true;
        n_gamePicss = n_gamePicss + 1;
    }

    file.close();

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();

        txSetColor(TX_BLACK, 5);
        Win32::RoundRect (txDC(), 1050, 550, 1250, 650, 30, 30);

        if (PAGE == "Режим игры")
        {
            txSetFillColor(TX_WHITE);
            txClear();
            txSetColor(RGB(115,115,115));
            txSetFillColor(RGB(115,115,115));
            txRectangle(0, 500, 1500, 800);

            //Картинки с файла
            for (int i = 0; i < n_gamePicss; i++)
                if(gamePics[i].visible)
                    txBitBlt(txDC(), gamePics[i].x, gamePics[i].y, 250, 160, gamePics[i].object);

            for (int i = 0; i < n_pics; i++)
            {
                if(pic[i].visible && pic[i].address == "Картинки/kirpich.bmp")
                {
                    txSetColor(RGB(115,115,115));
                    txSetFillColor(RGB(115,115,115));
                    txRectangle(pic[i].x, pic[i].y, pic[i].x + 60, pic[i].y + 60);
                }

                if(pic[i].visible && pic[i].address == "Картинки/money.bmp")
                {
                    txSetColor(RGB(245,136,46));
                    txSetFillColor(RGB(245,136,46));
                    txRectangle(pic[i].x, pic[i].y, pic[i].x + 60, pic[i].y + 60);
                }

                if(pic[i].visible && pic[i].address == "Картинки/fire.bmp")
                {
                    txSetColor(RGB(255,36,36));
                    txSetFillColor(RGB(255,36,36));
                    txRectangle(pic[i].x, pic[i].y, pic[i].x + 60, pic[i].y + 60);
                }


                if (pic[i].x      < pers.x + 60 and
                    pic[i].x + 60 > pers.x and
                    pic[i].y      < pers.y + 70 and
                    pic[i].visible and
                    pic[i].y + 60 > pers.y and
                    pic[i].address == "Картинки/money.bmp")
                {
                    pic[i].visible = false;
                    points = points + 20;
                }

            }

            txSetColor(TX_BLACK);
            txDrawText(1050, 550, 1250, 650, "Режим редактора");


            txSelectFont("Arial", 16);
            txSetFillColor (TX_GRAY);
            txRectangle (0, txGetExtentY() - 40, txGetExtentX(), txGetExtentY());

            txSetColor (TX_WHITE);
            char stroka [100];
            sprintf(stroka, "Очков: %d", points);
            txDrawText (30, txGetExtentY() - 40, 200, txGetExtentY(), stroka);


            Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
            pers.movePerson();

            if (txMouseButtons() == 1 &&
                txMouseX() > 1050 &&  txMouseX() < 1250 &&
                txMouseY() > 550 &&  txMouseY() < 650)
            {
                PAGE = "Режим редактора";
                txSleep(200);
            }

            gravityPerson(&pers);



            if (GetAsyncKeyState('J')) {
                pers.vy = -10;
            }

            pers.vy = pers.vy + 0.5;
            pers.y = pers.y + pers.vy;
            if (pers.y > 500)
                pers.y = 500;
        }
        if (PAGE == "Режим редактора")
        {
            txDrawText(1050, 550, 1250, 650, "Режим игры");

            txSetColor(TX_BLACK);
            for (int i = 0; i < COUNT_BTN; i = i + 1)
                drawButton(btn[i].x,btn[i].y, btn[i].text);

            if (txMouseButtons() == 1 &&
                txMouseX() > 1050 &&  txMouseX() < 1250 &&
                txMouseY() > 550 &&  txMouseY() < 650)
            {
                PAGE = "Режим игры";
                txSleep(200);
            }



            //Если нажал мышкой на кнопку кирпич
            for (int i = 0; i < COUNT_BTN; i = i + 1)
            if (txMouseButtons() == 1 &&
                txMouseX() > btn[i].x &&  txMouseX() < btn[i].x + 230 &&
                txMouseY() > btn[i].y &&  txMouseY() < btn[i].y + 110)
            {
                //Рисовать кирпич
                active_pic = n_pics;
                pic[n_pics] = {300, 250,  60, 60, btn[i].address, btn[i].object,true};
                n_pics = n_pics + 1;
                txSleep(50);
                //Создать новую картинку с кирпичом
            }


            for (int i = 0; i < n_pics; i++)
                if(pic[i].visible)
                    txBitBlt(txDC(), pic[i].x, pic[i].y, 250, 160, pic[i].object);


            //Выбор активной картинки
            for (int i = 0; i < n_pics; i++)
            {
                if (txMouseButtons() == 1 &&
                    txMouseX() > pic[i].x &&  txMouseX() < pic[i].x + 60 &&
                    txMouseY() > pic[i].y &&  txMouseY() < pic[i].y + 60)
                {
                    active_pic = i;
                }
            }

            /*if (GetAsyncKeyState(VK_LEFT)  and active_pic >= 0)
                pic[active_pic].x = pic[active_pic].x - 2;
            if (GetAsyncKeyState(VK_RIGHT) and active_pic >= 0)
                pic[active_pic].x = pic[active_pic].x + 2;
            if (GetAsyncKeyState(VK_UP)    and active_pic >= 0)
                pic[active_pic].y = pic[active_pic].y - 2;
            if (GetAsyncKeyState(VK_DOWN)  and active_pic >= 0)
                pic[active_pic].y = pic[active_pic].y + 2;
               */
            //Движение картинки мышкой
            if(active_pic >= 0 && txMouseButtons() == 1 && txMouseX() < 1000)
            {
                pic[active_pic].x = txMouseX() - 20;
                pic[active_pic].y = txMouseY() - 20;
            }

            //Отпустили мышку
            if(txMouseButtons() == 0 && active_pic >= 0)
            {
                pic[active_pic].x = round(pic[active_pic].x/30)*30;
                pic[active_pic].y = round(pic[active_pic].y/30)*30;
                active_pic = -999;
            }


            if (GetAsyncKeyState('B'))
            {
                for (int i = 0; i < n_pics; i++)
                {
                    pic[i].x = round(pic[i].x/60)*60;
                    pic[i].y = round(pic[i].y/60)*60;
                }
            }
        }



        txSleep(15);
        txEnd();
    }


    //Открыть файл
    ofstream file2("1.txt");

    //Пробежать по всем картинкам
    for (int i = 0; i < n_pics; i++)
    {
        //И сохранить вот это
        file2 << pic[i].x << endl;

        file2 << pic[i].y << endl;

        file2 << pic[i].address << endl;
    }

    file2.close();


    for (int i = 0; i < n_pics; i++)
        txDeleteDC(pic[i].object);

    return 0;
}
