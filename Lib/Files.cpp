#include "TXLib.h"
#include <fstream>
#include <iostream>
#include "dirent.h"
#include "windows.h"
using namespace std;

int ReadFiles(Picture* gamePics, int n_gamePicss)
{
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

    return n_gamePicss;
}
