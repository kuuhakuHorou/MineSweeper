#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define LINES 9
#define COLS 9

void game(void);    //�C�����e
void game_start(void);  //�]�w���
void gotoxy(int,int);   //���w�y��
void landboom_generate(void);   //�H���ͦ��a�p
void landboom_tester(int,int);  //���ծ���K��a�p
void mod_choose_1(void);        //"��"
void mod_choose_2(void);        //�аO
void print_game(void);          //����