#include "funtion.h"

int map[LINES+2][COLS+2];       //��l�a��
int map_guess[LINES+2][COLS+2]; //�C���̨ϥΪ��a��
int map_mark[LINES][COLS]={0};  //�аO�a��
int error_enter;    //���~��J
int game_over;      //�C������

void game() {   //�C�����e
    int i, j, mod, mod_choose;
    game_over=0;
    game_start();
    print_game();
    while (1) {
        if (error_enter==0) {
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
                    printf("��J���~!�Э��s��J!!");
                    error_enter=1;
                    mod_choose=0;   //�@�}�l�S��J���~���᭱���ɡA������J�W�@�ӿ�h
                    Sleep(3000);
                    gotoxy(45,5);
                    for (i=0;i<21;i++)
                        putchar(' ');
                    for (i=0;i<21;i++)
                        putchar('\b');
                    break;
            }
            if (mod_choose==1) {
                mod_choose_1();
            }
            else if (mod_choose==2) {
                mod_choose_2();
            }
        }
        else if (error_enter==1) {
            error_enter=0;
            if (mod_choose==1)
                mod_choose_1();
            else if (mod_choose==2)
                mod_choose_2();
        }
        
        if (game_over==1) {
            gotoxy(45,11);
            break;
        }
    }
}

void game_start() {     //�]�w���
    int i, j;
    for (i=0;i<LINES+2;i++) {
        for (j=0;j<COLS+2;j++) {
            if (i==0||i==LINES+1||j==0||j==COLS+1)
                map[i][j]=99;   //99�����
            else 
                map[i][j]=0;    //0���Ŧa
        }
    }
    landboom_generate();    //�ͦ��a�p
    for (i=0;i<LINES+2;i++) {
        for (j=0;j<COLS+2;j++) {
            map_guess[i][j]=map[i][j];
        }
    }
}

