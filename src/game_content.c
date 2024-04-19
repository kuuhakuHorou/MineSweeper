#include "function.h"

struct COOR player;
extern struct GAME game;

void game_content(MAP *map) {   //�C�����e
    player.x = 99;
    player.y = 99;
    map->map = (int*)calloc((game.set.lines + 2) * (game.set.cols + 2), sizeof(int));  //�a��
    map->mark = (int*)calloc(game.set.lines * game.set.cols, sizeof(int));     //�аO�a��
    game_start(map);
    is_hide_cursor(true);
    print_game(map, true);
    is_win(map);
    while (!game.over) {
        interactive_mod(map);
    }
    is_hide_cursor(false);
    color_set(0x07);
    free(map->map);
    free(map->mark);
}

void game_start(MAP *map) {     //�C���}�l�]�w
    Coor loop;
    bool error = false;
    Coor enter = {0, 0};
    for (loop.y = 0; loop.y < game.set.lines + 2; loop.y++) {
        for (loop.x = 0; loop.x < game.set.cols + 2; loop.x++) {
            if (loop.y == 0 || loop.y == game.set.lines + 1 ||
                loop.x == 0 || loop.x == game.set.cols + 1)
                map->map[map_location(loop, Map)] = Border;   //99�����
            else
                map->map[map_location(loop, Map)] = NoSweep;    //0���Ŧa
        }
    }
    do {
        error = false;
        print_game(map, true);
        gotoxy(60, 4);
        printf("�Х���J�@�Ӯy��(x y): ");
        scanf("%d%d", &enter.y, &enter.x);
        fflush(stdin);
        if (over_range(enter)) {
            error = true;
            gotoxy(60, 5);
            color_set(0xfc);
            printf("�Ф��n�ÿ�J��!");
            color_set(0x07);
            Sleep(3000);
        }
    } while (error);
    player = enter;
    map->map[map_location(enter, Map)] = Space;
    landboom_generate(enter, map->map);    //�ͦ��a�p
    landboom_tester(enter, map);
}

void interactive_mod(MAP *map) {
    int keyboard;
    while (!kbhit());
    keyboard = getch();
    switch (keyboard) {
        case 'w':
        case 'W':
        case 72:
            player.y--;
            if (player.y == 0) {
                player.y = game.set.lines;
            }
            print_game(map, false);
            break;
        case 'a':
        case 'A':
        case 75:
            player.x--;
            if (player.x == 0) {
                player.x = game.set.cols;
            }
            print_game(map, false);
            break;
        case 's':
        case 'S':
        case 80:
            player.y++;
            if (player.y == game.set.lines + 1) {
                player.y = 1;
            }
            print_game(map, false);
            break;
        case 'd':
        case 'D':
        case 77:
            player.x++;
            if (player.x == game.set.cols + 1) {
                player.x = 1;
            }
            print_game(map, false);
            break;
        case 'f':
        case 'F':
        case '2':
            map_mark(map, false);
            break;
        case 'e':
        case 'E':
        case '1':
            sweep(map, false);
            break;
        case 'r':
        case 'R':
            game.over = true;
            game.restart = true;
            break;
        case 't':
        case 'T':
            text_mod(map);
            break;
        case 27:
            game.over = true;
            game.exit = true;
            break;
    }
}

void is_win(MAP *map) {  //���լO�_Ĺ�F
    int untreated_places = 0;  //�S��L���a
    Coor loop;
    for (loop.y = 0; loop.y < game.set.lines + 2; loop.y++) {
        for (loop.x = 0; loop.x < game.set.cols + 2; loop.x++) {
            if (location_value(map, loop, Map) == NoSweep) {
                untreated_places++;
            }
            else if (location_value(map, loop, Map) < Landboom) {
                continue;   //��L�B����a�p�B
            }
        }
    }
    if (untreated_places == 0) {
        for (loop.y = 0; loop.y < game.set.lines + 2; loop.y++) {
            for (loop.x = 0; loop.x < game.set.cols + 2; loop.x++) {
                if (location_value(map, loop, Map) == Landboom)
                    map->map[map_location(loop, Map)] = WinLandboom;  //��{�a�p�B
            }
        }
        game.over = true;
        print_game(map, true);
        gotoxy(60, 4);
        color_set(0xe0);
        printf("�AĹ�F");
    }
}

void landboom_generate(Coor test, int *map) {  //�H���ͦ��a�p
    srand(time(NULL));
    Coor produce;
    int landboom_num = 0;
    int *p_map;
    while (landboom_num < game.set.landboom) {
        produce.x = rand() % game.set.cols + 1;
        produce.y = rand() % game.set.lines + 1;
        p_map = map + map_location(produce, Map);
        if (*p_map != Landboom && !compare_coor(produce, test)) {
            *p_map = Landboom;
            landboom_num++;
        }
    }
}

