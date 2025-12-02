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
// 친구 관리 메뉴
// -----------------------------
void friends() {
    clearScreen();
    int select = 0;
    printFriendSummary();

    printf("----------친구 관리 메뉴---------\n");
    printf("[1] 친구 추가\n");
    printf("[2] 친구 삭제\n");
    printf("-----------------------\n");
    printf("[0] 뒤로 가기\n");
    printf("입력: ");
    scanf("%d", &select);

    friendsConnect(select);
}

// -----------------------------
// 친구 추가
// -----------------------------
void appendfriend() {
    clearScreen();
    char searchId[64];
    char memberPath[256];

    printf("추가할 친구 아이디 입력: ");
    scanf("%s", searchId);

    sprintf(memberPath, "C:\\TodoList\\%s\\list.txt", searchId);

    FILE* fp = fopen(memberPath, "r");
    if (fp == NULL) {
        printf("\n[오류] 존재하지 않는 회원입니다.\n");
        Sleep(1500);
        return;
    }
    fclose(fp);

    // 이미 친구인지 확인
    fp = fopen(pathfriends, "r");
    if (fp != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), fp)) {
            trimNewline(line);
            if (strcmp(line, searchId) == 0) {
                printf("\n[안내] 이미 친구 목록에 존재하는 아이디입니다.\n");
                fclose(fp);
                Sleep(1500);
                return;
            }
        }
        fclose(fp);
    }

    FILE* fp2 = fopen(pathfriends, "a");
    if (fp2 == NULL) {
        printf("\n[오류] friends.txt 파일을 열 수 없습니다.\n");
        Sleep(1500);
        return;
    }

    fprintf(fp2, "%s\n", searchId);
    fclose(fp2);

    printf("\n[성공] '%s' 친구 추가 완료.\n", searchId);
    Sleep(1500);
}

// -----------------------------
// 친구 삭제
// -----------------------------
void removefriend() {
    char friendsList[100][64];
    int count = loadListFromFile(pathfriends, friendsList, 100);

    if (count == 0) {
        printf("삭제할 친구가 없습니다.\n");
        Sleep(1000);
        return;
    }

    printList(friendsList, count, "친구 목록");
    int select = selectFromList(count, "\n삭제할 번호 선택: ");
    if (select == -1) return;

    char targetId[64];
    strcpy(targetId, friendsList[select - 1]);

    FILE* fp = fopen(pathfriends, "w");
    if (!fp) {
        printf("친구 목록 파일 쓰기 실패\n");
        Sleep(1000);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (i != select - 1) {
            fprintf(fp, "%s\n", friendsList[i]);
        }
    }
    fclose(fp);

    printf("\n'%s' 친구 삭제 완료.\n", targetId);
    Sleep(1000);
}

// -----------------------------
// 친구 목록 요약 출력
// -----------------------------
void printFriendSummary() {
    char friendsList[100][64];
    int count = loadListFromFile(pathfriends, friendsList, 100);

    printf("------ 친구 목록 ------\n");
    if (count == 0) {
        printf("(친구 없음)\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            printf("- %s\n", friendsList[i]);
        }
    }
    printf("-----------------------\n");
}