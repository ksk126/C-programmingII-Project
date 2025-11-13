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

void friends()
{
    system("cls");
    int select = 0;
    printf("----------친구 관리 메뉴---------\n");
    printf("[1] 친구 추가\n");
    printf("[2] 친구 삭제\n");
    printf("-----------------------\n");
    printf("[0] 뒤로 가기\n");
    printf("입력: ");
    scanf("%d", &select);
    return;
}

void friendsConnect(int select)
{
    switch (select)
    {
    case 0:
        mainUi();
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