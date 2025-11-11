#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAXLOGIN 20
#define LINE 128
#define MAX 200

char id[MAXLOGIN];
char pw[MAXLOGIN];

typedef struct todo {
    int month;
    int day;
    char tasks[MAX];
    char memo[MAX];
} Todo;

void run();
void openfile();
void login(int sign, char* path);
void ui(Todo list, const char* path);
void uiConnect(int select, const char* path, Todo list);
void appendTodo(const char* path, Todo list);
int inputLogin(const char* message);
int signup(char* path);
int signin();
int sameID();
void appendMember(char* path);
void settingPath(char* path);
void print0check(char* path);

int main()
{
    openfile();
    run();
    return 0;
}

void openfile()
{
    _mkdir("c:\\TodoList");

    FILE* fp = fopen("c:\\TodoList\\member.txt", "a");
    if (fp == NULL)
    {
        printf("파일 열기 실패\n");
        exit(0);
    }
    fclose(fp);
}

void run() {
    char path[LINE];
    Todo list = { 0 };
	FILE* fp = NULL;
	int sign = 1;

    login(sign, path);

    while (1)
    {
        ui(list, path);
    }
}

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

void settingPath(char* path)
{
    sprintf(path, "c:\\TodoList\\%s.txt", id);
}

void login(int sign, char* path)
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (fp == NULL)
    {
        printf("회원 목록을 확인할 수 없습니다.\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    if (size == 0) sign = 0;

    while (1)
    {
        system("cls");

        //파일이 비어있을 경우 회원가입 먼저
        if (sign == 0)
        {
            if (signup(path))
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

        //로그인
        if (signin())
        {
            printf("로그인 성공!\n");
            Sleep(1000);
            settingPath(path);
            break;
        }
        else
        {
            printf("로그인 실패. 회원가입 하시겠습니까? (y/n)\n");
            char select = getch();
            if (select == 'y')
            {
                sign = 0;
                continue;
            }
            else
            {
                continue;
            }
        }
    }
    return;
}

//회원 목록 추가
void appendMember(char* path)
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "a");
    if (fp == NULL)
    {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "ID:%s,PW:%s\n", id, pw);
    fclose(fp);

    fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(fp);
}

//회원가입 함수
int signup(char* path)
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
    Sleep(1000);
    settingPath(path);
    appendMember(path);
    return 1;
}

//로그인 함수
int signin() {
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (fp == NULL)
    {
        printf("회원 정보를 확인할 수 없습니다.\n");
        return 0;
    }

    char line[LINE];
    char fileId[MAXLOGIN], filePw[MAXLOGIN];
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

int sameID() {
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (fp == NULL) return 1;

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

void print0check(const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("파일 불러오기 실패\n");
        return;
    }

    Todo todos[200] = { 0 };
    int check, count = 0;
    char line[LINE];

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%d | %d/%d | %[^|]| %[^\n]",
            &check, &todos[count].month, &todos[count].day,
            todos[count].tasks, todos[count].memo) >= 4)
        {
            if (check == 0)
            {
                count++;
            }
        }
    }
    fclose(fp);

    //날짜순 정렬
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (todos[i].month < todos[j].month ||
                (todos[i].month == todos[j].month && todos[i].day < todos[j].day))
            {
                Todo temp = todos[i];
                todos[i] = todos[j];
                todos[j] = temp;
            }
        }
    }

    //출력
    if (count == 0)
    {
        printf("(미완료 일정 없음)\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("%02d/%02d | %s | %s\n",
                todos[i].month, todos[i].day, todos[i].tasks, todos[i].memo);
        }
    }
}

void ui(Todo list, const char* path)
{
    system("cls");
    int select = 0;
    printf("-----미완료된 목록-----\n");
    print0check(path);
    printf("\n");
    printf("----------메뉴---------\n");
    printf("0. 목록\n");
    printf("1. 일정 추가\n");
    printf("2. 수정 및 삭제\n");
    printf("3. 로그아웃\n");
    printf("----------------------=\n");
    printf("입력: ");
    scanf("%d", &select);

    uiConnect(select, path, list);

    return;
}

void uiConnect(int select, const char* path, Todo list)
{
    switch (select)
    {
    case 0:
        printf("목록 표시 기능 준비중\n");
        break;
    case 1:
        appendTodo(path, list);
        break;
    case 2:
        printf("수정/삭제 기능 준비중\n");
        break;
    case 3:
        login(1, path);
        break;
    default:
        printf("잘못 입력하였습니다.");
        Sleep(1000);
        return;
    }

    return;
}

void appendTodo(const char* path, Todo list)
{
    char todo[128];
    printf("날짜|할일|비고: ");
    getchar();
    fgets(todo, sizeof(todo), stdin);
    todo[strcspn(todo, "\n")] = 0;

    char* ptr = strtok(todo, "/");
    if (ptr) list.month = atoi(ptr);
    ptr = strtok(NULL, "|");
    if (ptr) list.day = atoi(ptr);
    ptr = strtok(NULL, "|");
    if (ptr) strcpy(list.tasks, ptr);
    ptr = strtok(NULL, "|");
    if (ptr) strcpy(list.memo, ptr);

    FILE* fp = fopen(path, "a");
    if (fp == NULL)
    {
        printf("파일 열기 실패\n");
        return;
    }

    fprintf(fp, "%d | %02d/%02d | %s | %s\n",
        0, list.month, list.day, list.tasks, list.memo);
    fclose(fp);

    printf("일정 추가 완료!\n");
    Sleep(1000);

    while (1)
    {
        printf("이어서 등록하겠습니까? (y/n)\n");
        char select = getch();
        if (select == 'y')
        {
            uiConnect(1, path, list);
        }
        else if (select == 'n')
        {
            break;
        }

        printf("잘못 입력하였습니다.");
        Sleep(1000);
        system("cls");
    }


    return;
}
