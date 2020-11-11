#include "TXLib.h"
#include "dirent.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    txCreateWindow(800, 600);
    txSetColor(TX_BLACK);

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
           txRectangle(100, 200, 150, 250);
           txDrawText(100, 200, 150, 250, ent->d_name);

           int x = 100;
           x = x + 100;
       }

}

     closedir (dir);
}

return 0;

}
