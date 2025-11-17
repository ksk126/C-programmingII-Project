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
    sprintf(pathlist, "%s\\list.txt", path);
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
    sprintf(pathcategory, "%s\\category", path);
    _mkdir(pathcategory);
    sprintf(pathcategoryList, "%s\\category.txt", path);
    FILE* userFile = fopen(pathcategoryList, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패");
        exit(0);
    }
    fclose(userFile);
    return;
}

void appendFriendsFile()
{
    sprintf(pathfriends, "%s\\friends.txt", path);
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
    sprintf(pathteams, "%s\\teams.txt", path);
    FILE* userFile = fopen(pathteams, "w");
    if (!userFile)
    {
        printf("개인 파일 생성 실패\n");
        exit(0);
    }
    fclose(userFile);
    return;
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
    return;
}