#include<windows.h>
COORD coord={0,0};
void gotoxy(int x,int y)
 {
    coord.X=x;
    coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
