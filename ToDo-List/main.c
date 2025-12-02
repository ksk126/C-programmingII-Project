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

void run()
{
    int sign = 1;
    login(sign);

    while (1)
    {
        mainUi();
    }
}

// 회원에 따른 파일 경로 설정
// settingPath() ? call after id is set (signin/signup)
void settingPath()
{
    sprintf(path, "C:\\TodoList\\%s", id);

    // Per-user files/folders
    sprintf(pathlist, "%s\\list.txt", path);
    sprintf(pathfriends, "%s\\friends.txt", path);
    sprintf(pathcategory, "%s\\category", path);
    sprintf(pathcategoryList, "%s\\category\\category.txt", path);
    sprintf(pathteamsFile, "%s\\teams.txt", path);

    // Shared team tasks dir
    sprintf(pathteamsDir, "C:\\TodoList\\teams");

    // Ensure base folders exist
    _mkdir("C:\\TodoList");
    _mkdir(path);
    _mkdir(pathcategory);
    _mkdir(pathteamsDir);

    // Ensure files exist
    FILE* f;
    f = fopen(pathlist, "a"); if (f) fclose(f);
    f = fopen(pathfriends, "a"); if (f) fclose(f);
    f = fopen(pathcategoryList, "a"); if (f) fclose(f);
    f = fopen(pathteamsFile, "a"); if (f) fclose(f);
}

void settingCategoryPath()
{
    sprintf(pathcategoryfile, "%s\\%s", pathcategory, categoryName);

    return;
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