#include "funtion.h"

void color_set(int color_num) {     //https://baike.baidu.com/item/SetConsoleTextAttribute �C�������
    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,color_num);
}

void game_dif_choose() {
    int choose, error_in=0;
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
                game.lines=9;
                game.cols=9;
                game.landboom=10;
                game_content();
                break;
            case 2:
                game.lines=16;
                game.cols=16;
                game.landboom=40;
                game_content();
                break;
            case 3:
                game.lines=30;
                game.cols=16;
                game.landboom=99;
                game_content();
                break;
            default:
                color_set(12);
                printf("�Ф��n�ÿ�J��!\n");
                color_set(7);
                Sleep(3000);    //����
                system("cls");  //��s�ù�
                break;
        }
        if (game.over==1) {
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
