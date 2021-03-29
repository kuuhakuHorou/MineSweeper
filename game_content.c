#include "function.h"

extern struct GAME game;
extern struct SET set;

void game_content(MAP *map) {   //�C�����e
    int mod = 0, mod_choose = 0;
    game.over = false;
    game.error = false;
    map->map = (int*)calloc((set.lines + 2) * (set.cols + 2), sizeof(int));  //�a��
    map->mark = (int*)calloc(set.lines * set.cols, sizeof(int));     //�аO�a��
/*  for (i=0;i<set.lines;i++) {
        for (j=0;j<set.cols;j++) {
            *(map_mark+set.cols*i+j)=0;
        }
    } */
    game_start(map);
    print_game(map);
    while (!game.over) {
        if (!game.error) {
            gotoxy(60, 1);
            printf("�п�J�A�Q������(1:\"��\"�A2:�аO): ");
            print_space();
            scanf("%d", &mod);
            clean_stdin();
            switch (mod) {
                case 1:
                    mod = 0;
                    mod_choose = 1;
                    break;
                case 2:
                    mod = 0;
                    mod_choose = 2;
                    break;
                default:
                    gotoxy(60, 2);
                    color_set(252);
                    printf("��J���~!�Э��s��J!!");
                    color_set(7);
                    game.error = true;
                    mod_choose = 0;   //�@�}�l�S��J���~���᭱���ɡA������J�W�@�ӿ�h
                    Sleep(3000);
                    gotoxy(60, 2);
                    for (int i = 0; i < 21; i++)
                        putchar(' ');
                    break;
            }
            if (mod_choose == 1) {
                mod_choose_1(map);
            }
            else if (mod_choose == 2) {
                mod_choose_2(map);
            }
        }
        else if (game.error) {
            game.error = false;
            if (mod_choose == 1)
                mod_choose_1(map);
            else if (mod_choose == 2)
                mod_choose_2(map);
        }
    }
    color_set(7);
    gotoxy(60, 2);
    free(map->map);
    free(map->mark);
}

void game_start(MAP *map) {     //�C���}�l�]�w
    Coor loop;
    bool error = false;
    Coor enter = {0, 0};
    for (loop.y = 0; loop.y < set.lines + 2; loop.y++) {
        for (loop.x = 0; loop.x < set.cols + 2; loop.x++) {
            if (loop.y == 0 || loop.y == set.lines+1 || loop.x == 0 || loop.x == set.cols+1)
                map->map[map_location(loop, Map)] = 99;   //99�����
            else
                map->map[map_location(loop, Map)] = 0;    //0���Ŧa
        }
    }
    do {
        error = false;
        print_game(map);
        gotoxy(60, 1);
        printf("�Х���J�@�Ӯy��(x y): ");
        scanf("%d%d", &enter.y, &enter.x);
        fflush(stdin);
        if (over_range(enter)) {
            error = true;
            gotoxy(60,2);
            color_set(252);
            printf("�Ф��n�ÿ�J��!");
            color_set(7);
            Sleep(3000);
        }
    } while (error);
    map->map[map_location(enter, Map)] = 10;
    landboom_generate(enter, map->map);    //�ͦ��a�p
    landboom_tester(enter, map);
}

void landboom_generate(Coor test, int *map) {  //�H���ͦ��a�p
    srand(time(NULL));
    Coor produce;
    int landboom_num = 0;
    int *p_map;
    while (landboom_num < set.landboom) {
        produce.x = rand() % set.cols + 1;
        produce.y = rand() % set.lines + 1;
        p_map = map + map_location(produce, Map);
        if (*p_map != 20) {
            if (produce.x == test.x && produce.y == test.y) {
                continue;
            }
            *p_map = 20;   //20���a�p
            landboom_num++;
        }
    }
/*    for (int i=0;i<landboom_num;i++) {
 *       produce_x=rand()%COLS_EASY+1;
 *       produce_y=rand()%LINES_EASY+1;
 *       if (map_1[produce_y][produce_x]==20)  //�w�g���a�p�����p
 *           i--;
 *       map_1[produce_y][produce_x]=20;   //20���a�p
 *   }
 */
}

