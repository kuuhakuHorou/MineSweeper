#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
/*  #define LINES_EASY 9
    #define COLS_EASY 9
    #define LINES_NORMAL 16
    #define COLS_NORMAL 16
    #define LINES_HARD 30
    #define COLS_HARD 16 */

typedef enum {              //�W�X�a��       �w�аO��m
    OverRange, EnterError, OverCoordinate, MarkCoordinate
} Warning;

typedef enum {
    Map, Mark
} Type;

struct GAME{
    bool error;  //�C�����~(��J)
    bool over;   //�C������
    int flag;   //�C�����X�l�ƶq
    char continue_q;     //�C���~��߰�
};

struct SET{
    int lines;  //�a�ϴX��
    int cols;   //�a�ϴX�C
    int landboom;   //�a�p�ƶq
};

typedef struct MAP {
    int* map;    //�a��
    int* mark;   //�аO�a��
} MAP;

typedef struct COOR {
    int x;   //x
    int y;   //y
} Coor;

//���n�禡(important_funt.c)
void clean_stdin(void); //�M����J�w�İ�
void color_set(int);    //�����C��
void degree_of_difficulty(void);
void game_dif_choose(void); //�C���x���׿�h
void gotoxy(int, int);  //���w�y��
void print_space(void); //�L�ť�(10��)
void print_warning(Warning);    //ĵ�i
int map_location(Coor, Type);  //�a�Ϯy��
bool over_range(Coor);   //�p�⦳�L�W�X�a�Ͻd��
void reset(void);       //���s�C���Ѽ�
int location_value(MAP *, Coor, Type);  //�p��a�Ϧ�m�ƭ�

//�C�����e(game_content.c)
void game_content(MAP *);    //�C�����e
void game_start(MAP *);  //�]�w���
void landboom_generate(Coor, int *);   //�H���ͦ��a�p
void landboom_tester(Coor, MAP *);   //���ծ���K��a�p
void mod_choose_1(MAP *);        //"��"
void mod_choose_2(MAP *);        //�аO
void print_game(MAP *);          //����
