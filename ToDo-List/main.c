#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>

#define MAXLOGIN 20
#define LINE 128
#define MAX 200

char id[MAXLOGIN];
char pw[MAXLOGIN];

typedef struct todo
{
    int check;
    int month;
    int day;
    char tasks[MAX];
    char memo[MAX];
} Todo;

// 함수 선언
void run();
void openfile();

void ui(Todo list, const char* path);
void uiConnect(int select, const char* path, Todo list, Todo* todos);

void print0check(const char* path, Todo* todos);

void login(int sign, char* path);
int inputLogin(const char* message);
int signup(char* path);
int signin();
int sameID();
void appendMember(char* path);

void settingPath(char* path);

int loadTodos(const char* path, Todo* todos);
void saveTodos(const char* path, Todo* todos, int count);
void appendTodo(const char* path, Todo list, Todo* todos);
void qsortTodos(int count, Todo* todos);

void retouchTodo(const char* path, Todo list, Todo* todos);
int printTodoNum(int month, int day, int fcount, int count, int* found, Todo* todos);

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

void run()
{
    char path[LINE];
    Todo list = { 0 };
    int sign = 1;

    login(sign, path);

    while (1)
    {
        ui(list, path);
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
void settingPath(char* path)
{
    sprintf(path, "c:\\TodoList\\%s.txt", id);
}

// 로그인 총괄 함수
void login(int sign, char* path)
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

        if (signin())
        {
            printf("로그인 성공!\n");
            Sleep(800);
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
            }
        }
    }
}

// 회원목록에 id pw 추가
void appendMember(char* path)
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "a");
    if (!fp)
    {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "ID:%s,PW:%s\n", id, pw);
    fclose(fp);

    fp = fopen(path, "w");
    if (!fp)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(fp);
}

// 회원가입
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
    Sleep(800);
    settingPath(path);
    appendMember(path);
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
int loadTodos(const char* path, Todo* todos)
{
    FILE* fp = fopen(path, "r");
    if (!fp)
    {
        // 파일이 없으면 0개로 간주
        return 0;
    }

    int check = 0;
    int count = 0;
    char line[LINE];

    while (fgets(line, sizeof(line), fp))
    {
        int r = sscanf(line, "%d | %d/%d | %[^|] | %[^\n]",
            &check,
            &todos[count].month,
            &todos[count].day,
            todos[count].tasks,
            todos[count].memo);
        if (r == 5)
        {
            todos[count].check = check ? 1 : 0;
            count++;
            if (count >= MAX) break;
        }
    }

    fclose(fp);
    return count;
}

// 구조체 배열 오름차순 정리
void qsortTodos(int count, Todo* todos)
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
void print0check(const char* path, Todo* todos)
{
    int count = loadTodos(path, todos);
    qsortTodos(count, todos);

    int printed = 0;
    for (int i = 0; i < count; i++)
    {
        if (todos[i].check == 0)
        {
            if (!printed)
            {
                printf("-----미완료된 목록-----\n");
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
void ui(Todo list, const char* path)
{
    Todo todos[200] = { 0 };
    system("cls");

    int select = 0;
    print0check(path, todos);
    printf("\n");

    printf("----------메뉴---------\n");
    printf("0. 목록 (준비중)\n");
    printf("1. 일정 추가\n");
    printf("2. 수정 및 삭제\n");
    printf("3. 로그아웃\n");
    printf("4. 프로그램 종료\n");
    printf("-----------------------\n");
    printf("입력: ");
    scanf("%d", &select);

    uiConnect(select, path, list, todos);
}

// ui입력 처리
void uiConnect(int select, const char* path, Todo list, Todo* todos)
{
    switch (select)
    {
    case 0:
        printf("목록 표시 기능 준비중\n");
        Sleep(1000);
        break;

    case 1:
        appendTodo(path, list, todos);
        break;

    case 2:
        retouchTodo(path, list, todos);
        break;

    case 3:
        login(1, (char*)path);
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
void appendTodo(const char* path, Todo list, Todo* todos)
{
    system("cls");

    char todo[128];

    printf("날짜|할일|비고 형식으로 입력, 뒤로 가려면 0 (예: 12/25|크리스마스|선물 준비)\n");
    getchar(); // 입력 버퍼 비우기
    fgets(todo, sizeof(todo), stdin);
    todo[strcspn(todo, "\n")] = 0;

    if (!strcmp(todo, "0"))
    {
        return;
    }

    char* ptr = strtok(todo, "/");
    if (ptr) list.month = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) list.day = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(list.tasks, ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(list.memo, ptr);

    list.check = 0;

    FILE* fp = fopen(path, "a");
    if (!fp)
    {
        printf("파일 열기 실패\n");
        return;
    }

    fprintf(fp, "%d | %02d/%02d | %s | %s\n",
        list.check, list.month, list.day, list.tasks, list.memo);
    fclose(fp);

    printf("일정 추가 완료!\n");
    Sleep(800);
}

int printTodoNum(int month, int day, int fcount, int count, int* found, Todo* todos)
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

void saveTodos(const char* path, Todo* todos, int count)
{
    FILE* fp = fopen(path, "w");
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

void retouchTodo(const char* path, Todo list, Todo* todos)
{
    while (1)
    {
        system("cls");

        int count = loadTodos(path, todos);
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

        fcount = printTodoNum(month, day, fcount, count, found, todos);

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
            char todo[128];
            int idx = found[select - 1];
            printf("날짜|할일|비고 형식으로 새 입력 (예: 12/25|크리스마스|선물 준비)\n");
            getchar(); // 입력 버퍼 비우기
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

            todos[idx].month = list.month;
            todos[idx].day = list.day;
            strcpy(todos[idx].tasks, list.tasks);
            strcpy(todos[idx].memo, list.memo);

            saveTodos(path, todos, count);

            printf("일정 수정 완료!\n");
            Sleep(800);
            break;
        }
    }

    return;
}