void landboom_tester(Coor test, MAP *map) { //���ծ���K��a�p
    Coor loop;
    int landboom = 0; //����a�p��

    for (loop.y = test.y - 1; loop.y <= test.y + 1; loop.y++) {        //���թP��a�p
        for (loop.x = test.x - 1; loop.x <= test.x + 1; loop.x++) {
            if (loop.x == test.x && loop.y == test.y)     //�򪺨��椣�κ�
                continue;
            else if (location_value(map, loop, Map) == 20)
                landboom++;
        }
    }

    if (landboom == 0) {
        map->map[map_location(test, Map)] = 10;   //����S�a�p
        for (loop.y = test.y - 1; loop.y <= test.y + 1; loop.y++) {
            for (loop.x = test.x - 1; loop.x <= test.x + 1; loop.x++) {
                if (location_value(map, loop, Map) == 0 && location_value(map, loop, Mark) == 0)     //�٨S��L�B�S�аO���a��
                    landboom_tester(loop, map);
            }
        }
    }
    else
        map->map[map_location(test, Map)] = landboom;  //���䦳�a�p(��X�h��)
}

void mod_choose_1(MAP *map) {   //"��"
    Coor guess = {0, 0}, loop;
    int val_map, val_mark, untreated_places;
    gotoxy(60, 2);
    printf("�п�J�A�Q���(x y): ");
    print_space();
    scanf("%d%d", &guess.y, &guess.x);
    clean_stdin();
    val_map = location_value(map, guess, Map);
    val_mark = location_value(map, guess, Mark);
    if (over_range(guess)) {    //�W�X�a�p�d��
        print_warning(OverCoordinate);
        return;
    }
    else if (val_mark == 1) {
        print_warning(MarkCoordinate);
        return;
    }
    else if(val_map < 10 && val_map > 0) {
        int flags = 0;
        for (loop.y = guess.y - 1; loop.y <= guess.y + 1; loop.y++) {
            for (loop.x = guess.x - 1; loop.x <= guess.x + 1; loop.x++) {
                if (location_value(map, loop, Mark) == 1) {
                    flags++;
                }
            }
        }
        if (flags == val_map) {
            for (loop.y = guess.y - 1; loop.y <= guess.y + 1; loop.y++) {
                for (loop.x = guess.x - 1; loop.x <= guess.x + 1; loop.x++) {
                    if (location_value(map, loop, Map) == 0) {
                        landboom_tester(loop, map);
                    }
                }
            }
        }
    }
    else if (val_map == 20) {
        for (loop.y = 0; loop.y < set.lines + 2; loop.y++) {
            for (loop.x = 0; loop.x < set.cols + 2; loop.x++) {
                if (location_value(map, loop, Map) == 20)
                    map->map[map_location(loop, Map)] += 1;  //��F�H��ܦa�p�B
                else if (location_value(map, loop, Map) == 1 && location_value(map, loop, Map) < 20)
                    map->mark[map_location(loop, Mark)] = 2;   //�аO���~�A����~��{�X��
            }
        }
        print_game(map);
        gotoxy(60,1);
        color_set(192);
        printf("�A��F");
        game.over = true;
        return;
    }
    landboom_tester(guess, map);
    print_game(map);
    untreated_places = 0;  //����S��L���a
    for (loop.y = 0; loop.y < set.lines + 2; loop.y++) {
        for (loop.x = 0; loop.x < set.cols + 2; loop.x++) {
            if (location_value(map, loop, Map) == 0) {
                untreated_places++;
            }
            else if (location_value(map, loop, Map) < 20) {
                continue;   //��L�B����a�p�B
            }
        }
    }
    if (untreated_places == 0) {
        for (loop.y = 0; loop.y < set.lines + 2; loop.y++) {
            for (loop.x = 0; loop.x < set.cols + 2; loop.x++) {
                if (location_value(map, loop, Map) == 20)
                    map->map[map_location(loop, Map)] = 30; //��{�a�p�B
            }
        }
        print_game(map);
        gotoxy(60,1);
        color_set(224);
        printf("�AĹ�F");
        game.over = true;
        return;
    }
}

