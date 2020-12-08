///\file Person.cpp
///\brief Про персонажа
#include "TXLib.h"

///Структура "Персонаж"
struct Person
{

    int x;
    int y;
    ///Скорость движения по y
    float vy;
    int personLife;
    int frame;
    HDC personLeft;
    HDC personRight;
    HDC person;

    ///Функция движения
    void movePerson()
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            x = x - 3;
            person = personLeft;
            frame = frame + 1;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            x = x + 3;
            person = personRight;
            frame = frame + 1;
        }

        if (GetAsyncKeyState(VK_SPACE) &&
            y > 100)
        {
            y = y - 25;
        }

        if (frame >= 7)
        {
            frame = 0;
        }
    }
};

///Функция полёта
void gravityPerson(Person *pers)
{
    if (pers->vy > 10)
        pers->vy = 10;

    int x = pers->x - 40;
    while (x < pers->x + 40)
    {
        int y = pers->y - 40;
        while (y < pers->y + 40)
        {
            if (txGetPixel(x, y) == RGB(115,115,115) &&
                txGetPixel(pers->x, pers->y) != RGB(115,115,115) &&
                txGetPixel(pers->x , pers->y - 40) != RGB(115,115,115))
            {
                pers->y=pers->y + 5;

                break;
            }
            if (txGetPixel(x, y) == RGB(115,115,115) &&
                txGetPixel(pers->x, pers->y) != RGB(115,115,115) &&
                txGetPixel(pers->x + 40 , pers->y != RGB(115,115,115)))
            {
                pers->x=pers->x - 9;

                break;
            }


            if (txGetPixel(x, y) == RGB(128,255,128) &&
                txGetPixel(pers->x, pers->y) != RGB(128,255,128) &&    //Центр
                txGetPixel(pers->x, pers->y + 40) != RGB(128,255,128)) //Низ
            {
                pers->y=pers->y - 9;
                //pers->y=pers->y + 20;
                break;
            }

            if (txGetPixel(x, y) == RGB(255,128,64) &&
                txGetPixel(pers->x, pers->y) != RGB(255,128,64) &&
                txGetPixel(pers->x, pers->y + 40) != RGB(255,128,64))
            {
                pers->y=pers->y - 9;
                break;
            }

             if (txGetPixel(x, y) == RGB(100,100,100))
             {
                //pers ->x=pers->x + 9;
                break;

             }

            y = y + 10;
        }
        x = x + 10;
    }
}
