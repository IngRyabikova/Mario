int main() {

char header[54];
ifstream bmp;
bmp.open("fire.bmp", ios::in | ios::binary);

if (!bmp) {
    cout << "Error" << endl;
    system("PAUSE");
    exit(1);
}

bmp.read(header, 54);

char a = header[18];

int b = *(int *)&header[18];

system("PAUSE");
}
