#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"
#include "utils.h"   // 공통 함수 사용

// -----------------------------
// 메인 메뉴 출력
// -----------------------------
void mainUi() {
    clearScreen();

    int select = 0;
    printf("\n");

    int width = 30; // 박스 내부 너비

    // 윗줄
    TitleOnBar(30);

    // 메뉴 항목들
    printMiddleLine("메인 메뉴", width);
    printMiddleLine("[1] 카테고리 관리", width);
    printMiddleLine("[2] 친구 관리", width);
    printMiddleLine("[3] 팀 관리", width);
    printMiddleLine("[0] 로그아웃", width);

    // 아랫줄
    TitleUnderBar(30);

    printf("입력: ");
    scanf("%d", &select);

    uiConnect(select);
}

// -----------------------------
// 메인 메뉴 입력 처리
// -----------------------------
void uiConnect(int select) {
    switch (select) {
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

// -----------------------------
// 카테고리 메뉴 연결
// -----------------------------
void categoryConnect(int select) {
    switch (select)
    {
    case 0:
        mainUi();
        break;
    case 1:
        inputCategoryName();
        break;
    case 2:
        retouchCategory();
        break;
    case 3:
        removeCategory();
        break;
    case 4:
        appendTodoInCategory();
        break;
    case 5:
        retouchTodoInCategory();
        break;
    case 6:
        completeTodoInCategory();
        break;
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
    category();
}

// -----------------------------
// 친구 메뉴 연결
// -----------------------------
void friendsConnect(int select) {
    switch (select)
    {
    case 0:
        mainUi();
        break;
    case 1:
        appendfriend();
        break;
    case 2:
        removefriend();
        break;
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
    friends();
}

// -----------------------------
// 팀 메뉴 연결
// -----------------------------
void teamsConnect(int select) {
    switch (select)
    {
    case 0:
        mainUi();
        break;
    case 1:
        inputTeamName();
        break;
    case 2:
        retouchTeam();
        break;
    case 3:
        removeTeam();
        break;
    case 4:
        selectTeamForTask(1); // 팀 할일 추가
        break;
    case 5:
        selectTeamForTask(2); // 팀 할일 삭제
        break;
    case 6:
        selectTeamForTask(3);
        break;
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
    teams();
}