#include "TXLib.h"

struct Person
{
    int x;
    int y;
    float vy;
    int personLife;
    int frame;
    HDC personLeft;
    HDC personRight;
    HDC person;

    //Какая из двух функций движения используется?
    void movePerson()
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            x = x - 3;
            person = personLeft;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            x = x + 3;
            person = personRight;
        }
    }
};

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
            if (txGetPixel(x, y) == RGB(115,115,115))
            {
                pers->y=pers->y - 9;
                break;
            }

            if (txGetPixel(x, y) == RGB(128,255,128))
            {
                pers->y=pers->y - 9;
                break;
            }

            if (txGetPixel(x, y) == RGB(255,128,64))
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


void movePerson(Person *pers)
{
	//pers->personLife = pers->personLife - 1;
     if (pers->x<0 ||
        pers->x + 100> txGetExtentX()||
        pers->y<0)
    {
        pers->x=100;
        pers->y=100;
    }



    if (GetAsyncKeyState('D'))
    {
        pers->x += 5;
        pers->person = pers->personRight;
        pers->frame++;
    }
    else if (GetAsyncKeyState('A'))
    {
        pers->x -= 5;
        pers->person = pers->personLeft;
        pers->frame++;
    }

    if (GetAsyncKeyState(VK_SPACE) &&
        pers->y > 100)
    {
        pers->y = pers->y - 25;
    }

    if (pers->frame >= 7)
    {
        pers->frame = 0;
    }
}
