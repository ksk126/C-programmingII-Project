#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"

// 팀 요약 출력 (상단에 팀별 할일 목록)
void printTeamSummary()
{
    FILE* fp = fopen(pathteamsFile, "r");
    printf("------ 팀별 할일 목록 ------\n");
    if (!fp) { printf("(팀 없음)\n"); return; }

    char line[128];
    int anyTeam = 0;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '\0') continue;
        anyTeam = 1;

        char teamName[64];
        char* openParen = strchr(line, '(');
        if (openParen) {
            strncpy(teamName, line, openParen - line);
            teamName[openParen - line] = '\0';
        }
        else {
            strcpy(teamName, line);
        }

        printf("[%s]\n", teamName);

        char teamListPath[256];
        sprintf(teamListPath, "%s\\%s\\list.txt", pathteamsDir, teamName);
        FILE* tf = fopen(teamListPath, "r");
        if (!tf) { printf("(할일 없음)\n"); continue; }

        char taskLine[128];
        int printed = 0;
        while (fgets(taskLine, sizeof(taskLine), tf)) {
            taskLine[strcspn(taskLine, "\n")] = 0;
            if (taskLine[0] != '\0') {
                printf("- %s\n", taskLine);
                printed = 1;
            }
        }
        fclose(tf);

        if (!printed) printf("(할일 없음)\n");
    }
    fclose(fp);

    if (!anyTeam) printf("(등록된 팀 없음)\n");
    printf("----------------------------------\n");
}

// 팀 메뉴
void teams()
{
    int select = -1;
    while (select != 0) {
        system("cls");
        printTeamSummary();   // 상단 요약 출력

        printf("----------팀 관리 메뉴---------\n");
        printf("[1] 팀 추가\n");
        printf("[2] 팀 수정 (이름)\n");
        printf("[3] 팀 삭제\n");
        printf("[4] 팀 할일 추가\n");
        printf("[5] 팀 할일 삭제\n");
        printf("[0] 뒤로 가기\n");
        printf("입력: ");
        if (scanf("%d", &select) != 1) { fflush(stdin); select = -1; continue; }
        teamsConnect(select);
    }
}

// 메뉴 연결
void teamsConnect(int select)
{
    switch (select)
    {
    case 0: mainUi(); break;
    case 1: inputTeamName(); break;
    case 2: retouchTeam(); break;
    case 3: removeTeam(); break;
    case 4: selectTeamForTask(1); break; // 팀 할일 추가
    case 5: selectTeamForTask(2); break; // 팀 할일 삭제
    default: printf("잘못 입력하였습니다.\n"); Sleep(1000); break;
    }
}

// 팀 추가
void inputTeamName()
{
    char teamName[64];
    printf("추가할 팀 이름: ");
    scanf("%63s", teamName);

    // 친구 목록 불러오기
    FILE* fp = fopen(pathfriends, "r");
    if (!fp) { printf("친구 목록 파일 열기 실패\n"); Sleep(1000); return; }

    char friendsList[100][64];
    int count = 0;
    while (fscanf(fp, "%63s", friendsList[count]) != EOF) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("친구가 없습니다. 팀을 만들 수 없습니다.\n"); Sleep(1000); return; }

    printf("------ 친구 목록 ------\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, friendsList[i]);

    // 팀원 선택
    char teamMembersCSV[256] = "";
    int select;
    printf("팀원 선택 (0 입력 시 종료):\n");
    while (1) {
        printf("번호 입력: ");
        if (scanf("%d", &select) != 1) { fflush(stdin); continue; }
        if (select == 0) break;
        if (select < 1 || select > count) { printf("잘못된 선택입니다.\n"); continue; }

        if (strstr(teamMembersCSV, friendsList[select - 1]) == NULL) {
            if (strlen(teamMembersCSV) > 0) strcat(teamMembersCSV, ",");
            strcat(teamMembersCSV, friendsList[select - 1]);
        }
    }

    if (strlen(teamMembersCSV) == 0) {
        printf("팀원이 선택되지 않았습니다.\n"); Sleep(1000); return;
    }

    // 내 teams.txt에 기록
    FILE* myTeams = fopen(pathteamsFile, "a");
    if (!myTeams) { printf("내 teams.txt 열기 실패\n"); Sleep(1000); return; }
    fprintf(myTeams, "%s(%s)\n", teamName, teamMembersCSV);
    fclose(myTeams);

    // 팀 폴더 생성
    _mkdir(pathteamsDir);
    char teamPath[256];
    sprintf(teamPath, "%s\\%s", pathteamsDir, teamName);
    _mkdir(teamPath);

    char teamListPath[256];
    sprintf(teamListPath, "%s\\list.txt", teamPath);
    FILE* teamFile = fopen(teamListPath, "a");
    if (teamFile) fclose(teamFile);

    printf("팀 '%s' 추가 완료!\n", teamName);
    Sleep(1000);
}

