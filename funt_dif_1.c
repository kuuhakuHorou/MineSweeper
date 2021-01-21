#include "funtion.h"

int map_1[LINES_EASY+2][COLS_EASY+2];       //�a��
int map_mark_1[LINES_EASY][COLS_EASY]={0};  //�аO�a��

void game_easy() {   //�C�����e
    int i, j, mod, mod_choose;
    game.over=0;
    game_start_easy();
    print_game_easy();
    while (1) {
        if (game.error==0) {
            gotoxy(40,1);
            printf("�п�J�A�Q������(1:\"��\"�A2:�аO): ");
            for (i=0;i<10;i++)
                putchar(' ');
            for (i=0;i<10;i++)
                putchar('\b');
            scanf("%d", &mod);
            fflush(stdin);  //�M����J�w�İϡA�H���ÿ�J
            switch (mod) {
                case 1:
                    mod_choose=1;
                    break;
                case 2:
                    mod_choose=2;
                    break;
                default:
                    gotoxy(45,5);
                    color_set(12);
                    printf("��J���~!�Э��s��J!!");
                    color_set(7);
                    game.error=1;
                    mod_choose=0;   //�@�}�l�S��J���~���᭱���ɡA������J�W�@�ӿ�h
                    Sleep(3000);
                    gotoxy(45,5);
                    for (i=0;i<21;i++)
                        putchar(' ');
                    break;
            }
            if (mod_choose==1) {
                mod_choose_1_easy();
            }
            else if (mod_choose==2) {
                mod_choose_2_easy();
            }
        }
        else if (game.error==1) {
            game.error=0;
            if (mod_choose==1)
                mod_choose_1_easy();
            else if (mod_choose==2)
                mod_choose_2_easy();
        }
        
        if (game.over==1) {
            gotoxy(45,11);
            break;
        }
    }
}

void game_start_easy() {     //�C���}�l�]�w
    int i, j, enter_x, enter_y, error;
    for (i=0;i<LINES_EASY+2;i++) {
        for (j=0;j<COLS_EASY+2;j++) {
            if (i==0||i==LINES_EASY+1||j==0||j==COLS_EASY+1)
                map_1[i][j]=99;   //99�����
            else 
                map_1[i][j]=0;    //0���Ŧa
        }
    }
    while (1) {
        error=0;
        print_game_easy();
        gotoxy(40,1);
        printf("�Х���J�@�Ӯy��(x y): ");
        scanf("%d%d", &enter_y, &enter_x);
        fflush(stdin);
        if (enter_x>COLS_EASY||enter_x<1||enter_y>LINES_EASY||enter_y<1) {
            error=1;
            gotoxy(45,5);
            color_set(252);
            printf("�Ф��n�ÿ�J��!");
            color_set(7);
            Sleep(3000);
        }
        if (error!=1)
            break;
    }
    map_1[enter_y][enter_x]=10;
    landboom_generate_easy(&enter_x,&enter_y);    //�ͦ��a�p
    landboom_tester_easy(enter_x,enter_y);
}

void landboom_generate_easy(int *enter_x, int *enter_y) {  //�H���ͦ��a�p
    srand(time(0));
    int i, j, produce_x, produce_y, landboom_num=0;
    do {
        produce_x=rand()%COLS_EASY+1;
        produce_y=rand()%LINES_EASY+1;
        if (map_1[produce_y][produce_x]!=20&&produce_x!=*enter_x&&produce_y!=*enter_y) {
            map_1[produce_y][produce_x]=20;   //20���a�p
            landboom_num++;
        }
    } while (landboom_num<10);
/*    for (int i=0;i<landboom_num;i++) {
 *       produce_x=rand()%COLS_EASY+1;
 *       produce_y=rand()%LINES_EASY+1;
 *       if (map_1[produce_y][produce_x]==20)  //�w�g���a�p�����p
 *           i--;
 *       map_1[produce_y][produce_x]=20;   //20���a�p
 *   }
 */
}

void landboom_tester_easy(int x,int y) { //���ծ���K��a�p
    int i, j, landboom;
    landboom=0; //����a�p��
    
    for (i=y-1;i<=y+1;i++) {        //���թP��a�p
        for (j=x-1;j<=x+1;j++) {
            if (i==y&&j==x)     //�򪺨��椣�κ�
                continue;
            else if (map_1[i][j]==20)
                landboom++;
        }
    }
    
    if (landboom==0) {
        map_1[y][x]=10;   //����S�a�p
        for (i=y-1;i<=y+1;i++) {
            for (j=x-1;j<=x+1;j++) {
                if (map_1[i][j]==0)     //�٨S��L���a��
                    landboom_tester_easy(j,i);
            }
        }
    }
    else
        map_1[y][x]=landboom;  //���䦳�a�p(��X�h��)
}

void mod_choose_1_easy() {   //"��"
    int i, j, guess_x, guess_y, untreated_items;
    gotoxy(40,2);
    printf("�п�J�A�Q���(x y): ");
    for (i=0;i<10;i++)
        putchar(' ');
    for (i=0;i<10;i++)
        putchar('\b');
    scanf("%d%d", &guess_y, &guess_x);
    fflush(stdin);  //�M����J�w�İϡA�H���ÿ�J
    if (guess_x>COLS_EASY||guess_x<1||guess_y>LINES_EASY||guess_y<1) {    //�W�X�a�p�d��
        gotoxy(45,5);
        color_set(12);
        printf("��J���~!�Э��s��J!!");
        color_set(7);
        game.error=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        return;
    }
    else if (map_mark_1[guess_y-1][guess_x-1]==1) {
        gotoxy(45,5);
        color_set(12);
        printf("�A�����аO���a��!");
        color_set(7);
        game.error=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        return;
    }
    else if (map_1[guess_y][guess_x]==20) {
        for (i=0;i<LINES_EASY+2;i++) {
            for (j=0;j<COLS_EASY+2;j++) {
                if (map_1[i][j]==20)
                    map_1[i][j]++;  //��F�H��ܦa�p�B
                else if (map_mark_1[i-1][j-1]==1&&map_1[i][j]<20)
                    map_mark_1[i-1][j-1]=2;   //�аO���~�A����~��{�X��
            }
        }
        print_game_easy();
        gotoxy(45,10);
        printf("�A��F");
        game.over=1;
        return;
    }
    landboom_tester_easy(guess_x,guess_y);
    print_game_easy();
    untreated_items=0;  //����S��L���a
    for (i=0;i<LINES_EASY+2;i++) {
        for (j=0;j<COLS_EASY+2;j++) {
            if (map_1[i][j]==0) {
                untreated_items++;
            }
            else if (map_1[i][j]<20) {
                continue;   //��L�B����a�p�B
            }
        }
    }
    if (untreated_items==0) {
        for (i=0;i<LINES_EASY+2;i++) {
            for (j=0;j<COLS_EASY+2;j++) {
                if (map_1[i][j]==20)
                    map_1[i][j]=30; //��{�a�p�B
            }
        }
        print_game_easy();
        gotoxy(45,10);
        printf("�AĹ�F");
        game.over=1;
        return;
    }
}

void mod_choose_2_easy() {   //�аO
    int i, mark_x, mark_y;
    gotoxy(40,2);
    printf("�п�J�A�Q�аO��(x y): ");
    for (i=0;i<10;i++)
        putchar(' ');
    for (i=0;i<10;i++)
        putchar('\b');
    scanf("%d%d", &mark_y, &mark_x);
    fflush(stdin);  //�M����J�w�İϡA�H���ÿ�J
    if (mark_x>COLS_EASY||mark_x<1||mark_y>LINES_EASY||mark_y<1) {//�W�X�a�p�d��
        gotoxy(45,5);
        color_set(12);
        printf("��J���~!�Э��s��J!!");
        color_set(7);
        game.error=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        return;
    }
    else if (map_1[mark_y][mark_x]==20||map_1[mark_y][mark_x]==0) {
        if (map_mark_1[mark_y-1][mark_x-1]==0) {
            map_mark_1[mark_y-1][mark_x-1]=1; //�аO
            game.flag++;
            print_game_easy();
        }
        else if (map_mark_1[mark_y-1][mark_x-1]==1) {
            map_mark_1[mark_y-1][mark_x-1]=0; //�M���аO
            game.flag--;
            print_game_easy();
        }
    }
    else
        print_game_easy();
}

void print_game_easy() { //����
    system("cls");
    int i, j;
    printf("�@ �@y��\n�@�@�@");
    for (i=1;i<10;i++)
        printf("%2d", i);
    printf("\n x\n��");  //�U����]�p
/*  gotoxy(2,3);
 *  printf("x");
 *  gotoxy(1,4);
 *  printf("��");
 */
    for (i=1;i<10;i++) {
        gotoxy(3,i+3);
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
    gotoxy(14,1);
    printf("�a�p��:10");
    gotoxy(25,1);
    printf("�X�l��:%2d", game.flag);
    for (i=0;i<LINES_EASY+2;i++) {
        gotoxy(5,i+3);
        for (j=0;j<COLS_EASY+2;j++) {
            if (map_1[i][j]==99)
                printf("��");         //���
            else if (map_1[i][j]==10)
                printf("�@");    //��L���Ŧa
            else if (map_1[i][j]==0||map_1[i][j]==20) {
                if (map_mark_1[i-1][j-1]==0)
                    printf("��");     //�٨S��L���a��&�a�p
                else if (map_mark_1[i-1][j-1]==1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
                else if (map_mark_1[i-1][j-1]==2) {
                    color_set(12);
                    printf("�Y");     //�аO���~��{
                }
            }
            else if (map_1[i][j]<10)
                printf(" %d", map_1[i][j]); //��L�B���䦳�a�p�A��{�a�p��
            else if (map_1[i][j]==21) {
                if (map_mark_1[i-1][j-1]==0) {
                    color_set(14);
                    printf("��");    //�����a�p�B
                }
                else if (map_mark_1[i-1][j-1]==1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
            }
            else if (map_1[i][j]==30) {
                if (map_mark_1[i-1][j-1]==0) {
                    color_set(11);
                    printf("��");    //�L����ܦa�p
                }
                else if (map_mark_1[i-1][j-1]==1) {
                    color_set(12);
                    printf("��");    //�a�p�аO��{
                }
            }
            color_set(7);
        }
    }
    putchar('\n');
}