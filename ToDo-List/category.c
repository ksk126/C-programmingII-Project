#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"
#include "utils.h"

// -----------------------------
// 카테고리 메뉴
// -----------------------------
void category() {
    clearScreen();
    int select = 0;
    int width = 30;
    printCategorySummary();

    // 윗줄
    TitleOnBar(width);

    // 메뉴 항목들
    printMiddleLine("카테고리 관리 메뉴", width);
    printMiddleLine("[1] 카테고리 추가", width);
    printMiddleLine("[2] 수정", width);
    printMiddleLine("[3] 카테고리 삭제", width);
    printMiddleLine("[4] 카테고리 할일 추가", width);
    printMiddleLine("[5] 카테고리 할일 수정", width);
    printMiddleLine("[6] 카테고리 할일 완료", width);
    printMiddleLine("[0] 뒤로가기", width);

    // 아랫줄
    TitleUnderBar(width);

    printf("입력: ");
    scanf("%d", &select);

    categoryConnect(select);
}

// -----------------------------
// 카테고리 추가
// -----------------------------
void inputCategoryName() {
    printf("추가할 카테고리 이름: ");
    scanf("%s", categoryName);

    appendCategory();
}

// -----------------------------
// 카테고리 수정
// -----------------------------
void retouchCategory() {
    char categories[100][64];
    int count = loadListFromFile(pathcategoryList, categories, 100);

    if (count == 0) {
        printf("수정할 카테고리가 없습니다.\n");
        Sleep(1000);
        return;
    }

    printList(categories, count, "수정할 카테고리 목록");
    int select = selectFromList(count, "번호 선택: ");
    if (select == -1) return;

    char newName[64];
    printf("새 카테고리 이름: ");
    scanf("%s", newName);

    char oldPath[256], newPath[256];
    sprintf(oldPath, "%s\\%s", pathcategory, categories[select - 1]);
    sprintf(newPath, "%s\\%s", pathcategory, newName);

    if (rename(oldPath, newPath) == 0) {
        printf("폴더 이름 변경 완료\n");
    }
    else {
        printf("폴더 이름 변경 실패 (파일이 열려있거나 권한 문제)\n");
    }

    strcpy(categories[select - 1], newName);
    FILE* fp = fopen(pathcategoryList, "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", categories[i]);
    }
    fclose(fp);

    Sleep(1000);
}

// -----------------------------
// 카테고리 삭제
// -----------------------------
void removeCategory() {
    char categories[100][64];
    int count = loadListFromFile(pathcategoryList, categories, 100);

    if (count == 0) {
        printf("삭제할 카테고리가 없습니다.\n");
        Sleep(1000);
        return;
    }

    printList(categories, count, "삭제할 카테고리 목록");
    int select = selectFromList(count, "번호 선택: ");
    if (select == -1) return;

    char folderPath[256];
    sprintf(folderPath, "%s\\%s", pathcategory, categories[select - 1]);

    if (_rmdir(folderPath) == 0) {
        printf("폴더 삭제 완료\n");
    }
    else {
        printf("폴더 삭제 실패 (비어있지 않거나 권한 문제)\n");
    }

    FILE* fp = fopen(pathcategoryList, "w");
    for (int i = 0; i < count; i++) {
        if (i != select - 1) fprintf(fp, "%s\n", categories[i]);
    }
    fclose(fp);

    Sleep(1000);
}

