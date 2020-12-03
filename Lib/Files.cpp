///\file Files.cpp
///\brief Про сохранение в файлы
#include "TXLib.h"
#include "Picture.cpp"
#include <fstream>
#include <iostream>
#include "dirent.h"
#include "windows.h"
using namespace std;

///Функция "Сохранение в файл"
void saveToFile(int n_pics, Picture* pic)
{
    OPENFILENAME ofn;			/// структура стандартного диалогового окна
    char szFile[260] = {0};			/// буфер для имени файла

    /// Инициализация OPENFILENAME
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


    /// Покажем диалоговое окно Открыть (Open).
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
    }
}

int ReadFiles(Picture* gamePics, int n_gamePicss, string fileName)
{
    n_gamePicss = 0;
    string strokaX;
    string strokaY;
    string address;

    ///Прочитал первую строку
    ifstream file(fileName);

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

    return n_gamePicss;
}
