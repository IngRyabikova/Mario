///\file Button.cpp
///\brief ��� ������

#include "TXLib.h"

///��������� "������"
struct Button
{
    int x;
    int y;
    const char* text;

    ///����� ��������, ��������� � �������
    string address;
    ///��������
    HDC object;
};

///������� "��������� ������"
void drawButton(int x,int y,const char* text)
{
    txSetColour(TX_BLACK);
    txRectangle(x,y,x + 200,y + 80);
    txSelectFont("ARIAL", 40);
    txDrawText(x,y,x + 200,y + 80,text);
}
