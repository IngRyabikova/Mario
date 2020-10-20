#include "TXLib.h"

#include <fstream>
using namespace std;

int main() {

char header[54];
ifstream bmp;
bmp.open("kirpich.bmp", ios::in | ios::binary);


bmp.read(header, 54);

int b = *(int *)&header[18];
cout << b;
int b1 = *(int *)&header[22];
cout << b1;
}