void gotoxy(int x,int y) {  //���w�y��
    COORD c;
    c.X=x-1;
    c.Y=y-1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void landboom_generate() {  //�H���ͦ��a�p
    srand(time(0));
    int produce_x, produce_y, landboom_num=10;
    for (int i=0;i<landboom_num;i++) {
        produce_x=rand()%COLS+1;
        produce_y=rand()%LINES+1;
        if (map[produce_y][produce_x]==20)  //�w�g���a�p�����p
            i--;
        map[produce_y][produce_x]=20;   //20���a�p
    }
}

void landboom_tester(int x,int y) { //���ծ���K��a�p
    int i, j, landboom;
    landboom=0; //����a�p��
    
    for (i=y-1;i<=y+1;i++) {        //���թP��a�p
        for (j=x-1;j<=x+1;j++) {
            if (i==y&&j==x)     //�򪺨��椣�κ�
                continue;
            else if (map[i][j]==20)
                landboom++;
        }
    }
    
    if (landboom==0) {
        map_guess[y][x]=10;   //����S�a�p
        for (i=y-1;i<=y+1;i++) {
            for (j=x-1;j<=x+1;j++) {
                if (map_guess[i][j]==0)     //�٨S��L���a��
                    landboom_tester(j,i);
            }
        }
    }
    else
        map_guess[y][x]=landboom;  //���䦳�a�p(��X�h��)
}

void mod_choose_1() {   //"��"
    int i, j, guess_x, guess_y, untreated_items;
    gotoxy(40,2);
    printf("�п�J�A�Q���: ");
    for (i=0;i<10;i++)
        putchar(' ');
    for (i=0;i<10;i++)
        putchar('\b');
    scanf("%d%d", &guess_y, &guess_x);
    fflush(stdin);  //�M����J�w�İϡA�H���ÿ�J
    if (guess_x>COLS||guess_x<1||guess_y>LINES||guess_y<1) {    //�W�X�a�p�d��
        gotoxy(45,5);
        printf("��J���~!�Э��s��J!!");
        error_enter=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        for (i=0;i<21;i++)
            putchar('\b');
        return;
    }
    else if (map_mark[guess_y-1][guess_x-1]==1) {
        gotoxy(45,5);
        printf("�A�����аO���a��!");
        error_enter=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        for (i=0;i<21;i++)
            putchar('\b');
        return;
    }
    else if (map_guess[guess_y][guess_x]==20) {
        for (i=0;i<LINES+2;i++) {
            for (j=0;j<COLS+2;j++) {
                if (map_guess[i][j]==20)
                    map_guess[i][j]++;  //��F�H��ܦa�p�B
                else if (map_mark[i-1][j-1]==1&&map_guess[i][j]<20)
                    map_mark[i-1][j-1]=2;   //�аO���~�A����~��{�X��
            }
        }
        print_game();
        gotoxy(45,10);
        printf("�A��F");
        game_over=1;
        return;
    }
    landboom_tester(guess_x,guess_y);
    print_game();
    untreated_items=0;  //����S��L���a
    for (i=0;i<LINES+2;i++) {
        for (j=0;j<COLS+2;j++) {
            if (map_guess[i][j]==0) {
                untreated_items++;
            }
            else if (map_guess[i][j]<20) {
                continue;   //��L�B����a�p�B
            }
        }
    }
    if (untreated_items==0) {
        for (i=0;i<LINES+2;i++) {
            for (j=0;j<COLS+2;j++) {
                if (map_guess[i][j]==20)
                    map_guess[i][j]=30; //��{�a�p�B
            }
        }
        print_game();
        gotoxy(45,10);
        printf("�AĹ�F");
        game_over=1;
        return;
    }
}

void mod_choose_2() {   //�аO
    int i, mark_x, mark_y;
    gotoxy(40,2);
    printf("�п�J�A�Q�аO��: ");
    scanf("%d%d", &mark_y, &mark_x);
    fflush(stdin);  //�M����J�w�İϡA�H���ÿ�J
    if (mark_x>COLS||mark_x<1||mark_y>LINES||mark_y<1) {//�W�X�a�p�d��
        gotoxy(45,5);
        printf("��J���~!�Э��s��J!!");
        error_enter=1;
        Sleep(3000);
        gotoxy(45,5);
        for (i=0;i<21;i++)
            putchar(' ');
        for (i=0;i<21;i++)
            putchar('\b');
        return;
    }
    else if (map_mark[mark_y-1][mark_x-1]==0) {
        map_mark[mark_y-1][mark_x-1]=1; //�аO
        print_game();
    }
    else if (map_mark[mark_y-1][mark_x-1]==1) {
        map_mark[mark_y-1][mark_x-1]=0; //�M���аO
        print_game();
    }
}

void print_game() { //����
    system("cls");
    int i, j;
    printf("�@ �@y��\n"
           "�@�@�@ 1 2 3 4 5 6 7 8 9\n"
           " x�@\n"
           "�� 1\n"
           "�@ 2\n"
           "�@ 3\n"
           "�@ 4\n"
           "�@ 5\n"
           "�@ 6\n"
           "�@ 7\n"
           "�@ 8\n"
           "�@ 9\n");
    for (i=0;i<LINES+2;i++) {
        gotoxy(5,i+3);
        for (j=0;j<COLS+2;j++) {
            if (map_guess[i][j]==99)
                printf("��");         //���
            else if (map_guess[i][j]==10)
                printf("�@");    //��L���Ŧa
            else if (map_guess[i][j]==0||map_guess[i][j]==20) {
                if (map_mark[i-1][j-1]==0)
                    printf("��");     //�٨S��L���a��&�a�p
                else if (map_mark[i-1][j-1]==1)
                    printf("��");    //�a�p�аO��{
                else if (map_mark[i-1][j-1]==2)
                    printf("�Y");     //�аO���~��{
            }
            else if (map_guess[i][j]<10)
                printf(" %d", map_guess[i][j]); //��L�B���䦳�a�p�A��{�a�p��
            else if (map_guess[i][j]==21) {
                if (map_mark[i-1][j-1]==0)
                    printf("��");    //�����a�p�B
                else if (map_mark[i-1][j-1]==1)
                    printf("��");    //�a�p�аO��{
            }
            else if (map_guess[i][j]==30) {
                if (map_mark[i-1][j-1]==0)
                    printf("��");    //�L����ܦa�p
                else if (map_mark[i-1][j-1]==1)
                    printf("��");    //�a�p�аO��{
            }
        }
    }
    putchar('\n');
}