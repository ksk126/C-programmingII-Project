#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"

// 메뉴 출력
void mainUi()
{
    system("cls");

    int select = 0;
    print0check();
    printf("\n");

    printf("----------메인 메뉴---------\n");
    printf("[1] 카테고리 관리\n");
    printf("[2] 친구 관리\n");
    printf("[3] 팀 관리\n");
    printf("-----------------------\n");
    printf("[0] 로그아웃\n");
    printf("입력: ");
    scanf("%d", &select);

    uiConnect(select);

    return;
}

// ui입력 처리
void uiConnect(int select)
{
    switch (select)
    {
    case 0:
        login(1);
        break;

    case 1:
        category();
        break;

    case 2:
        friends();
        break;

    case 3:
        teams();
        break;

    case 4:
        exit(0);

    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
}