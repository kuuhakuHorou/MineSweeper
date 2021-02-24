#include "funtion.h"

void color_set(int color_num) {     //https://baike.baidu.com/item/SetConsoleTextAttribute �C�������
    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,color_num);
}

void degree_of_difficulty() {       //�ۭq����
    int choose, i, change, exit, choose_exit;
    while (1) {
        if (set.lines==0) {
            choose=1;
        }
        else if (set.cols==0) {
            choose=2;
        }
        else if (set.landboom==0) {
            choose=3;
        }
        switch (choose) {
            case 1:
            while (1) {
                gotoxy(30,1);
                printf("�п�J����x(�̤p9,�̤j30): ");
                for (i=0;i<10;i++) {
                    putchar(' ');
                }
                for (i=0;i<10;i++) {
                    putchar('\b');
                }
                scanf("%d", &set.lines);
                fflush(stdin);
                if (set.lines<9||set.lines>30) {
                    gotoxy(30,6);
                    color_set(252);
                    printf("�Ф��n�W�L�d���!");
                    Sleep(3000);
                    color_set(7);
                    gotoxy(30,1);
                    for (i=0;i<35;i++) {
                        putchar(' ');
                    }
                    gotoxy(30,6);
                    for (i=0;i<17;i++) {
                        putchar(' ');
                    }
                }
                else
                    break;
            }
            break;
            case 2:
            while (1) {
                gotoxy(30,2);
                printf("�п�J�e��y(�̤p9,�̤j24): ");
                for (i=0;i<10;i++) {
                    putchar(' ');
                }
                for (i=0;i<10;i++) {
                    putchar('\b');
                }
                scanf("%d", &set.cols);
                fflush(stdin);
                if (set.cols<9||set.cols>24) {
                    gotoxy(30,6);
                    color_set(252);
                    printf("�Ф��n�W�L�d���!");
                    Sleep(3000);
                    color_set(7);
                    gotoxy(30,2);
                    for (i=0;i<35;i++) {
                        putchar(' ');
                    }
                    gotoxy(30,6);
                    for (i=0;i<17;i++) {
                        putchar(' ');
                    }
                }
                else
                    break;
            }
            break;
            case 3:
            while (1) {
                gotoxy(30,3);
                printf("�п�J���u��(�̤p10,�̤j%-3d): ", (set.lines-1)*(set.cols-1));
                for (i=0;i<10;i++) {
                    putchar(' ');
                }
                for (i=0;i<10;i++) {
                    putchar('\b');
                }
                scanf("%d", &set.landboom);
                fflush(stdin);
                if (set.landboom<10||set.landboom>(set.lines-1)*(set.cols-1)) {
                    gotoxy(30,6);
                    color_set(252);
                    printf("�Ф��n�W�L�d���!");
                    Sleep(3000);
                    color_set(7);
                    gotoxy(30,3);
                    for (i=0;i<40;i++) {
                        putchar(' ');
                    }
                    gotoxy(30,6);
                    for (i=0;i<17;i++) {
                        putchar(' ');
                    }
                }
                else
                    break;
            }
            break;
        }
        if (set.lines!=0&&set.cols!=0&&set.landboom!=0) {
            while (1) {
                char decide;
                gotoxy(30,4);
                printf("���n�վ㪺��?(Y/N) ");
                for (i=0;i<10;i++) {
                    putchar(' ');
                }
                for (i=0;i<10;i++) {
                    putchar('\b');
                }
                scanf("%c", &decide);
                fflush(stdin);
                switch (decide) {
                    case 'y':
                    case 'Y':
                        while (1) {
                            gotoxy(30,5);
                            printf("�аݻݭn�վ���̩O?(1:���� 2:�e�� 3:�a�p��) ");
                            for (i=0;i<10;i++) {
                                putchar(' ');
                            }
                            for (i=0;i<10;i++) {
                                putchar('\b');
                            }
                            scanf("%d", &change);
                            fflush(stdin);
                            if (change<1||change>3) {
                                gotoxy(30,6);
                                color_set(252);
                                printf("�Ф��n�ÿ�J��!");
                                Sleep(3000);
                                color_set(7);
                                gotoxy(30,5);
                                for (i=0;i<50;i++) {
                                    putchar(' ');
                                }
                                gotoxy(30,6);
                                for (i=0;i<15;i++) {
                                    putchar(' ');
                                }
                            }
                            else if (change==1) {
                                change=0;
                                set.lines=0;
                                choose_exit=1;
                                break;
                            }
                            else if (change==2) {
                                change=0;
                                set.cols=0;
                                choose_exit=1;
                                break;
                            }
                            else if (change==3) {
                                change=0;
                                set.landboom=0;
                                choose_exit=1;
                                break;
                            }
                        }
                    break;
                    case 'n':
                    case 'N':
                        gotoxy(30,6);
                        printf("���N�}�l�C���o");
                        Sleep(1000);
                        choose_exit=1;
                        exit=1;
                    break;
                    default:
                        gotoxy(30,6);
                        color_set(252);
                        printf("�Ф��n�ÿ�J��!");
                        Sleep(3000);
                        color_set(7);
                        gotoxy(30,4);
                        for (i=0;i<25;i++) {
                            putchar(' ');
                        }
                        gotoxy(30,6);
                        for (i=0;i<15;i++) {
                            putchar(' ');
                        }
                    break;
                }
                if (choose_exit==1) {
                    break;
                }
            }
        }
        if (exit==1) {
            break;
        }
    }
}

void game_dif_choose() {        //�C�����׿�h
    int choose, error_in=0, over, i;
    while (1) {
        printf("�аݭn����˪����שO\n"
               "    ²��:1\n"
               "    ���q:2\n"
               "    �x��:3\n"
               "    �۩w�q:4\n"
               "  �п�J: ");
        scanf("%d", &choose);
        fflush(stdin);  //�M�z��J�w�İ�
        switch (choose) {
            case 1:
                set.lines=9;
                set.cols=9;
                set.landboom=10;
                game_content();
                break;
            case 2:
                set.lines=16;
                set.cols=16;
                set.landboom=40;
                game_content();
                break;
            case 3:
                set.lines=30;
                set.cols=16;
                set.landboom=99;
                game_content();
                break;
            case 4:
                degree_of_difficulty();
                game_content();
                break;
            default:
                color_set(252);
                printf("�Ф��n�ÿ�J��!\n");
                color_set(7);
                Sleep(3000);    //����
                system("cls");  //��s�ù�
                break;
        }
        while (game.over==1) {
            gotoxy(60,2);
            printf("�A�ٷQ�n�~�򪱶�(Y/N) ");
            for (i=0;i<10;i++) {
                putchar(' ');
            }
            for (i=0;i<10;i++) {
                putchar('\b');
            }
            scanf("%c", &game.continue_q);
            fflush(stdin);
            switch (game.continue_q) {
                case 'y':
                case 'Y':
                    game.continue_q=1;
                    gotoxy(60,3);
                    printf("���N���s�}�l�o");
                    Sleep(1000);
                break;
                case 'n':
                case 'N':
                    over=1;
                    gotoxy(60,3);
                    printf("���N�T�T�o");
                    Sleep(1000);
                break;
                default:
                    gotoxy(60,3);
                    color_set(252);
                    printf("�Ф��n�ÿ�J��");
                    Sleep(3000);
                    gotoxy(60,3);
                    color_set(7);
                    for (i=0;i<14;i++) {
                        putchar(' ');
                    }
                break;
            }
            if (over==1||game.continue_q==1) {
                break;
            }
        }
        if (game.continue_q==1) {
            system("cls");
        }
        else if (over==1) {
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
