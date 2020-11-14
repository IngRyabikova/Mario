#include "TXLib.h"
#include "dirent.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    txCreateWindow(800, 600);
    txSetColor(TX_BLACK);

    int x = 100;
   setlocale(LC_ALL, "Russian");
   DIR *dir;
   struct dirent *ent;
   if ((dir = opendir (".")) != NULL) {
     /* print all the files and directories within directory */
     while ((ent = readdir (dir)) != NULL) {
       string str = ent->d_name;
       str = "" + str;

       if (str.find(".txt") != -1)
       {
           txRectangle(x, 200, x + 50, 250);
           txDrawText(x, 200, x + 50, 250, ent->d_name);

           x = x + 100;
       }

}

     closedir (dir);
}

return 0;

}
