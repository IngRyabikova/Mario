#include "TXLib.h"
#include <fstream>
#include <iostream>
#include "dirent.h"
#include "windows.h"
using namespace std;

void saveToFile(int n_pics, Picture* pic)
{
    OPENFILENAME ofn;			// ��������� ������������ ����������� ����
    char szFile[260] = {0};			// ����� ��� ����� �����

    // ������������� OPENFILENAME
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


    // ������� ���������� ���� ������� (Open).
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
