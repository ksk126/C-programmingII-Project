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
void settingPath()
{
    sprintf(path, "c:\\TodoList\\%s", id);
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