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

int main()
{
    openfile();
    run();
    return 0;
}

// 초기 파일 구성
void openfile()
{
    _mkdir("c:\\TodoList");

    FILE* fp = fopen("c:\\TodoList\\member.txt", "a");
    if (!fp)
    {
        printf("파일 열기 실패\n");
        exit(0);
    }
    fclose(fp);
}

void makefile()
{
    _mkdir(path);
    return;
}

void run()
{
    int sign = 1;
    login(sign);

    while (1)
    {
        mainUi();
    }
}

// 회원가입, 로그인 입력
int inputLogin(const char* message)
{
    printf("%s", message);
    printf("ID: ");
    scanf("%s", id);

    if (!strcmp(id, "0"))
    {
        exit(0);
    }
    else if (!strcmp(id, "1"))
    {
        return 1;
    }

    printf("PW: ");
    scanf("%s", pw);
    return 0;
}

// 회원에 따른 파일 경로 설정
void settingPath()
{
    sprintf(path, "c:\\TodoList\\%s", id);
}

// 로그인 총괄 함수
void login(int sign)
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        printf("회원 목록을 확인할 수 없습니다.\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    if (size == 0)
    {
        sign = 0;
    }

    while (1)
    {
        system("cls");

        if (sign == 0)
        {
            if (signup())
            {
                sign = 1;
                continue;
            }
            else
            {
                printf("회원가입 실패\n");
                Sleep(1000);
                continue;
            }
        }

        if (signin())
        {
            printf("로그인 성공!\n");
            Sleep(800);
            settingPath();
            break;
        }
        else
        {
            printf("로그인 실패. 회원가입 하시겠습니까? (y/n)\n");
            char select = getch();
            if (select == 'y')
            {
                sign = 0;
            }
        }
    }
}

// 회원가입
int signup()
{
    int select = inputLogin("회원가입을 종료하려면 0, 로그인 하려면 1.\n");

    if (select == 1)
    {
        return 1;
    }

    if (!sameID())
    {
        printf("이미 존재하는 아이디입니다.\n");
        Sleep(1000);
        return 0;
    }

    printf("회원가입 성공!\n");
    Sleep(800);
    settingPath();
    appendMember();
    return 1;
}

// 로그인
int signin()
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        printf("회원 정보를 확인할 수 없습니다.\n");
        return 0;
    }

    char line[LINE];
    char fileId[MAXLOGIN];
    char filePw[MAXLOGIN];

    inputLogin("로그인 (0 입력시 종료)\n");

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "ID:%[^,],PW:%s", fileId, filePw) == 2)
        {
            if (!strcmp(id, fileId) && !strcmp(pw, filePw))
            {
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}

// 같은 아이디인지 확인
int sameID()
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        return 1;
    }

    char line[LINE];
    char fileId[MAXLOGIN];

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "ID:%[^,]", fileId) == 1)
        {
            if (!strcmp(id, fileId))
            {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

// 파일 목록 구조체 배열로 불러오기
int loadTodos()
{
    FILE* fp = fopen(pathlist, "r");
    if (!fp)
    {
        return 0;
    }

    int count = 0;
    char line[LINE];

    while (fgets(line, sizeof(line), fp))
    {
        int r = sscanf(line, "%d | %d/%d | %[^|] | %[^\n]",
            &todos[count].check,
            &todos[count].month,
            &todos[count].day,
            todos[count].tasks,
            todos[count].memo);
        if (r == 5)
        {
            count++;
            if (count >= MAX) break;
        }
    }

    fclose(fp);
    return count;
}

// 구조체 배열 오름차순 정리
void qsortTodos(int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (todos[i].month > todos[j].month ||
                (todos[i].month == todos[j].month && todos[i].day > todos[j].day))
            {
                Todo tmp = todos[i];
                todos[i] = todos[j];
                todos[j] = tmp;
            }
        }
    }
}

// 미완료 목록만 출력
void print0check()
{
    int count = loadTodos();
    qsortTodos(count);

    int printed = 0;
    for (int i = 0; i < count; i++)
    {
        if (todos[i].check == 0)
        {
            if (!printed)
            {
                printf("------미완료된 목록------\n");
            }
            printf("%02d/%02d | %s| %s\n",
                todos[i].month, todos[i].day,
                todos[i].tasks, todos[i].memo);
            printed = 1;
        }
    }

    if (!printed)
    {
        printf("(미완료 일정 없음)\n");
    }
}

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

