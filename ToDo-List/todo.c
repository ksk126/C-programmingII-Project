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