void landboom_tester(Coor test, MAP *map) { //���ծ���K��a�p
    if (over_range(test))
        return;
    Coor loop;
    int landboom = 0; //����a�p��
    int val_map = location_value(map, test, Map);
    int val_mark = location_value(map, test, Mark);
    if (val_mark != NoFlag || (val_map > NoSweep && val_map < Space))
        //���ݺX�l�M�P�䦳�a�p���a��
        return;
    if (location_value(map, test, Map) == Landboom) {
        map->map[map_location(test, Map)] = SweepLandboom;
        game.sweep_landboom = true;
        return;
    }
    for (loop.y = test.y - 1; loop.y <= test.y + 1; loop.y++) {        //���թP��a�p
        for (loop.x = test.x - 1; loop.x <= test.x + 1; loop.x++) {
            if (compare_coor(test, loop))     //�򪺨��椣�κ�
                continue;
            else if (location_value(map, loop, Map) == Landboom ||
                     location_value(map, loop, Map) == SweepLandboom)
                landboom++;
        }
    }
    if (landboom == 0) {
        map->map[map_location(test, Map)] = Space;   //����S�a�p
        for (loop.y = test.y - 1; loop.y <= test.y + 1; loop.y++) {
            for (loop.x = test.x - 1; loop.x <= test.x + 1; loop.x++) {
                //�٨S��L�B�S�аO���a��
                if (location_value(map, loop, Map) == NoSweep &&
                    location_value(map, loop, Mark) == NoFlag)
                    landboom_tester(loop, map);
            }
        }
    }
    else
        map->map[map_location(test, Map)] = landboom;  //���䦳�a�p(��X�h��)
}

bool mod_choose(int mod, MAP *map, bool isTextmod) {
    if (mod == 1) {
        return sweep(map, isTextmod);
    }
    return map_mark(map, isTextmod);
}

bool sweep(MAP *map, bool isTextmod) {   //"��"
    Coor guess = {0, 0}, loop;
    if (isTextmod) {
        gotoxy(60, 6);
        printf("�п�J�A�Q���(x y): ");
        print_space();
        scanf("%d%d", &guess.y, &guess.x);
        clean_stdin();
    }
    else {
        guess = player;
    }
    if (over_range(guess)) {    //�W�X�a�p�d��
        print_warning(OverCoordinate);
        return false;
    }
    else if (location_value(map, guess, Mark) == Flag) {   //��аO
        print_warning(MarkCoordinate);
        return false;
    }
    else if(location_value(map, guess, Map) < Space &&
            location_value(map, guess, Map) > NoSweep) {
        //��Ʀr(�E�c��a�p��)
        int flags = 0;
        for (loop.y = guess.y - 1; loop.y <= guess.y + 1; loop.y++) {
            for (loop.x = guess.x - 1; loop.x <= guess.x + 1; loop.x++) {
                if (over_range(loop))
                    continue;
                if (location_value(map, loop, Mark) == Flag) {
                    flags++;
                }
            }
        }
        if (flags == location_value(map, guess, Map)) {
            for (loop.y = guess.y - 1; loop.y <= guess.y + 1; loop.y++) {
                for (loop.x = guess.x - 1; loop.x <= guess.x + 1; loop.x++) {
                    landboom_tester(loop, map);
                }
            }
        }
    }
    //���a�p�B
    if (location_value(map, guess, Map) == Landboom || game.sweep_landboom) {
        if (!game.sweep_landboom) {
            //���T��ܽ�쪺�a�p
            map->map[map_location(guess, Map)] = SweepLandboom;
        }
        for (loop.y = 0; loop.y < game.set.lines + 2; loop.y++) {
            for (loop.x = 0; loop.x < game.set.cols + 2; loop.x++) {
                if (location_value(map, loop, Map) == Landboom) {
                    //��F�H��ܦa�p�B
                    map->map[map_location(loop, Map)] = LoseLandboom;
                }
                else if (location_value(map, loop, Mark) == Flag &&
                         location_value(map, loop, Map) < Landboom) {
                    //�аO���~�A����~��{�X��
                    map->mark[map_location(loop, Mark)] = WrongFlag;
                }
            }
        }
        game.over = true;
        print_game(map, isTextmod);
        gotoxy(60, 4);
        color_set(0xc0);
        printf("�A��F");
        return true;
    }
    player = guess;
    landboom_tester(guess, map);
    print_game(map, isTextmod);
    is_win(map);
    return true;
}

bool map_mark(MAP *map, bool isTextmod) {   //�аO
    Coor mark = {0, 0};
    int *p_mark;
    int val_map;
    if (isTextmod) {
        gotoxy(60, 6);
        printf("�п�J�A�Q�аO��(x y): ");
        print_space();
        scanf("%d%d", &mark.y, &mark.x);
        clean_stdin();
    }
    else {
        mark = player;
    }
    if (over_range(mark)) { //�W�X�a�p�d��
        print_warning(OverCoordinate);
        return false;
    }
    val_map = location_value(map, mark, Map);
    if (val_map == Landboom || val_map == NoSweep) {
        p_mark = &map->mark[map_location(mark, Mark)];
        if (*p_mark == NoFlag) {
            *p_mark = Flag;    //�аO
            game.flag++;
        }
        else if (*p_mark == Flag) {
            *p_mark = NoFlag;    //�M���аO
            game.flag--;
        }
    }
    player = mark;
    print_game(map, isTextmod);
    return true;
}