// 팀 수정
void retouchTeam()
{
    FILE* fp = fopen(pathteamsFile, "r");
    if (!fp) { printf("팀 목록 파일 열기 실패\n"); Sleep(1000); return; }

    char lines[100][128];
    int count = 0;
    while (fgets(lines[count], sizeof(lines[count]), fp)) {
        lines[count][strcspn(lines[count], "\n")] = 0;
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("수정할 팀이 없습니다.\n"); Sleep(1000); return; }

    printf("수정할 팀 목록:\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, lines[i]);

    int select;
    printf("번호 선택: "); if (scanf("%d", &select) != 1) { fflush(stdin); return; }
    if (select < 1 || select > count) { printf("잘못된 선택입니다.\n"); Sleep(1000); return; }

    char oldTeamLine[128]; strcpy(oldTeamLine, lines[select - 1]);

    char newName[64];
    printf("새 팀 이름: "); scanf("%63s", newName);

    char oldName[64];
    char* openParen = strchr(oldTeamLine, '(');
    if (openParen) {
        strncpy(oldName, oldTeamLine, openParen - oldTeamLine);
        oldName[openParen - oldTeamLine] = '\0';
    }
    else {
        strcpy(oldName, oldTeamLine);
    }

    char oldPath[256], newPath[256];
    sprintf(oldPath, "%s\\%s", pathteamsDir, oldName);
    sprintf(newPath, "%s\\%s", pathteamsDir, newName);
    if (rename(oldPath, newPath) == 0) {
        printf("팀 폴더 이름 변경 완료\n");
    }
    else {
        printf("팀 폴더 이름 변경 실패\n");
    }

    sprintf(lines[select - 1], "%s", newName);
    fp = fopen(pathteamsFile, "w");
    if (!fp) { printf("팀 목록 갱신 실패\n"); Sleep(1000); return; }
    for (int i = 0; i < count; i++) fprintf(fp, "%s\n", lines[i]);
    fclose(fp);

    printf("팀 이름 변경 완료!\n");
    Sleep(1000);
}

// 팀 삭제
void removeTeam()
{
    FILE* fp = fopen(pathteamsFile, "r");
    if (!fp) { printf("팀 목록 파일 열기 실패\n"); Sleep(1000); return; }

    char lines[100][128];
    int count = 0;
    while (fgets(lines[count], sizeof(lines[count]), fp)) {
        lines[count][strcspn(lines[count], "\n")] = 0;
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) {
        printf("삭제할 팀이 없습니다.\n");
        Sleep(1000);
        return;
    }

    printf("삭제할 팀 목록:\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, lines[i]);

    int select;
    printf("번호 선택: ");
    if (scanf("%d", &select) != 1) { fflush(stdin); return; }
    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    // 팀 이름 추출
    char teamName[64];
    char* openParen = strchr(lines[select - 1], '(');
    if (openParen) {
        strncpy(teamName, lines[select - 1], openParen - lines[select - 1]);
        teamName[openParen - lines[select - 1]] = '\0';
    }
    else {
        strcpy(teamName, lines[select - 1]);
    }

    // 현재 사용자 teams.txt에서 제거
    fp = fopen(pathteamsFile, "w");
    if (!fp) {
        printf("팀 목록 갱신 실패\n");
        Sleep(1000);
        return;
    }
    for (int i = 0; i < count; i++) {
        if (i != select - 1) fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
    printf("팀 목록에서 '%s' 제거 완료.\n", teamName);

    // 공유 팀 폴더 파일 삭제 후 폴더 삭제
    char teamPath[256];
    sprintf(teamPath, "%s\\%s", pathteamsDir, teamName);

    char teamListPath[256];
    sprintf(teamListPath, "%s\\list.txt", teamPath);

    DeleteFileA(teamListPath); // list.txt 삭제

    if (_rmdir(teamPath) == 0) {
        printf("팀 폴더 삭제 완료.\n");
    }
    else {
        printf("팀 폴더 삭제 실패 (파일이 남아있거나 권한 문제일 수 있음): %s\n", teamPath);
    }

    Sleep(1000);
}

void selectTeamForTask(int mode)
{
    FILE* fp = fopen(pathteamsFile, "r");
    if (!fp) { printf("팀 목록 파일 열기 실패\n"); Sleep(1000); return; }

    char teams[100][128];
    int count = 0;
    while (fgets(teams[count], sizeof(teams[count]), fp)) {
        teams[count][strcspn(teams[count], "\n")] = 0;
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("팀이 없습니다.\n"); Sleep(1000); return; }

    printf("------ 팀 목록 ------\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, teams[i]);

    int select;
    printf("번호 선택: ");
    if (scanf("%d", &select) != 1) { fflush(stdin); return; }
    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    // 팀 이름 추출
    char teamName[64];
    char* openParen = strchr(teams[select - 1], '(');
    if (openParen) {
        strncpy(teamName, teams[select - 1], openParen - teams[select - 1]);
        teamName[openParen - teams[select - 1]] = '\0';
    }
    else {
        strcpy(teamName, teams[select - 1]);
    }

    if (mode == 1) appendTeamTask(teamName);
    else if (mode == 2) removeTeamTask(teamName);
}

void appendTeamTask(const char* teamName)
{
    char teamListPath[256];
    sprintf(teamListPath, "%s\\%s\\list.txt", pathteamsDir, teamName);

    FILE* fp = fopen(teamListPath, "a");
    if (!fp) { printf("팀 할일 파일 열기 실패\n"); Sleep(1000); return; }

    char task[128];
    printf("추가할 팀 할일 입력: ");
    getchar(); // flush leftover newline
    fgets(task, sizeof(task), stdin);
    task[strcspn(task, "\n")] = 0;

    fprintf(fp, "%s\n", task);
    fclose(fp);

    printf("팀 '%s'에 할일 추가 완료!\n", teamName);
    Sleep(1000);
}

void removeTeamTask(const char* teamName)
{
    char teamListPath[256];
    sprintf(teamListPath, "%s\\%s\\list.txt", pathteamsDir, teamName);

    FILE* fp = fopen(teamListPath, "r");
    if (!fp) { printf("팀 할일 파일 열기 실패\n"); Sleep(1000); return; }

    char tasks[100][128];
    int count = 0;
    while (fgets(tasks[count], sizeof(tasks[count]), fp)) {
        tasks[count][strcspn(tasks[count], "\n")] = 0;
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("삭제할 팀 할일이 없습니다.\n"); Sleep(1000); return; }

    printf("------ 팀 '%s' 할일 목록 ------\n", teamName);
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, tasks[i]);

    int select;
    printf("삭제할 번호 선택: ");
    if (scanf("%d", &select) != 1) { fflush(stdin); return; }
    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    fp = fopen(teamListPath, "w");
    if (!fp) { printf("팀 할일 파일 쓰기 실패\n"); Sleep(1000); return; }
    for (int i = 0; i < count; i++) {
        if (i != select - 1) fprintf(fp, "%s\n", tasks[i]);
    }
    fclose(fp);

    printf("팀 '%s' 할일 삭제 완료!\n", teamName);
    Sleep(1000);
}

void loadTeamTasks(const char* userId)
{
    FILE* fp = fopen(pathteamsFile, "r");
    if (!fp) return;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;

        char teamName[64], members[192] = "";
        char* openParen = strchr(line, '(');
        char* closeParen = strchr(line, ')');
        if (!openParen || !closeParen) continue;

        strncpy(teamName, line, openParen - line);
        teamName[openParen - line] = '\0';

        strncpy(members, openParen + 1, closeParen - openParen - 1);
        members[closeParen - openParen - 1] = '\0';

        char tmp[256]; strcpy(tmp, members);
        char* tok = strtok(tmp, ",");
        while (tok) {
            if (strcmp(tok, userId) == 0) {
                char teamListPath[256];
                sprintf(teamListPath, "%s\\%s\\list.txt", pathteamsDir, teamName);

                FILE* teamFile = fopen(teamListPath, "r");
                if (teamFile) {
                    printf("\n[팀 '%s' 할일 목록]\n", teamName);
                    char taskLine[128];
                    while (fgets(taskLine, sizeof(taskLine), teamFile)) {
                        taskLine[strcspn(taskLine, "\n")] = 0;
                        printf("- %s\n", taskLine);
                    }
                    fclose(teamFile);
                }
                break;
            }
            tok = strtok(NULL, ",");
        }
    }
    fclose(fp);
}