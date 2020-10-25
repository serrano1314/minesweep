#include<windows.h>
/*
black-------------0
blue--------------1
green-------------2
cyan--------------3
red---------------4
magenta-----------5
brown-------------6
light gray--------7
dark gray---------8
light blue--------9
light green-------10
light cyan--------11
light red---------12
light magenta-----13
yellow------------14
white-------------15

*/
void textcolor(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