// 할일 추가
void appendTodo()
{
    system("cls");

    char input[128];

    printf("날짜|할일|비고 형식으로 입력, 뒤로 가려면 0 (예: 12/25|크리스마스|선물 준비)\n");
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (!strcmp(input, "0"))
    {
        return;
    }

    char* ptr = strtok(input, "/");
    if (ptr) todo.month = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) todo.day = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(todo.tasks, ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(todo.memo, ptr);

    todo.check = 0;

    FILE* fp = fopen(pathlist, "a");
    if (!fp)
    {
        printf("파일 열기 실패\n");
        return;
    }

    fprintf(fp, "%d | %02d/%02d | %s | %s\n",
        todo.check, todo.month, todo.day, todo.tasks, todo.memo);
    fclose(fp);

    printf("일정 추가 완료!\n");
    Sleep(800);
}

int printTodoNum(int month, int day, int fcount, int count, int* found)
{
    for (int i = 0; i < count; i++)
    {
        if (todos[i].month == month && todos[i].day == day)
        {
            printf("[%d] %02d/%02d | %s | %s\n",
                fcount + 1,
                todos[i].month, todos[i].day,
                todos[i].tasks, todos[i].memo);
            found[fcount++] = i;
            if (fcount >= 100) break;
        }
    }

    return fcount;
}

void saveTodos(int count)
{
    FILE* fp = fopen(pathlist, "w");
    if (fp == NULL)
    {
        printf("파일 열기 실패: %s\n", path);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d | %02d/%02d | %s | %s\n",
            todos[i].check, todos[i].month, todos[i].day,
            todos[i].tasks, todos[i].memo);
    }

    fclose(fp);
}

void retouchTodo()
{
    while (1)
    {
        system("cls");

        int count = loadTodos();
        int month = 0, day = 0, fcount = 0;
        int found[100];

        if (count == 0)
        {
            printf("수정할 데이터가 없습니다.\n");
            Sleep(1000);
            return;
        }

        printf("날짜 입력, 뒤로 가려면 0 (예: mm/dd) ");
        scanf("%d/%d", &month, &day);

        if (month == 0)
        {
            return;
        }

        fcount = printTodoNum(month, day, fcount, count, found);

        if (fcount == 0)
        {
            printf("해당 날짜에 데이터가 없습니다.\n");
            Sleep(1000);
            continue;
        }

        int select;
        printf("수정할 번호 선택: ");
        scanf("%d", &select);

        if (select < 1 || select > fcount)
        {
            printf("잘못된 선택입니다.\n");
            Sleep(1000);
            continue;
        }
        else
        {
            char input[128];
            int idx = found[select - 1];
            printf("날짜|할일|비고 형식으로 새 입력 (예: 12/25|크리스마스|선물 준비)\n");
            getchar();
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char* ptr = strtok(input, "/");
            if (ptr) todo.month = atoi(ptr);

            ptr = strtok(NULL, "|");
            if (ptr) todo.day = atoi(ptr);

            ptr = strtok(NULL, "|");
            if (ptr) strcpy(todo.tasks, ptr);

            ptr = strtok(NULL, "|");
            if (ptr) strcpy(todo.memo, ptr);

            todos[idx].month = todo.month;
            todos[idx].day = todo.day;
            strcpy(todos[idx].tasks, todo.tasks);
            strcpy(todos[idx].memo, todo.memo);

            saveTodos(count);

            printf("일정 수정 완료!\n");
            Sleep(800);
            break;
        }
    }

    return;
}

// 회원목록에 id pw 추가, 개인 파일 생성
void appendMember()
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "a");
    if (!fp)
    {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "ID:%s,PW:%s\n", id, pw);
    fclose(fp);

    makefile();
    appendList();
    appendFriends();
    appendTeams();
}

void appendList()
{
    sprintf(pathlist, "%s\\list.txt", path);
    FILE* userFile = fopen(pathlist, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
}

void appendFriends()
{
    sprintf(pathfriends, "%s\\friends.txt", path);
    FILE* userFile = fopen(pathfriends, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
    return;
}

void appendTeams()
{
    sprintf(pathteams, "%s\\teams.txt", path);
    FILE* userFile = fopen(pathteams, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
    return;
}

void category()
{
    system("cls");
    int select = 0;
    printf("----------카테고리 관리 메뉴---------\n");
    printf("[1] 카테고리 추가\n");
    printf("[2] 카테고리 수정\n");
    printf("[3] 카테고리 삭제\n");
    printf("-----------------------\n");
    printf("[0] 뒤로 가기\n");
    printf("입력: ");
    scanf("%d", &select);

    categoryConnect(select);
    return;
}

void categoryConnect(int select)
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

void teams()
{
    system("cls");
    int select = 0;
    printf("----------팀 관리 메뉴---------\n");
    printf("[1] 팀 추가\n");
    printf("[2] 팀 수정\n");
    printf("[3] 팀 삭제\n");
    printf("-----------------------\n");
    printf("[0] 로그아웃\n");
    printf("입력: ");
    scanf("%d", &select);
    return;
}

void teamsConnect(int select)
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