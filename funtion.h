#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define LINES_EASY 9
#define COLS_EASY 9
#define LINES_NORMAL 16
#define COLS_NORMAL 16
#define LINES_HARD 30
#define COLS_HARD 16

//���n�禡(important_funt.c)
void color_set(int);    //�����C��
void game_dif_choose(void); //�C���x���׿�h
void gotoxy(int,int);   //���w�y��

//9��9���a��(²��)(funt_dif_1.c)
void game_easy(void);    //�C�����e
void game_start_easy(void);  //�]�w���
void landboom_generate_easy(int *,int *);   //�H���ͦ��a�p
void landboom_tester_easy(int,int);  //���ծ���K��a�p
void mod_choose_1_easy(void);        //"��"
void mod_choose_2_easy(void);        //�аO
void print_game_easy(void);          //����

//16��16���a��(���q)(funt_dif_2.c)
void game_normal(void);    //�C�����e
void game_start_normal(void);  //�]�w���
void landboom_generate_normal(int *,int *);   //�H���ͦ��a�p
void landboom_tester_normal(int,int);  //���ծ���K��a�p
void mod_choose_1_normal(void);        //"��"
void mod_choose_2_normal(void);        //�аO
void print_game_normal(void);          //����

//16��30���a��(�x��)(funt_dif_3.c)
void game_hard(void);    //�C�����e
void game_start_hard(void);  //�]�w���
void landboom_generate_hard(int *,int *);   //�H���ͦ��a�p
void landboom_tester_hard(int,int);  //���ծ���K��a�p
void mod_choose_1_hard(void);        //"��"
void mod_choose_2_hard(void);        //�аO
void print_game_hard(void);          //����
