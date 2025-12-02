#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include "struct.h"
#include "function.h"
#include "global_variable.h"

void category()
{
    system("cls");
    int select = 0;
    printf("----------카테고리 관리 메뉴---------\n");
    printf("[1] 카테고리 추가\n");
    printf("[2] 카테고리 수정\n");
    printf("[3] 카테고리 삭제\n");
    printf("-----------------------\n");
    printf("[0] 뒤로 가기\n");
    printf("입력: ");
    scanf("%d", &select);

    categoryConnect(select);
    return;
}

void categoryConnect(int select)
{
    switch (select)
    {
    case 0:
        mainUi();
        break;
    case 1:
        inputCategoryName();
        break;
    case 2:
        retouchCategory();
        break;
    case 3:
        removeCategory();
        break;
    default:
        printf("잘못 입력하였습니다.\n");
        Sleep(1000);
        break;
    }
}

void inputCategoryName()
{
    printf("추가할 카테고리 이름: ");
    scanf("%s", categoryName);

    appendCategory();
    return;
}

void retouchCategory()
{
    FILE* fp = fopen(pathcategoryList, "r");
    if (!fp) { printf("카테고리 파일 열기 실패\n"); Sleep(1000); return; }

    char categories[100][64];
    int count = 0;
    while (fscanf(fp, "%s", categories[count]) != EOF) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("수정할 카테고리가 없습니다.\n"); Sleep(1000); return; }

    printf("수정할 카테고리 목록:\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, categories[i]);

    int select;
    printf("번호 선택: "); scanf("%d", &select);
    if (select < 1 || select > count) { printf("잘못된 선택입니다.\n"); Sleep(1000); return; }

    char newName[64];
    printf("새 카테고리 이름: "); scanf("%s", newName);


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
    fp = fopen(pathcategoryList, "w");
    for (int i = 0; i < count; i++) fprintf(fp, "%s\n", categories[i]);
    fclose(fp);

    Sleep(1000);
}

void removeCategory()
{
    FILE* fp = fopen(pathcategoryList, "r");
    if (!fp) { printf("카테고리 파일 열기 실패\n"); Sleep(1000); return; }

    char categories[100][64];
    int count = 0;
    while (fscanf(fp, "%s", categories[count]) != EOF) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    if (count == 0) { printf("삭제할 카테고리가 없습니다.\n"); Sleep(1000); return; }

    printf("삭제할 카테고리 목록:\n");
    for (int i = 0; i < count; i++) printf("[%d] %s\n", i + 1, categories[i]);

    int select;
    printf("번호 선택: "); scanf("%d", &select);
    if (select < 1 || select > count) { printf("잘못된 선택입니다.\n"); Sleep(1000); return; }


    char folderPath[256];
    sprintf(folderPath, "%s\\%s", pathcategory, categories[select - 1]);


    if (_rmdir(folderPath) == 0) {
        printf("폴더 삭제 완료\n");
    }
    else {
        printf("폴더 삭제 실패 (비어있지 않거나 권한 문제)\n");
    }


    fp = fopen(pathcategoryList, "w");
    for (int i = 0; i < count; i++) {
        if (i != select - 1) fprintf(fp, "%s\n", categories[i]);
    }
    fclose(fp);

    Sleep(1000);
}