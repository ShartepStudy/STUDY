#ifndef _CONST_H_
#define _CONST_H_

enum EDirection { ALL, LEFT, RIGHT, UP, DOWN };

//    ������� ���� � ������� ���������� �������� �������� ����
const char GAME_POLE_SIZE = 10;

//    ���������� ����� �������� ������
const char GAME_POLE_INTERVAL = 5;

//    ������� ������������ ������ ������ 
const char GAME_SCREEN_WIDTH = GAME_POLE_INTERVAL*4 + GAME_POLE_SIZE*4;
const char GAME_SCREEN_HEIGHT = GAME_POLE_INTERVAL*3 + GAME_POLE_SIZE*2;

//    ������� ������������ �� ���� ���
const wchar_t EMPTY_NON_SHOOTED_CHAR = 0x0000;
const wchar_t EMPTY_SHOOTED_CHAR = 0x2022;
const wchar_t COMP_SHIP_NON_SHOOTED_CHAR = L'+'; //0x00A0; //
const wchar_t PLAYER_SHIP_NON_SHOOTED_CHAR = L'*'; //
const wchar_t SHIP_SHOOTED_CHAR = L'#';

//    ���� ��������������� ��������� ������
const char EMPTY_NON_SHOOTED = 0;
const char EMPTY_SHOOTED = 1;
const char SHIP_NON_SHOOTED = 2;
const char SHIP_SHOOTED = 3;
const char STATE_NON_DEFINE = 99;

//    ���� ��������������� ��������� ��������
const char ERROR_SHOOT = 0;
const char FAIL_SHOOT = 1;
const char HURT_SHOOT = 2;
const char KILLED_SHOOT = 3;

//    ���� ��������������� ����������� �������� ��������
const char RIGHT_DIRECT = 1;
const char DOWN_DIRECT = 2;
const char LEFT_DIRECT = 3;
const char UP_DIRECT = 4;

//    ������ ����������� �������
const char BIGGEST_SHIP_SIZE = 4;

const float GAME_DELAY = 0.2f;
#endif