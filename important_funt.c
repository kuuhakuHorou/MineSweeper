#include "function.h"

struct SET set;
struct GAME game;

void clean_stdin(void) {  //�M����J�w�İ�
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void color_set(int color_num) {     //https://baike.baidu.com/item/SetConsoleTextAttribute �C�������
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, color_num);
}

bool compare_coor(Coor t1, Coor t2) {
    if (t1.x == t2.x && t1.y == t2.y) {
        return true;
    }
    return false;
}

void degree_of_difficulty(void) {       //�ۭq����
    int choose, change;
    char decide = '\0';
    bool exit = false, choose_exit = false, error = false;
    while (!exit) {
        if (set.lines == 0) {
            choose = 1;
        }
        else if (set.cols == 0) {
            choose = 2;
        }
        else if (set.landboom == 0) {
            choose = 3;
        }
        switch (choose) {
            case 1:
                do {
                    error = false;
                    gotoxy(30,1);
                    printf("�п�J����x(�̤p9,�̤j30): ");
                    print_space();
                    scanf("%d", &set.lines);
                    clean_stdin();
                    if (set.lines < 9 || set.lines > 30) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
            case 2:
                do {
                    error = false;
                    gotoxy(30,2);
                    printf("�п�J�e��y(�̤p9,�̤j24): ");
                    print_space();
                    scanf("%d", &set.cols);
                    clean_stdin();
                    if (set.cols < 9 || set.cols > 24) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
            case 3:
                do {
                    error = false;
                    gotoxy(30,3);
                    printf("�п�J���u��(�̤p10,�̤j%-3d): ", (set.lines-1) * (set.cols-1));
                    print_space();
                    scanf("%d", &set.landboom);
                    clean_stdin();
                    if (set.landboom < 10 || set.landboom > (set.lines-1) * (set.cols-1)) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
        }
        if (set.lines != 0 && set.cols != 0 && set.landboom != 0) {
            change = 0;
            decide = '\0';
            choose_exit = false;
            while (!choose_exit) {
                gotoxy(30,4);
                printf("���n�վ㪺��?(Y/N) ");
                print_space();
                scanf("%c", &decide);
                clean_stdin();
                switch (decide) {
                    case 'y':
                    case 'Y':
                        do {
                            error = false;
                            gotoxy(30,5);
                            printf("�аݻݭn�վ���̩O?(1:���� 2:�e�� 3:�a�p��) ");
                            print_space();
                            scanf("%d", &change);
                            clean_stdin();
                            switch (change) {
                                case 1:
                                    change = 0;
                                    set.lines = 0;
                                    set.landboom = 0;
                                    choose_exit = true;
                                    break;
                                case 2:
                                    change = 0;
                                    set.cols = 0;
                                    set.landboom = 0;
                                    choose_exit = true;
                                    break;
                                case 3:
                                    change = 0;
                                    set.landboom = 0;
                                    choose_exit = true;
                                    break;
                                default:
                                    error = true;
                                    print_warning(EnterError);
                                    break;
                            }
                        } while (error);
                        break;
                    case 'n':
                    case 'N':
                        gotoxy(30,6);
                        printf("���N�}�l�C���o");
                        Sleep(1000);
                        choose_exit = true;
                        exit = true;
                        break;
                    default:
                        print_warning(EnterError);
                        break;
                }
            }
        }
    }
}

void game_dif_choose(void) {        //�C�����׿�h
    int choose = 0,  i;
    bool over = false, continue_q = false, first_play = true, error = false;
    MAP map;
    reset();
    while (!over) {
        if (!game.restart) {
            error = false;
            printf("�аݭn����˪����שO\n");
            if (!first_play) {
                printf("    ������(�]�t�۩w�q):0\n");
            }
            printf("    ²��:1\n"
                   "    ���q:2\n"
                   "    �x��:3\n"
                   "    �۩w�q:4\n"
                   "  �п�J: ");
            scanf("%d", &choose);
            clean_stdin();
        } else if (game.restart){
            choose = 0;
        }
        switch (choose) {
            case 0:
                reset_game();
                break;
            case 1:
                reset();
                set.lines = 9;
                set.cols = 9;
                set.landboom = 10;
                break;
            case 2:
                reset();
                set.lines = 16;
                set.cols = 16;
                set.landboom = 40;
                break;
            case 3:
                reset();
                set.lines = 30;
                set.cols = 16;
                set.landboom = 99;
                break;
            case 4:
                reset();
                degree_of_difficulty();
                break;
            default:
                error = true;
                color_set(0xfc);
                printf("�Ф��n�ÿ�J��!\n");
                color_set(0x07);
                Sleep(3000);    //����
                system("cls");  //��s�ù�
                break;
        }
        if (!error) {
            game_content(&map);
        }
        while (game.over && !game.restart) {
            gotoxy(60,2);
            printf("�A�ٷQ�n�~�򪱶�(Y/N) ");
            print_space();
            scanf("%c", &game.continue_q);
            clean_stdin();
            switch (game.continue_q) {
                case 'y':
                case 'Y':
                    continue_q = true;
                    gotoxy(60,3);
                    printf("���N���s�}�l");
                    Sleep(1000);
                    break;
                case 'n':
                case 'N':
                    over = true;
                    gotoxy(60,3);
                    printf("�U���A��");
                    Sleep(1000);
                    break;
                default:
                    gotoxy(60,3);
                    color_set(0xfc);
                    printf("�Ф��n�ÿ�J��");
                    Sleep(3000);
                    gotoxy(60,3);
                    color_set(0x07);
                    for (i = 0; i < 14; i++) {
                        putchar(' ');
                    }
                    break;
            }
            if (over || continue_q) {
                break;
            }
        }
        if (continue_q) {
            first_play = false;
            system("cls");
        }
    }
}

void gotoxy(int x,int y) {  //���w�y��(x�My�q0�}�l��A�ҥH��1�A������[)
    COORD c;
    c.X = x-1;
    c.Y = y-1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int location_value(MAP *map, Coor coor, Type type) { //�p��a�Ϧ�m�ƭ�
    int value = 0;
    switch(type) {
        case Map:
            value = map->map[map_location(coor, type)];
            break;
        case Mark:
            value = map->mark[map_location(coor, type)];
            break;
    }
    return value;
}

int map_location(Coor test, Type type) {  //�p��}�C��m
    int location;
    switch (type) {
        case Map:
            location = (set.cols + 1) * test.y + test.x;
            break;
        case Mark:
            location = set.cols * (test.y - 1) + (test.x - 1);
            break;
    }
    return location;
}

bool over_range(Coor c) {   //�p�⦳�L�W�X�a�Ͻd��
    if (c.x < 1 || c.x > set.cols || c.y < 1 || c.y > set.lines) {
        return true;
    }
    else {
        return false;
    }
}

void print_space(void) {    //�L�ť�(10��)
    int space_number = 10;
    for (int i = 0; i < space_number; i++) {
        putchar(' ');
    }
    for (int i = 0; i < space_number; i++) {
        putchar('\b');
    }
}

void print_warning(Warning warn) {  //��J���~ĵ�i
    int i, space_number = 30;
    color_set(0xfc);
    switch(warn) {
        case OverRange:
            gotoxy(30,6);
            printf("�Ф��n�W�L�d���!");
            Sleep(3000);
            gotoxy(30,6);
            break;
        case EnterError:
            gotoxy(30,6);
            printf("�Ф��n�ÿ�J��!");
            Sleep(3000);
            gotoxy(30,6);
            break;
        case OverCoordinate:
            gotoxy(60,3);
            printf("��J���~!�Э��s��J!!");
            game.error = true;
            Sleep(3000);
            gotoxy(60,3);
            break;
        case MarkCoordinate:
            gotoxy(60,3);
            printf("�A�����аO���a��!");
            game.error = true;
            Sleep(3000);
            gotoxy(60,3);
            break;
    }
    color_set(0x07);
    for (i = 0; i < space_number; i++) {
        putchar(' ');
    }
}

void reset(void) {  //���]�C���Ѽ�
    reset_game();
    reset_set();
}

void reset_game(void) {     //���]game�Ѽ�
    game.error = false;
    game.over = false;
    game.restart = false;
    game.sweep_landboom = false;
    game.flag = 0;
    game.continue_q = '\0';
}

void reset_set(void) {      //���]set�Ѽ�
    set.lines = 0;
    set.cols = 0;
    set.landboom = 0;
}