// -----------------------------
// 카테고리 할일 추가
// -----------------------------
void appendTodoInCategory() {
    clearScreen();

    char categories[100][64];
    int count = loadListFromFile(pathcategoryList, categories, 100);

    if (count == 0) {
        printf("등록된 카테고리가 없습니다.\n");
        Sleep(1000);
        return;
    }

    printList(categories, count, "카테고리 목록");
    int select;
    printf("카테고리 번호 선택 (뒤로 가려면 0): ");
    scanf("%d", &select);
    if (select == 0) return;
    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return;
    }

    strcpy(categoryName, categories[select - 1]);
    settingCategoryPath();

    char input[128];
    printf("날짜|할일|비고 형식으로 입력, 뒤로 가려면 0 (예: 12/25|보고서 작성|초안 완료)\n");
    getchar();
    fgets(input, sizeof(input), stdin);
    trimNewline(input);

    if (!strcmp(input, "0")) return;

    char* ptr = strtok(input, "/");
    if (ptr) todo.month = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) todo.day = atoi(ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(todo.tasks, ptr);

    ptr = strtok(NULL, "|");
    if (ptr) strcpy(todo.memo, ptr);

    todo.check = 0;

    char categoryListFile[256];
    sprintf(categoryListFile, "%s\\list.txt", pathcategoryfile);

    FILE* fp = fopen(categoryListFile, "a");
    if (!fp) {
        printf("파일 열기 실패\n");
        return;
    }

    fprintf(fp, "%d | %02d/%02d | %s | %s\n",
        todo.check, todo.month, todo.day, todo.tasks, todo.memo);
    fclose(fp);

    printf("[%s] 카테고리에 일정 추가 완료!\n", categoryName);
    Sleep(800);
}

// -----------------------------
// 카테고리 할일 출력 (날짜별)
// -----------------------------
int printTodoNumInCategory(int month, int day, int fcount, int count, int* found) {
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
// 카테고리 할일 수정
// -----------------------------
void retouchTodoInCategory() {
    while (1) {
        clearScreen();

        int count = loadTodosToCategory();
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

        fcount = printTodoNumInCategory(month, day, fcount, count, found);

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

            saveTodosToCategory(count);

            printf("카테고리 일정 수정 완료!\n");
            Sleep(800);
            break;
        }
    }
}
// -----------------------------
// 카테고리 일정 저장
// -----------------------------
void saveTodosToCategory(int count) {
    char categoryListFile[256];
    sprintf(categoryListFile, "%s\\list.txt", pathcategoryfile);

    FILE* fp = fopen(categoryListFile, "w");
    if (!fp) {
        printf("카테고리 할일 파일 저장 실패\n");
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
// 카테고리 일정 로드
// -----------------------------
int loadTodosToCategory() {
    char categoryListFile[256];
    sprintf(categoryListFile, "%s\\list.txt", pathcategoryfile);

    FILE* fp = fopen(categoryListFile, "r");
    if (!fp) return 0;

    int count = 0;
    while (fscanf(fp, "%d | %d/%d | %[^|]| %[^\n]",
        &todos[count].check,
        &todos[count].month,
        &todos[count].day,
        todos[count].tasks,
        todos[count].memo) != EOF) {
        count++;
        if (count >= 100) break; // 최대 100개까지만 로드
    }
    fclose(fp);
    return count;
}

// -----------------------------
// 카테고리별 미완료 일정 출력
// -----------------------------
void printCategorySummary()
{
    char categories[100][64];
    int count = loadListFromFile(pathcategoryList, categories, 100);

    printf("------ 카테고리별 미완료 일정 ------\n");
    if (count == 0) {
        printf("(등록된 카테고리 없음)\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        strcpy(categoryName, categories[i]);
        settingCategoryPath();
        int todoCount = loadTodosToCategory();

        int printed = 0;
        for (int j = 0; j < todoCount; j++) {
            if (todos[j].check == 0) {
                if (!printed) {
                    printf("[%s]\n", categories[i]); // 카테고리 이름
                }
                printf("%02d/%02d | %s | %s\n",
                    todos[j].month,
                    todos[j].day,
                    todos[j].tasks,
                    todos[j].memo);
                printed = 1;
            }
        }
        if (!printed) {
            printf("[%s] (미완료 일정 없음)\n", categories[i]);
        }
    }
    printf("----------------------------------\n");
}

// 카테고리 일정 완료 처리
void completeTodoInCategory() {
    clearScreen();

    int count = loadTodosToCategory();
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
    int fcount = printTodoNumInCategory(month, day, 0, count, found);

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
    saveTodosToCategory(count);

    printf("카테고리 일정 완료 처리 완료!\n");
    Sleep(800);
}