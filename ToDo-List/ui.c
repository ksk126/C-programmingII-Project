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

    printf("----------메인 메뉴---------\n");
    printf("[1] 카테고리 관리\n");
    printf("[2] 친구 관리\n");
    printf("[3] 팀 관리\n");
    printf("-----------------------\n");
    printf("[0] 로그아웃\n");
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
    switch (select) {
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
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
}

// -----------------------------
// 친구 메뉴 연결
// -----------------------------
void friendsConnect(int select) {
    switch (select) {
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
}

// -----------------------------
// 팀 메뉴 연결
// -----------------------------
void teamsConnect(int select) {
    switch (select) {
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
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
}