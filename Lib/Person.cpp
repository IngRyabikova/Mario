///\file Person.cpp
///\brief ��� ���������
#include "TXLib.h"

///��������� "��������"
struct Person
{

    int x;
    int y;
    ///�������� �������� �� y
    float vy;
    int personLife;
    int frame;
    HDC personLeft;
    HDC personRight;
    HDC person;
    int oldX;
    int oldY;

    ///������� ��������
    void movePerson()
    {
        oldX = x;
        oldY = y;
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

///������� �����
void gravityPerson(Person *pers, int central_x)
{
    pers->vy = pers->vy + 0.5;
    pers->y = pers->y + pers->vy;
    if (pers->y > 500)
        pers->y = 500;


    if (pers->vy > 10)
        pers->vy = 10;

    bool stolknulsa = false;
    bool sverhu = false;

    int x = pers->x - central_x - 30;
    while (x < pers->x - central_x + 30)
    {
        int y = pers->y - 30;
        while (y < pers->y + 30)
        {
            //������
            if (txGetPixel(x, y) == RGB(115,115,115))
            {
                //pers->x=pers->x - 9;
                stolknulsa = true;
                if (y >= pers->y + 20)
                    sverhu = true;
            }


            if (txGetPixel(x, y) == RGB(128,255,128)) //���
            {
                stolknulsa = true;
                if (y >= pers->y + 20)
                    sverhu = true;
                //break;
            }

            if (txGetPixel(x, y) == RGB(255,128,64))
            {
                stolknulsa = true;
                if (y >= pers->y + 20)
                    sverhu = true;
                //break;
            }

             if (txGetPixel(x, y) == RGB(100,100,100))
             {
                stolknulsa = true;
                if (y >= pers->y + 20)
                    sverhu = true;
                //break;

             }

            y = y + 10;
        }
        x = x + 10;
    }

    if (stolknulsa)
    {
        if (!sverhu)
            pers->x = pers->oldX;
        pers->y = pers->oldY;
    }
}
