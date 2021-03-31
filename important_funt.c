#include "function.h"

struct GAME game;

void clean_stdin(void) {  //�M����J�w�İ�
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void color_set(int color_num) {     //�]�w��X�C��
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, color_num);
}

bool compare_coor(Coor t1, Coor t2) {    //����y�ЬO�_�@��
    if (t1.x == t2.x && t1.y == t2.y) {
        return true;
    }
    return false;
}

void degree_of_difficulty(void) {       //�ۭq����
    int choose, change, max_landboom;
    char decide = '\0';
    bool exit = false, choose_exit = false, error = false;
    while (!exit) {
        if (game.set.lines == 0) {
            choose = 1;
        }
        else if (game.set.cols == 0) {
            choose = 2;
        }
        else if (game.set.landboom == 0) {
            max_landboom = (game.set.lines - 1) * (game.set.cols - 1);
            choose = 3;
        }
        switch (choose) {
            case 1:
                do {
                    error = false;
                    gotoxy(30, 1);
                    printf("�п�J����x(�̤p9,�̤j30): ");
                    print_space();
                    scanf("%d", &game.set.lines);
                    clean_stdin();
                    if (game.set.lines < 9 || game.set.lines > 30) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
            case 2:
                do {
                    error = false;
                    gotoxy(30, 2);
                    printf("�п�J�e��y(�̤p9,�̤j24): ");
                    print_space();
                    scanf("%d", &game.set.cols);
                    clean_stdin();
                    if (game.set.cols < 9 || game.set.cols > 24) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
            case 3:
                do {
                    error = false;
                    gotoxy(30, 3);
                    printf("�п�J���u��(�̤p10,�̤j%-3d): ", max_landboom);
                    print_space();
                    scanf("%d", &game.set.landboom);
                    clean_stdin();
                    if (game.set.landboom < 10 || game.set.landboom > max_landboom) {
                        error = true;
                        print_warning(OverRange);
                    }
                } while (error);
                break;
        }
        if (game.set.lines != 0 && game.set.cols != 0 && game.set.landboom != 0) {
            choose_exit = false;
            while (!choose_exit) {
                decide = '\0';
                gotoxy(30, 4);
                printf("���n�վ㪺��?(Y/N) ");
                print_space();
                scanf("%c", &decide);
                clean_stdin();
                switch (decide) {
                    case 'y':
                    case 'Y':
                        do {
                            change = 0;
                            error = false;
                            gotoxy(30, 5);
                            printf("�аݻݭn�վ���̩O?(1:���� 2:�e�� 3:�a�p��) ");
                            print_space();
                            scanf("%d", &change);
                            clean_stdin();
                            switch (change) {
                                case 1:
                                    change = 0;
                                    game.set.lines = 0;
                                    game.set.landboom = 0;
                                    choose_exit = true;
                                    break;
                                case 2:
                                    change = 0;
                                    game.set.cols = 0;
                                    game.set.landboom = 0;
                                    choose_exit = true;
                                    break;
                                case 3:
                                    change = 0;
                                    game.set.landboom = 0;
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
                        gotoxy(30, 6);
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
    bool dif_restart = false;
    char restart = '\0';
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
                game.set.lines = 9;
                game.set.cols = 9;
                game.set.landboom = 10;
                break;
            case 2:
                reset();
                game.set.lines = 16;
                game.set.cols = 16;
                game.set.landboom = 40;
                break;
            case 3:
                reset();
                game.set.lines = 30;
                game.set.cols = 16;
                game.set.landboom = 99;
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
            continue_q = false;
            restart = '\0';
            dif_restart = false;
        }
        while (!dif_restart) {
            bool isRestart = true;
            gotoxy(60, 5);
            printf("�A�n���������׶�(Y/N) ");
            print_space();
            scanf("%c", &restart);
            clean_stdin();
            switch (restart) {
                case 'y':
                case 'Y':
                    game.restart = true;
                    dif_restart = true;
                    gotoxy(60, 6);
                    printf("���N���s�}�l");
                    Sleep(1000);
                    break;
                case 'n':
                case 'N':
                    isRestart = false;
                    break;
                default:
                    gotoxy(60, 6);
                    color_set(0xfc);
                    printf("�Ф��n�ÿ�J��");
                    Sleep(3000);
                    gotoxy(60, 6);
                    color_set(0x07);
                    for (i = 0; i < 14; i++) {
                        putchar(' ');
                    }
                    break;
            }
            if (!isRestart) {
                break;
            }
        }
        while (game.over && !game.restart && !over && !continue_q) {
            gotoxy(60, 6);
            printf("�A�ٷQ�n�~�򪱶�(Y/N) ");
            print_space();
            scanf("%c", &game.continue_q);
            clean_stdin();
            switch (game.continue_q) {
                case 'y':
                case 'Y':
                    continue_q = true;
                    gotoxy(60, 7);
                    printf("���N���s�}�l");
                    Sleep(1000);
                    break;
                case 'n':
                case 'N':
                    over = true;
                    gotoxy(60, 7);
                    printf("�U���A��");
                    Sleep(1000);
                    break;
                default:
                    gotoxy(60, 7);
                    color_set(0xfc);
                    printf("�Ф��n�ÿ�J��");
                    Sleep(3000);
                    gotoxy(60, 7);
                    color_set(0x07);
                    for (i = 0; i < 14; i++) {
                        putchar(' ');
                    }
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
    COORD c = { (SHORT)(x - 1), (SHORT)(y - 1)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void is_hide_cursor(bool isHide) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = {1, !isHide};
    SetConsoleCursorInfo(hOut, &info);
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
    int location = 0;
    switch (type) {
        case Map:
            location = (game.set.cols + 1) * test.y + test.x;
            break;
        case Mark:
            if (!over_range(test))
                location = game.set.cols * (test.y - 1) + (test.x - 1);
            break;
    }
    return location;
}

bool over_range(Coor c) {   //�p�⦳�L�W�X�a�Ͻd��
    if (c.x < 1 || c.x > game.set.cols || c.y < 1 || c.y > game.set.lines) {
        return true;
    }
    return false;
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
            gotoxy(30, 6);
            printf("�Ф��n�W�L�d���!");
            Sleep(3000);
            gotoxy(30, 6);
            break;
        case EnterError:
            gotoxy(30, 6);
            printf("�Ф��n�ÿ�J��!");
            Sleep(3000);
            gotoxy(30, 6);
            break;
        case OverCoordinate:
            gotoxy(60, 7);
            printf("��J���~!�Э��s��J!!");
            game.error = true;
            Sleep(3000);
            gotoxy(60, 7);
            break;
        case MarkCoordinate:
            gotoxy(60, 7);
            printf("�A�����аO���a��!");
            game.error = true;
            Sleep(3000);
            gotoxy(60, 7);
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
    game.exit = false;
    game.flag = 0;
    game.continue_q = '\0';
}

void reset_set(void) {      //���]set�Ѽ�
    game.set.lines = 0;
    game.set.cols = 0;
    game.set.landboom = 0;
}
