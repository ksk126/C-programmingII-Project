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
    appendListFile();
    appendCategoryFile();
    appendFriendsFile();
    appendTeamsFile();
}

void appendListFile()
{
    FILE* userFile = fopen(pathlist, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
}

void appendCategoryFile()
{
    _mkdir(pathcategory);
    FILE* userFile = fopen(pathcategoryList, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
    return;
}

void appendFriendsFile()
{
    FILE* userFile = fopen(pathfriends, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
    return;
}

void appendTeamsFile()
{
    FILE* userFile = fopen(pathteamsFile, "a");
    if (!userFile) { printf("개인 팀 파일 생성 실패\n"); Sleep(1000); return; }
    fclose(userFile);

    _mkdir(pathteamsDir);
}


void appendCategory()
{
    FILE* fp = fopen(pathcategoryList, "a");
    if (!fp)
    {
        printf("파일 정보 추가 실패\n");
        exit(0);
    }

    fprintf(fp, "%s\n", categoryName);
    fclose(fp);

    appendCategoryListFile();

    return;
}

void appendCategoryListFile()
{
    settingCategoryPath();

    _mkdir(pathcategoryfile);
}