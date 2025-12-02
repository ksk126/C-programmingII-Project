#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"
#include "utils.h"   // 공통 함수 사용

// -----------------------------
// 일정 불러오기
// -----------------------------
int loadTodos() {
    FILE* fp = fopen(pathlist, "r");
    if (!fp) return 0;

    int count = 0;
    while (fscanf(fp, "%d | %d/%d | %[^|]| %[^\n]",
        &todos[count].check,
        &todos[count].month,
        &todos[count].day,
        todos[count].tasks,
        todos[count].memo) != EOF) {
        count++;
        if (count >= MAX_TODO_COUNT) break;
    }
    fclose(fp);
    return count;
}

// -----------------------------
// 일정 저장
// -----------------------------
void saveTodos(int count) {
    FILE* fp = fopen(pathlist, "w");
    if (!fp) {
        printf("일정 파일 저장 실패\n");
        Sleep(1000);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d | %02d/%02d | %s | %s\n",
            todos[i].check,
            todos[i].month,
            todos[i].day,
            todos[i].tasks,
            todos[i].memo);
    }
    fclose(fp);
}

// -----------------------------
// 일정 추가
// -----------------------------
void appendTodo() {
    clearScreen();
    char input[128];
    printf("날짜|할일|비고 형식으로 입력 (예: 12/25|보고서 작성|초안 완료)\n");
    getchar();
    fgets(input, sizeof(input), stdin);
    trimNewline(input);

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
    if (!fp) {
        printf("파일 열기 실패\n");
        return;
    }

    fprintf(fp, "%d | %02d/%02d | %s | %s\n",
        todo.check, todo.month, todo.day, todo.tasks, todo.memo);
    fclose(fp);

    printf("일정 추가 완료!\n");
    Sleep(800);
}

// -----------------------------
// 일정 정렬 (날짜순)
// -----------------------------
void qsortTodos(int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (todos[i].month > todos[j].month ||
                (todos[i].month == todos[j].month && todos[i].day > todos[j].day)) {
                Todo temp = todos[i];
                todos[i] = todos[j];
                todos[j] = temp;
            }
        }
    }
}

// -----------------------------
// 일정 번호 출력 (날짜별)
// -----------------------------
int printTodoNum(int month, int day, int fcount, int count, int* found) {
    for (int i = 0; i < count; i++) {
        if (todos[i].month == month && todos[i].day == day) {
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

// -----------------------------
// 일정 수정
// -----------------------------
void retouchTodo() {
    while (1) {
        clearScreen();

        int count = loadTodos();
        int month = 0, day = 0, fcount = 0;
        int found[100];

        if (count == 0) {
            printf("수정할 데이터가 없습니다.\n");
            Sleep(1000);
            return;
        }

        printf("날짜 입력, 뒤로 가려면 0 (예: mm/dd) ");
        scanf("%d/%d", &month, &day);

        if (month == 0) return;

        fcount = printTodoNum(month, day, fcount, count, found);

        if (fcount == 0) {
            printf("해당 날짜에 데이터가 없습니다.\n");
            Sleep(1000);
            continue;
        }

        int select;
        printf("수정할 번호 선택: ");
        scanf("%d", &select);

        if (select < 1 || select > fcount) {
            printf("잘못된 선택입니다.\n");
            Sleep(1000);
            continue;
        }
        else {
            char input[128];
            int idx = found[select - 1];
            printf("날짜|할일|비고 형식으로 새 입력 (예: 12/25|보고서 작성|초안 완료)\n");
            getchar();
            fgets(input, sizeof(input), stdin);
            trimNewline(input);

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
}

// 일정 완료 처리
void completeTodo() {
    clearScreen();

    int count = loadTodos();
    if (count == 0) {
        printf("완료할 데이터가 없습니다.\n");
        Sleep(1000);
        return;
    }

    int month, day;
    printf("완료할 일정 날짜 입력 (예: mm/dd, 뒤로 가려면 0): ");
    scanf("%d/%d", &month, &day);
    if (month == 0) return;

    int found[100];
    int fcount = printTodoNum(month, day, 0, count, found);

    if (fcount == 0) {
        printf("해당 날짜에 일정이 없습니다.\n");
        Sleep(1000);
        return;
    }

    int select;
    printf("완료할 번호 선택: ");
    scanf("%d", &select);

    if (select < 1 || select > fcount) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    int idx = found[select - 1];
    todos[idx].check = 1;

    saveTodos(count);

    printf("일정 완료 처리 완료!\n");
    Sleep(800);
}