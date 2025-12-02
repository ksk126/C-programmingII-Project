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
    printFriendSummary();

    printf("----------친구 관리 메뉴---------\n");
    printf("[1] 친구 추가\n");
    printf("[2] 친구 삭제\n");
    printf("-----------------------\n");
    printf("[0] 뒤로 가기\n");
    printf("입력: ");
    scanf("%d", &select);

    friendsConnect(select);
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
void appendfriend()
{
    system("cls");
    char searchId[50];
    char memberPath[256];
    char myFriendPath[256];
    FILE* fp = NULL;
    FILE* fp2 = NULL;

    printf("추가할 친구 아이디 입력: ");
    scanf("%s", searchId);

    sprintf(memberPath, "C:\\TodoList\\%s\\list.txt", searchId);

    fp = fopen(memberPath, "r");
    if (fp == NULL)
    {
        printf("\n[오류] 존재하지 않는 회원입니다.\n");
        exit(0);
    }

    fclose(fp);

    strcpy(myFriendPath, pathfriends);

    fp = fopen(myFriendPath, "r");
    if (fp != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), fp))
        {
            line[strcspn(line, "\n")] = 0;
            if (strcmp(line, searchId) == 0)
            {
                printf("\n[안내] 이미 친구 목록에 존재하는 아이디입니다.\n");
                fclose(fp);
                Sleep(1500);
                return;
            }
        }
        fclose(fp);
    }
    fp2 = fopen(myFriendPath, "a");
    if (fp2 == NULL)
    {
        printf("\n[오류] friends.txt 파일을 열 수 없습니다.\n");
        Sleep(1500);
        return;
    }

    fprintf(fp2, "%s\n", searchId);
    fclose(fp2);

    printf("\n[성공] '%s' 친구 추가 완료.\n", searchId);
    Sleep(1500);
}

void removefriend()
{
    FILE* fp = fopen(pathfriends, "r");
    if (!fp) {
        printf("친구 목록 파일 열기 실패\n");
        Sleep(1000);
        return;
    }

    char friendsList[100][64];
    int count = 0;

    while (fscanf(fp, "%s", friendsList[count]) != EOF) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) {
        printf("삭제할 친구가 없습니다.\n");
        Sleep(1000);
        return;
    }

    printf("------ 친구 목록 ------\n");
    for (int i = 0; i < count; i++) {
        printf("[%d] %s\n", i + 1, friendsList[i]);
    }

    int select;
    printf("\n삭제할 번호 선택: ");
    scanf("%d", &select);

    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    char targetId[64];
    strcpy(targetId, friendsList[select - 1]);

    fp = fopen(pathfriends, "w");
    if (!fp) {
        printf("친구 목록 파일 쓰기 실패\n");
        Sleep(1000);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (i != select - 1)
            fprintf(fp, "%s\n", friendsList[i]);
    }
    fclose(fp);

    printf("\n'%s' 친구 삭제 완료.\n", targetId);
    Sleep(1000);
}

void printFriendSummary()
{
    FILE* fp = fopen(pathfriends, "r");
    if (!fp) { printf("친구 없음\n"); return; }

    char friendsList[100][64];
    int count = 0;
    while (fscanf(fp, "%s", friendsList[count]) != EOF) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    printf("------ 친구 목록 ------\n");
    if (count == 0) printf("(친구 없음)\n");
    else {
        for (int i = 0; i < count; i++) {
            printf("- %s\n", friendsList[i]);
        }
    }
    printf("-----------------------\n");

    return;
}