void mod_choose_2(MAP *map) {   //�аO
    Coor mark = {0, 0};
    int *p_mark;
    int val_map;
    gotoxy(60, 2);
    printf("�п�J�A�Q�аO��(x y): ");
    print_space();
    scanf("%d%d", &mark.y, &mark.x);
    clean_stdin();
    if (over_range(mark)) {//�W�X�a�p�d��
        print_warning(OverCoordinate);
        return;
    }
    val_map = location_value(map, mark, Map);
    if (val_map == 20 || val_map == 0) {
        p_mark = &map->mark[map_location(mark, Mark)];
        if (*p_mark == 0) {
            *p_mark = 1; //�аO
            game.flag++;
        }
        else if (*p_mark == 1) {
            *p_mark = 0; //�M���аO
            game.flag--;
        }
    }
    if (val_map > 0 ) {

    }
    print_game(map);
}

void print_game(MAP *map) { //����
    system("cls");
    Coor loop;
    int val_map, val_mark;
    printf("�@ �@y��\n�@�@�@");
    for (int i = 1; i < set.cols + 1; i++)
        printf("%2d", i);
    printf("\n x\n��");  //�U����]�p
/*  gotoxy(2,3);
 *  printf("x");
 *  gotoxy(1,4);
 *  printf("��");
 */
    for (int i = 1; i < set.lines + 1; i++) {
        gotoxy(3, i + 3);
        printf("%2d", i);
    }
/*  printf("�@�@ y��\n"        ���X
 *         "�@�@�@ 1 2 3 4 5 6 7 8 9\n"
 *         " x�@\n"
 *         "�� 1\n"
 *         "�@ 2\n"
 *         "�@ 3\n"
 *         "�@ 4\n"
 *         "�@ 5\n"
 *         "�@ 6\n"
 *         "�@ 7\n"
 *         "�@ 8\n"
 *         "�@ 9\n");
 */
    gotoxy(14, 1);
    printf("�a�p��:%d", set.landboom);
    gotoxy(25, 1);
    printf("�X�l��:%2d", game.flag);
    for (loop.y = 0; loop.y < set.lines + 2; loop.y++) {
        gotoxy(5, loop.y + 3);
        for (loop.x = 0; loop.x < set.cols + 2; loop.x++) {
            val_map = location_value(map, loop, Map);
            val_mark = location_value(map, loop, Mark);
            if (val_map == 99) {
                color_set(51);
                printf("��");         //���
            }
            else if (val_map == 10) {
                color_set(119);
                printf("��");    //��L���Ŧa
            }
            else if (val_map == 0 || val_map == 20) {
                if (val_mark == 0) {
                    color_set(135);
                    printf("��");     //�٨S��L���a��&�a�p
                }
                else if (val_mark == 1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
                else if (val_mark == 2) {
                    color_set(12);
                    printf("�Y");     //�аO���~��{
                }
            }
            else if (val_map < 10) {
                color_set(23);
                printf(" %d", val_map); //��L�B���䦳�a�p�A��{�a�p��
            }
            else if (val_map == 21) {
                if (val_mark == 0) {
                    color_set(14);
                    printf("��");    //�����a�p�B
                }
                else if (val_mark == 1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
            }
            else if (val_map == 30) {
                if (val_mark == 0) {
                    color_set(11);
                    printf("��");    //�L����ܦa�p
                }
                else if (val_mark == 1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
            }
            color_set(7);
        }
    }
    for (int i = 1; i <= 36; i++) {
        gotoxy(58, i);
        printf("|");
    }
}
