#include "funtion.h"

void game_dif_choose() {
    int choose, error_in=0, game_end;
    while (1) {
        printf("�аݭn����˪����שO\n"
               "    ²��:1\n"
               "    ���q:2\n"
               "    �x��:3\n"
               "  �п�J: ");
        scanf("%d", &choose);
        fflush(stdin);  //�M�z��J�w�İ�
        switch (choose) {
            case 1:
                game_easy();
                game_end=1;
                break;
            case 2:
                game_normal();
                game_end=1;
                break;
            case 3:
                game_hard();
                game_end=1;
                break;
            default:
                printf("�Ф��n�ÿ�J��!\n");
                Sleep(3000);    //����
                system("cls");  //��s�ù�
                break;
        }
        if (game_end==1) {
            break;
        }
        
    }
}

void gotoxy(int x,int y) {  //���w�y��(x�My�q0�}�l��A�ҥH��1�A������[)
    COORD c;
    c.X=x-1;
    c.Y=y-1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
