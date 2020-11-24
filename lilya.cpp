#include "TXLib.h"
#include "Person.cpp"
#include <fstream>
#include <iostream>
#include "dirent.h"
#include "windows.h"
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

    int central_x = 0;

    Picture pic[100];
    int n_pics = 0;
    int active_pic = -1;
    const char* PAGE = "Режим меню";
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


        if(PAGE == "Режим меню")
        {
            int x = 100;
            int y = 200;
            setlocale(LC_ALL, "Russian");
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir (".")) != NULL) {
            /* print all the files and directories within directory */
                while ((ent = readdir (dir)) != NULL) {
                    string str = ent->d_name;
                    str = "" + str;

                    if (str.find(".txt") != -1)
                    {
                        Win32::RoundRect(txDC(), x, y, x + 100, y + 100, 30, 30);
                        txDrawText(x, y, x + 100, y + 100, ent->d_name);

                        if (txMouseButtons() == 1 &&
                            txMouseX() > x &&  txMouseX() < x + 100 &&
                            txMouseY() > y &&  txMouseY() < y + 200)
                        {
                            PAGE = "Режим игры";
                            txSleep(200);
                        }



                        x = x + 100;

                        if (x > 700)
                        {
                            y = y + 150;
                            x = 100;
                        }
                    }

                }

                closedir (dir);
            }

        }
        if (PAGE == "Режим игры")
        {
            txSetFillColor(TX_WHITE);
            txClear();


            if (pers.x >= 1500)
            {
                txMessageBox("Ты победил");
                break;
            }


            //Рисование квадратов
            for (int i = 0; i < n_gamePicss; i++)
            {
                if(gamePics[i].visible && gamePics[i].address == "Картинки/kirpich.bmp")
                {
                    txSetColor(RGB(115,115,115));
                    txSetFillColor(RGB(115,115,115));
                    txRectangle(gamePics[i].x, gamePics[i].y, gamePics[i].x + 60, gamePics[i].y + 60);
                }

                if(gamePics[i].visible && gamePics[i].address == "Картинки/money.bmp")
                {
                    txSetColor(RGB(245,136,46));
                    txSetFillColor(RGB(245,136,46));
                    txRectangle(gamePics[i].x - central_x, gamePics[i].y, gamePics[i].x + 60, gamePics[i].y + 60);
                }

                if(gamePics[i].visible && gamePics[i].address == "Картинки/fire.bmp")
                {
                    txSetColor(RGB(255,36,36));
                    txSetFillColor(RGB(255,36,36));
                    txRectangle(gamePics[i].x - central_x, gamePics[i].y, gamePics[i].x + 60, gamePics[i].y + 60);
                }

                if(gamePics[i].visible && gamePics[i].address == "Картинки/truba.bmp")
                {
                    txSetColor(RGB(128,255,128));
                    txSetFillColor(RGB(128,255,128));
                    txRectangle(gamePics[i].x - central_x, gamePics[i].y, gamePics[i].x + 60, gamePics[i].y + 60  );
                }

                if(gamePics[i].visible && gamePics[i].address == "Картинки/vopros.bmp")
                {
                    txSetColor(RGB(255,128,64));
                    txSetFillColor(RGB(255,128,64));
                    txRectangle(gamePics[i].x - central_x, gamePics[i].y, gamePics[i].x + 60, gamePics[i].y + 60);
                }


                if (gamePics[i].x      < pers.x + 60 and
                    gamePics[i].x + 60 > pers.x and
                    gamePics[i].y      < pers.y + 70 and
                    gamePics[i].visible and
                    gamePics[i].y + 60 > pers.y and
                    gamePics[i].address == "Картинки/money.bmp")
                {
                    gamePics[i].visible = false;
                    points = points + 20;
                }

            }

            //Игровая логика
            pers.movePerson();

            if (pers.x < 100)
            {
                central_x = central_x - 5;
            }

            if (pers.x > 900)
            {
                central_x = central_x + 5;
            }

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


            txSetFillColor(TX_WHITE);
            txClear();
            txSetColor(RGB(115,115,115));
            txSetFillColor(RGB(115,115,115));
            txRectangle(0, 500, 1500, 800);

            txSetColor(TX_BLACK);
            txDrawText(1050, 550, 1250, 650, "Режим редактора");


            txSelectFont("Arial", 16);
            txSetFillColor (TX_GRAY);
            txRectangle (0, txGetExtentY() - 40, txGetExtentX(), txGetExtentY());

            txSetColor (TX_WHITE);
            char stroka [100];
            sprintf(stroka, "Очков: %d", points);
            txDrawText (30, txGetExtentY() - 40, 200, txGetExtentY(), stroka);

            Win32::TransparentBlt (txDC(), pers.x - 50 - central_x, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);

            //Рисование кирпичей, монет и т.д.
            for (int i = 0; i < n_gamePicss; i++)
                if(gamePics[i].visible)
                    txBitBlt(txDC(), gamePics[i].x - central_x, gamePics[i].y, 250, 160, gamePics[i].object);

        }
        if (PAGE == "Режим редактора")
        {
            txSetFillColor(TX_YELLOW);
            Win32::RoundRect (txDC(), 200, 600, 300, 700, 30, 30);
            Win32::RoundRect (txDC(), 900, 600, 1000, 700, 30, 30);
            if (txMouseButtons() == 1 &&
                txMouseX() > 200 &&  txMouseX() < 300 &&
                txMouseY() > 600 &&  txMouseY() < 700)
            {
                central_x = central_x + 5;
            }

            if (txMouseButtons() == 1 &&
                txMouseX() > 900 &&  txMouseX() < 1000 &&
                txMouseY() > 600 &&  txMouseY() < 700)
            {
                central_x = central_x - 5;
            }

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
                    txBitBlt(txDC(), pic[i].x - central_x, pic[i].y, 250, 160, pic[i].object);


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


        //Открыть файл
        txRectangle(2,2, 200, 60);
        txDrawText(2,2,200,60, "Открыть", 5);
        if (txMouseButtons() == 1 &&
                txMouseX() > 2 &&  txMouseY() > 2 &&
                txMouseX() < 200 &&  txMouseY() < 60)
        {
            OPENFILENAME ofn;			// структура стандартного диалогового окна
            char szFile[260] = {0};			// буфер для имени файла

            // Инициализация OPENFILENAME
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = txWindow();
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "Text\0*.TXT\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


            // Покажем диалоговое окно Открыть (Open).

            if (GetSaveFileName(&ofn))
            {
                string fileName = ofn.lpstrFile;

                ofstream file2(fileName);

                for (int i = 0; i < n_pics; i++)
                {

                    file2 << pic[i].x << endl;

                    file2 << pic[i].y << endl;

                    file2 << pic[i].address << endl;
                }

                file2.close();

            }    //return 0;
        }


    }


        txSleep(15);
        txEnd();
    }


    //Пробежать по всем картинкам




    for (int i = 0; i < n_pics; i++)
        txDeleteDC(pic[i].object);

    return 0;
}
