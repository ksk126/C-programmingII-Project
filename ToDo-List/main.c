#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"
#include "utils.h"   // clearScreen 등 공통 함수 사용

// -----------------------------
// 프로그램 시작점
// -----------------------------
int main() {
    openfile();
    run();
    return 
        ;
}

// -----------------------------
// 실행 루프
// -----------------------------
void run() {
    int sign = 1;
    login(sign);

    while (1) {
        mainUi();
    }
}

// -----------------------------
// 회원에 따른 파일 경로 설정
// -----------------------------
void settingPath() {
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

    f = fopen(pathlist, "a");
    if (f) {
        fclose(f);
    }

    f = fopen(pathfriends, "a");
    if (f) {
        fclose(f);
    }

    f = fopen(pathcategoryList, "a");
    if (f) {
        fclose(f);
    }

    f = fopen(pathteamsFile, "a");
    if (f) {
        fclose(f);
    }
}

// -----------------------------
// 카테고리 경로 설정
// -----------------------------
void settingCategoryPath() {
    sprintf(pathcategoryfile, "%s\\%s", pathcategory, categoryName);
}