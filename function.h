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
    bool restart;   //�C�����s�}�l
    bool sweep_landboom;    //��쬵�u
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
bool compare_coor(Coor, Coor);   //
void degree_of_difficulty(void);    //�ۭq�a�ϸ�T
void game_dif_choose(void); //�C���x���׿�h
void gotoxy(int, int);  //���w�y��
int location_value(MAP *, Coor, Type);  //�p��a�Ϧ�m�ƭ�
int map_location(Coor, Type);  //�a�Ϯy��
bool over_range(Coor);   //�p�⦳�L�W�X�a�Ͻd��
void print_space(void); //�L�ť�(10��)
void print_warning(Warning);    //ĵ�i
void reset(void);       //���s�C���Ѽ�
void reset_game(void);  //���]game�Ѽ�
void reset_set(void);   //���]set�Ѽ�

//�C�����e(game_content.c)
void game_content(MAP *);    //�C�����e
void game_start(MAP *);  //�]�w���
void is_win(MAP *);  //���լO�_Ĺ�F
void landboom_generate(Coor, int *);   //�H���ͦ��a�p
void landboom_tester(Coor, MAP *);   //���ծ���K��a�p
void mod_choose_1(MAP *);        //"��"
void mod_choose_2(MAP *);        //�аO
void print_game(MAP *);          //����
