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

    //������� ��� � ��������

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
    const char* PAGE = "����� ����";
    int points = 0;


    //������� ������� �������� (0)
    const int COUNT_BTN = 5;
    Button btn[COUNT_BTN];
    btn[0] = {1050,0,   "������",   "��������/kirpich.bmp", txLoadImage ("��������/kirpich.bmp")};
    btn[1] = {1050,110, "������",   "��������/������.bmp", txLoadImage ("��������/������.bmp")};
    btn[2] = {1050,220, "�����",    "��������/truba.bmp", txLoadImage ("��������/truba.bmp")};
    btn[3] = {1050,330, "������",   "��������/money.bmp", txLoadImage ("��������/money.bmp")};
    btn[4] = {1050,440, "�����",    "��������/fire.bmp", txLoadImage ("��������/fire.bmp")};



    Person pers = {100, 150, -10, 100, 0, txLoadImage("��������/HeroLeft.bmp"), txLoadImage("��������/HeroRight.bmp"), txLoadImage("��������/HeroLeft.bmp")};


    Picture gamePics[100];
    int n_gamePicss = 0;
    string strokaX;
    string strokaY;
    string address;

    //�������� ������ ������
    ifstream file("2.txt");
    while (file.good())
    {
        //������1 (x)
        getline(file, strokaX);
        gamePics[n_gamePicss].x = atoi(strokaX.c_str());


        //������2 (y)
        getline(file, strokaY);
        gamePics[n_gamePicss].y = atoi(strokaY.c_str());


        //������3 (�����)
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

        if (PAGE == "����� ����")
        {
            txSetFillColor(TX_WHITE);
            txClear();
            txSetColor(RGB(115,115,115));
            txSetFillColor(RGB(115,115,115));
            txRectangle(0, 500, 1500, 800);

            //�������� � �����
            for (int i = 0; i < n_gamePicss; i++)
                if(gamePics[i].visible)
                    txBitBlt(txDC(), gamePics[i].x, gamePics[i].y, 250, 160, gamePics[i].object);

            for (int i = 0; i < n_pics; i++)
            {
                if(pic[i].visible && pic[i].address == "��������/kirpich.bmp")
                {
                    txSetColor(RGB(115,115,115));
                    txSetFillColor(RGB(115,115,115));
                    txRectangle(pic[i].x, pic[i].y, pic[i].x + 60, pic[i].y + 60);
                }

                if(pic[i].visible && pic[i].address == "��������/money.bmp")
                {
                    txSetColor(RGB(245,136,46));
                    txSetFillColor(RGB(245,136,46));
                    txRectangle(pic[i].x, pic[i].y, pic[i].x + 60, pic[i].y + 60);
                }

                if(pic[i].visible && pic[i].address == "��������/fire.bmp")
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
                    pic[i].address == "��������/money.bmp")
                {
                    pic[i].visible = false;
                    points = points + 20;
                }

            }

            txSetColor(TX_BLACK);
            txDrawText(1050, 550, 1250, 650, "����� ���������");


            txSelectFont("Arial", 16);
            txSetFillColor (TX_GRAY);
            txRectangle (0, txGetExtentY() - 40, txGetExtentX(), txGetExtentY());

            txSetColor (TX_WHITE);
            char stroka [100];
            sprintf(stroka, "�����: %d", points);
            txDrawText (30, txGetExtentY() - 40, 200, txGetExtentY(), stroka);


            Win32::TransparentBlt (txDC(), pers.x - 50, pers.y - 50, 100, 100, pers.person, 536 * pers.frame, 0, 536, 422, TX_WHITE);
            pers.movePerson();

            if (txMouseButtons() == 1 &&
                txMouseX() > 1050 &&  txMouseX() < 1250 &&
                txMouseY() > 550 &&  txMouseY() < 650)
            {
                PAGE = "����� ���������";
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
        if (PAGE == "����� ���������")
        {
            txDrawText(1050, 550, 1250, 650, "����� ����");

            txSetColor(TX_BLACK);
            for (int i = 0; i < COUNT_BTN; i = i + 1)
                drawButton(btn[i].x,btn[i].y, btn[i].text);

            if (txMouseButtons() == 1 &&
                txMouseX() > 1050 &&  txMouseX() < 1250 &&
                txMouseY() > 550 &&  txMouseY() < 650)
            {
                PAGE = "����� ����";
                txSleep(200);
            }



            //���� ����� ������ �� ������ ������
            for (int i = 0; i < COUNT_BTN; i = i + 1)
            if (txMouseButtons() == 1 &&
                txMouseX() > btn[i].x &&  txMouseX() < btn[i].x + 230 &&
                txMouseY() > btn[i].y &&  txMouseY() < btn[i].y + 110)
            {
                //�������� ������
                active_pic = n_pics;
                pic[n_pics] = {300, 250,  60, 60, btn[i].address, btn[i].object,true};
                n_pics = n_pics + 1;
                txSleep(50);
                //������� ����� �������� � ��������
            }


            for (int i = 0; i < n_pics; i++)
                if(pic[i].visible)
                    txBitBlt(txDC(), pic[i].x, pic[i].y, 250, 160, pic[i].object);


            //����� �������� ��������
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
            //�������� �������� ������
            if(active_pic >= 0 && txMouseButtons() == 1 && txMouseX() < 1000)
            {
                pic[active_pic].x = txMouseX() - 20;
                pic[active_pic].y = txMouseY() - 20;
            }

            //��������� �����
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


    //������� ����
    ofstream file2("1.txt");

    //��������� �� ���� ���������
    for (int i = 0; i < n_pics; i++)
    {
        //� ��������� ��� ���
        file2 << pic[i].x << endl;

        file2 << pic[i].y << endl;

        file2 << pic[i].address << endl;
    }

    file2.close();


    for (int i = 0; i < n_pics; i++)
        txDeleteDC(pic[i].object);

    return 0;
}
