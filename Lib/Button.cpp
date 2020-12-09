///\file Button.cpp
///\brief Про кнопки

#include "TXLib.h"

///Структура "кнопка"
struct Button
{
    int x;
    int y;
    const char* text;

    ///Адрес картинки, связанной с кнопкой
    string address;
    ///Картинка
    HDC object;
};

///Функция "рисование кнопки"
void drawButton(int x,int y,const char* text)
{
    txSetColour(TX_BLACK);
    txRectangle(x,y,x + 200,y + 80);
    txSelectFont("ARIAL", 40);
    txDrawText(x,y,x + 200,y + 80,text);
}
