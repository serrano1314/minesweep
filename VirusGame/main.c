#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <time.h>
#include<string.h>
#include "gotoxy.h"
#include "colorfunc.h"
#include "validate_func.h"//my own header file for error handling for integer inputs
#define max 150
clrscr(){
    system("cls");
}
void generateRandNum(int size);
void sortingRandNum(int *param, int *target, int size);
void ditributeRandNum();
void startGame();
void reset();
void selectLevel();
int enteredNums(int num);
bool displayMatrix();
char menu();
bool minus,addWin;
int randomNumbers[max],sortedRandNum[max],opened[max],tmp[max];
int matrixCount[max][max];
char dataVirus[max][max],levelName[15];
char ch,level;
int i,j,k,l=0,temp,target,timePlus=0,counts=0,
    lives,numberOfVirus,lives,win=0;
int rows,columns,limit,borderColor=14;

int main(){
system("chcp 65001 > nul");
    do{
        clrscr();
        selectLevel();
        limit=rows*columns;
        startGame();
        do{
            textcolor(15,0);
            displayMatrix();
            border(rows, columns);
            gotoxy(14,8);
            textcolor(0,15);
            printf(" %s\t",levelName);
            printf("%d X %d ", rows, columns);
            textcolor(15,0);
            gotoxy(1,2);
            printf("\tSCORE: %d/%d\tSAFE = ",win,limit-numberOfVirus);
            textcolor(15,10);
            printf("   ");
            textcolor(15,0);
            printf("   VIRUS = ");
            textcolor(15,12);
            printf("   ");
            textcolor(15,0);
            printf("\n\t\tVIRUS : ");
            textcolor(12,0);
            printf("%d\n",numberOfVirus);
            textcolor(15,0);
            /*for(i=0;i<limit;i++){
                printf("%d_",tmp[i]);
            }*/
            printf("\t\tLIFES: ");
            for(i=0;i<lives;i++){
                textcolor(13,0);
                printf("♥ ");
            }
            putchar('\n');
            i=0;
            if(lives==0){
                textcolor(12,0);
                putchar('\a');
                printf("\t\tGAME OVER !");
                reset();
                break;
            }
            if(win==(limit-numberOfVirus)){
                textcolor(11,0);
                putchar('\a');
                printf("\t\tYOU WIN !");
                target=NULL;
                reset();
                break;
            }
            textcolor(11,0);
            while(target=inputAndValidation("\t\tTARGET")){
                if (target>limit||enteredNums(target)==1){
                    continue;
                }
                else{
                    tmp[l]=target;
                    l++;
                    for(i=0;i<limit;i++){//minus lives when selecting the virus coordinate
                        if(target==sortedRandNum[i]&&sortedRandNum[i]!=-1){
                            lives--;
                            addWin=false;
                            sortedRandNum[i]=-1;//already chosen
                            break;
                        }
                        else if(sortedRandNum[i]!=-1)
                            addWin=true;
                    }
                    break;
                }
            }
            if(addWin)
                win++;
            i++;
        }
        while(true);
        _getch();
    }while(menu()!='n');
}
void selectLevel(){
    do{
        textcolor(15,0);
        printf("\n\n\tPLEASE SELECT A LEVEL...\n\n");
        printf("\t[0]CUSTOM         \n");
        printf("\t[1]EASY           \n");
        printf("\t[2]MEDIUM         \n");
        printf("\t[3]HARD           \n");
        printf("\t[4]EXTREME        \n");
        printf("\t[5]HARDCORE       \n\n");
        printf("\t[X]EXIT           \n");
        switch(level=_getch()){
        case '0':
            strcpy(levelName,"CUSTOM");
            clrscr();
            printf("INPUT ROWS: ");
            scanf("%d",&rows);
            printf("INPUT COLUMNS: ");
            scanf("%d",&columns);
            printf("INPUT NUMBER OF VIRUS: ");
            scanf("%d",&numberOfVirus);
            fflush(stdin);
            printf("INPUT LIVES: ");
            scanf("%d",&lives);
            break;
        case '1':
            strcpy(levelName,"EASY");
            rows=5;
            columns=6;
            numberOfVirus=8;
            lives=5;
            break;
        case '2':
            strcpy(levelName,"MEDIUM");
            rows=7;
            columns=7;
            numberOfVirus=12;
            lives=5;
            break;
        case '3':
            strcpy(levelName,"HARD");
            rows=8;
            columns=8;
            numberOfVirus=20;
            lives=4;
            break;
        case '4':
            strcpy(levelName,"EXTREME");
            rows=8;
            columns=8;
            numberOfVirus=25;
            lives=3;
            break;
        case '5':
            strcpy(levelName,"HARDCORE");
            rows=10;
            columns=10;
            numberOfVirus=30;
            lives=6;
            break;
        case 'x':
            exit(0);
        default:
            printf("\nINVALID CHOICE!");
            _getch();
            clrscr();
            continue;
        }
    break;
    }while(true);

}
char menu(){
    do{
        textcolor(15,1);
        gotoxy(15,columns*2+10);
        printf("\n\n[1]PLAY AGAIN\n[2]EXIT\n[3]REVEAL");
        textcolor(15,0);
        switch(ch=_getch()){
        case '1':
            return 'y';
            break;
        case '2':
            return 'n';
            break;
        case '3'://reveal
            for(i=0;i<limit;i++){
                opened[i]=1;
            }

            displayMatrix();
            border(rows,columns);
            printf("\n\nPress any key to continue...");
            _getch();
            for(i=0;i<limit;i++){
                opened[i]=0;
            }
            break;
        default:
            printf("\nINVALID CHOICE!");
            _getch();
            clrscr();
            continue;
        }

    }while(true);

}
void startGame(){
    generateRandNum(numberOfVirus);
}
void generateRandNum(int size){
    int x;
    bool arr[100];
    srand(time(0)+timePlus);
    for(i=0;i<size;i++){
        x=1+rand()%limit;
        if(!arr[x])
                randomNumbers[i]=x;
            else
                i--;
            arr[x]=1;
    }
    timePlus++;
    sortingRandNum(randomNumbers,sortedRandNum,size);
}
void sortingRandNum(int *param, int *target, int size) {
    int past_min = max, current_min = max;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            if (i == 0 || param[j] > past_min) {
                if (past_min == current_min || param[j] < current_min) {
                    current_min = param[j];
                }
            }
        }
        target[i] = current_min;
        past_min = current_min;
    }

        ditributeRandNum();
}
void ditributeRandNum(){
    int count=1,temp;
    k=0;
    for(i=0;i<rows;i++){//
        for(j=0;j<columns;j++){//distributing virus data and safes to 2d array
            if(count==sortedRandNum[k]||count==target){
                dataVirus[i][j]='*';
                k++;
            }
            else{
                dataVirus[i][j]='_';
            }
            matrixCount[i][j]=count;
            count++;
        }
    }
}
bool displayMatrix(){
    clrscr();
    textcolor(15,0);
    int count=1;
    int horiSpace=8,vertiSpace=10;
    bool liveMinus;
    k=0;
    gotoxy(8,10);
    for(i=0;i<rows;i++){//
        if(i!=0&&j!=0)
            putchar('\t\t');
        for(j=0;j<columns;j++){
            if(count==target||opened[k]==1){
                if(dataVirus[i][j]=='*'){
                    textcolor(15,12);
                    addWin=false;
                }
                else{
                    textcolor(15,10);
                }
                opened[k]=1;
            }
            gotoxy(horiSpace,vertiSpace);
            printf("%3d ",count);
            textcolor(15,0);
            count++;
            k++;
            horiSpace+=5;
        }
        horiSpace = 8;
        vertiSpace+=2;
    }
    return liveMinus;
}
int enteredNums(int num){
    counts=0;
    while(num!=tmp[counts]){
        if(counts==limit){
            return 0;
        }
        counts++;
    }
    return 1;
}
void reset(){//resets values
    textcolor(15,0);
    target=NULL;
    win=0;
    i=0;j=0;k=0;l=0;
    for(i=0;i<limit;i++){
        opened[i]=0;
        tmp[i]=0;
        sortedRandNum[i]=0;
        randomNumbers[i]=0;
    }

}
void border(int y, int x){


    int horiSpace=7,vertiSpace=9;

    textcolor(borderColor,0);
    //horizontal lines
    gotoxy(8,11);
    for(i=0;i<y;i++){
        gotoxy(horiSpace,vertiSpace);
        for(j=0;j<x*5;j++){
            printf("═");
        }
        vertiSpace+=2;
    }
    //vertical lines
    gotoxy(horiSpace=12,vertiSpace=10);
    for(i=0;i<x-1;i++){
        for(j=0;j<y*2;j++){
            if(j%2==0)
                printf("╬");
            else
                printf("║");
            gotoxy(horiSpace,vertiSpace++);
        }
        horiSpace+=5;
        vertiSpace=10;
    }
    horiSpace=7;vertiSpace=9;
    //printf("╔ ═ ╗ ║ ╚ ╝")
    //top margin line
    gotoxy(7,9);printf("╔");
    for(i=0;i<(x*5)-1;i++)
        printf("═");
    printf("╗");
    //right margin line
    gotoxy(horiSpace+(x*5),vertiSpace+=1);
    for(i=0;i<y*2;i++){
        printf("║");
        gotoxy(horiSpace+(x*5),vertiSpace++);
    }
    //bottom margin line
    gotoxy(7,(y*2)+9);printf("╚");
    for(i=0;i<(x*5)-1;i++)
        printf("═");
    printf("╝");
    //left margin line
    gotoxy(horiSpace=7,vertiSpace=10);
    for(i=0;i<y*2;i++){
        printf("║");
        gotoxy(horiSpace,vertiSpace++);
    }
    textcolor(15,0);
}