void print_game(MAP *map, bool isClean) { //����
    gotoxy(1, 1);
    if (isClean) {
        system("cls");
    }
    Coor loop;
    int val_map, val_mark;
    printf("�@ �@y��\n�@�@�@");
    for (int i = 1; i < game.set.cols + 1; i++)
        printf("%2d", i);
    printf("\n x\n��");
    for (int i = 1; i < game.set.lines + 1; i++) {
        gotoxy(3, i + 3);
        printf("%2d", i);
    }
    gotoxy(14, 1);
    printf("�a�p��:%d", game.set.landboom);
    gotoxy(25, 1);
    printf("�X�l��:%2d", game.flag);
    for (loop.y = 0; loop.y < game.set.lines + 2; loop.y++) {
        gotoxy(5, loop.y + 3);
        for (loop.x = 0; loop.x < game.set.cols + 2; loop.x++) {
            val_map = location_value(map, loop, Map);
            val_mark = location_value(map, loop, Mark);
            if (val_map == Border) {
                color_set(0xaa);
                printf("  ");         //���
            }
            else if (compare_coor(loop, player) && !game.over) { //���a��m�B
                if (val_map == NoSweep || val_map == Landboom) {
                    if (val_mark == NoFlag) {
                        color_set(0x86);    //�٨S��L���a��&�a�p
                        printf("��");
                    }
                    else if (val_mark == Flag) {
                        color_set(0x64);
                        printf("��");    //�a�p�аO��{
                    }
                }
                else if (val_map == Space) {
                    color_set(0x68);
                    printf("��");    //��L���Ŧa
                }
                else if (val_map < Space) {
                    color_set(0x61);
                    printf(" %d", val_map); //��L�B���䦳�a�p�A��{�a�p��
                }
            }
            else if (val_mark == Flag) {
                color_set(0x8c);
                printf("��");    //�a�p�аO��{
            }
            else if (val_mark == WrongFlag) {
                color_set(0x8c);
                printf("�Y");     //�аO���~��{
            }
            else if (val_map == Space) {
                color_set(0x88);
                printf("  ");    //��L���Ŧa
            }
            else if (val_map == NoSweep || val_map == Landboom) {
                color_set(0x87);
                printf("��");     //�٨S��L���a��&�a�p
            }
            else if (val_map < Space) {
                color_set(0x8b);
                printf(" %d", val_map); //��L�B���䦳�a�p�A��{�a�p��
            }
            else if (val_map == LoseLandboom) {
                color_set(0x8e);
                printf("��");    //�����a�p�B
            }
            else if (val_map == SweepLandboom) {
                color_set(0xce);
                printf("��");    //���a�p�B
            }
            else if (val_map == WinLandboom) {
                color_set(0x8e);
                printf("��");    //�L����ܦa�p
            }
        }
    }
    color_set(0x07);
    for (int i = 1; i <= 36; i++) {
        gotoxy(58, i);
        printf("|");
    }
    gotoxy(60, 1);
    printf("w,a,s,d & ��V��: ���ʤ�V\te & 1: \"��\"  f & 2: �аO");
    gotoxy(60, 2);
    printf("t: ��r�Ҧ�  r: ���s�}�l\tesc: ���}");
    gotoxy(60, 3);
    for (int i = 0; i < 60; i++) {
        putchar('-');
    }
    gotoxy(60, 4);
}

void text_mod(MAP *map) {
    int mod = 0, choose = 0;
    bool over = false;
    is_hide_cursor(false);
    while(!over || game.error) {
        if (!game.error) {
            mod = 0;
            choose = 0;
            gotoxy(60, 4);
            printf("1:\"��\", 2:�аO, 3:���s�}�l, 4:�h�X��r�Ҧ�");
            gotoxy(60, 5);
            printf("�п�J�A�Q������: ");
            print_space();
            scanf("%d", &mod);
            clean_stdin();
            switch (mod) {
                case 1:
                    mod = 0;
                    choose = 1;
                    break;
                case 2:
                    mod = 0;
                    choose = 2;
                    break;
                case 3:
                    mod = 0;
                    choose = 0;
                    over = true;
                    game.over = true;
                    game.restart = true;
                    break;
                case 4:
                    mod = 0;
                    choose = 0;
                    over = true;
                    print_game(map, true);
                    break;
                default:
                    gotoxy(60, 6);
                    color_set(0xfc);
                    printf("��J���~!�Э��s��J!!");
                    color_set(0x07);
                    game.error = true;
                    choose = 0;   //�@�}�l�S��J���~���᭱���ɡA������J�W�@�ӿ�h
                    Sleep(3000);
                    gotoxy(60, 6);
                    for (int i = 0; i < 30; i++)
                        putchar(' ');
                    break;
            }
            if (choose != 0) {
                over = mod_choose(choose, map, true);
            }
        }
        else if (game.error) {
            game.error = false;
            if (choose != 0) {
                over = mod_choose(choose, map, true);
            }
        }
    }
    is_hide_cursor(true);
}
