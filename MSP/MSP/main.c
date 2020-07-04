#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
 
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80           //매크로로 좌우상하 설정한다.
 
int map[25][25] = {0,};
int score = 0;
int Mscore;
 
void mapin()
{
    int q,w;
    for(q=0; q<25; q++){
        for(w=0; w<25; w++){
            if(q==0 || q==24 || w==0 || w==24)
                map[q][w] = 1;
            else
                map[q][w] = 0;
        }
    }
}
 
void setXY(short x, short y) // 함수값을 정해주는 함수
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
 
void Pmap()  //맵 프린트
{
    FILE *fp ;
    
    int i, j;
 
    system("cls");
 
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            setXY(i * 2, j);
 
            if (map[i][j] == 0)
                printf("");
 
            else if (map[i][j] == 1)
                printf("■");
 
            else if (map[i][j] == 2)
                printf("○");
 
            else if (map[i][j] == 3)
                printf("★");
 
        }
        printf("  score : %d", score);
    }
    
    fp = fopen("score.txt", "r");
    fscanf(fp, "%d", &Mscore);
    fclose(fp);
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 23 });
    printf("  max score : %d", Mscore);
}
 
int arrow() //방향키 입력
{
    int N = 0;
    char c;
    c = _getch();
 
    if (c == -32) {
 
        c = _getch();
 
        switch (c) {
        case LEFT:
            N = 1;
            break;
 
        case RIGHT:
            N = 2;
            break;
 
        case UP:
            N = 3;
            break;
 
        case DOWN:
            N = 4;
            break;
 
        }
    }
    return(N);
}
 
void star() // 맵에 별을 찍는 함수
 
{
    int x, y;
 
    srand(time(NULL));
 
    x = rand() % 23 + 1;
    y = rand() % 23 + 1;
 
    while (map[x][y] == 2) {
        x = rand() % 23 + 1;
        y = rand() % 23 + 1;
    }
    map[x][y] = 3;
}
 
void reprint(short x, short y, int n) //맵프린팅(커서단위)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
 
    if (n == 0)
        printf("  ");
    else
        printf("○");
}
 
void RemoveCursor()//커서지우기
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
 
void InMscore()//최고점수 저장
{
    FILE* fp;
        
    if(score > Mscore){
        fp = fopen("score.txt", "w");
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}
 
void gameover()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 20, 12 });
    printf("GAME OVER");
}
 
int main(void)
{
    int arrowN;
    int x, y;
    int ex, ey;
    int rx = 0, ry = 0;
    int erx = 0, ery = 0;
    int regame = 0;
    
    RemoveCursor();
 
    while(regame == 0){
        
        score = 0;
        mapin();
        
        x = 12, y = 12;
        ex = 24, ey = 12;
 
        star();
        Pmap();
        
        while (map[x][y] != 1 && map[x][y] != 2) {
 
            if (map[x][y] == 3) {
                score++;
                InMscore();
                star();
                Pmap();
            }
            else {
                rx = x;
                erx = ex;
                ry = y;
                ery = ey;
            }
 
            map[x][y] = 2;
            reprint(ex, ey, 2);
 
            Sleep(100);
 
            map[rx][ry] = 0;
            reprint(erx, ery, 0);
 
            if (_kbhit())
                arrowN = arrow();
 
            if (arrowN == 1) {
                x--;
                ex -= 2;
            }
 
            else if (arrowN == 2) {
                x++;
                ex += 2;
            }
 
            else if (arrowN == 3) {
                y--;
                ey--;
            }
 
            else if (arrowN == 4) {
                y++;
                ey++;
            }
 
        }
        gameover();
        
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 25 });
        
        printf("다시하려면 0, 나가려면 1을 입력하십시오 :");
        scanf("%d", &regame);
        while(regame != 0 && regame != 1){
            printf("\n잘못 입력하였습니다 다시 입력해 주세요. :");
            scanf("%d", &regame);
        }
    }
}
