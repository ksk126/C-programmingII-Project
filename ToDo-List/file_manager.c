#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"

// -----------------------------
// 기본 TodoList 디렉터리 및 회원 파일 생성
// -----------------------------
void openfile() {
    _mkdir("C:\\TodoList");

    FILE* fp = fopen("C:\\TodoList\\member.txt", "a");
    if (!fp) {
        printf("파일 열기 실패\n");
        exit(0);
    }
    fclose(fp);
}

// -----------------------------
// 사용자 디렉터리 생성
// -----------------------------
void makefile() {
    _mkdir(path);
}

// -----------------------------
// 회원 정보 추가 및 개인 파일 생성
// -----------------------------
void appendMember() {
    FILE* fp = fopen("C:\\TodoList\\member.txt", "a");
    if (!fp) {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "ID:%s,PW:%s\n", id, pw);
    fclose(fp);

    makefile();
    appendListFile();
    appendCategoryFile();
    appendFriendsFile();
    appendTeamsFile();
}

// -----------------------------
// 개인 일정 파일 생성
// -----------------------------
void appendListFile() {
    FILE* userFile = fopen(pathlist, "w");
    if (!userFile) {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
}

// -----------------------------
// 카테고리 파일 생성
// -----------------------------
void appendCategoryFile() {
    _mkdir(pathcategory);
    FILE* userFile = fopen(pathcategoryList, "w");
    if (!userFile) {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
}

// -----------------------------
// 친구 목록 파일 생성
// -----------------------------
void appendFriendsFile() {
    FILE* userFile = fopen(pathfriends, "w");
    if (!userFile) {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
}

// -----------------------------
// 팀 목록 파일 생성
// -----------------------------
void appendTeamsFile() {
    FILE* userFile = fopen(pathteamsFile, "a");
    if (!userFile) {
        printf("개인 팀 파일 생성 실패\n");
        Sleep(1000);
        return;
    }
    fclose(userFile);

    _mkdir(pathteamsDir);
}

// -----------------------------
// 카테고리 추가
// -----------------------------
void appendCategory() {
    FILE* fp = fopen(pathcategoryList, "a");
    if (!fp) {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "%s\n", categoryName);
    fclose(fp);

    appendCategoryListFile();
}

// -----------------------------
// 카테고리 디렉터리 생성
// -----------------------------
void appendCategoryListFile() {
    settingCategoryPath();
    _mkdir(pathcategoryfile);
}