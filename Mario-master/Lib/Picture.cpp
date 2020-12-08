///\file Picture.cpp
///\brief Про картинку
#pragma once
#include "TXLib.h"

///Структура "картинка"
struct Picture
{
    int x;
    int y;
    int width;
    int height;
    ///Адрес картинки, связанной с картинкой
    string address;
    HDC object;
    bool visible;
};

///Функция "рисование картинок"
void drawAllPics(int n_pics, Picture* pic, int central_x)
{
    for (int i = 0; i < n_pics; i++)
        if(pic[i].visible)
            txBitBlt(txDC(), pic[i].x - central_x, pic[i].y, 250, 160, pic[i].object);
}
