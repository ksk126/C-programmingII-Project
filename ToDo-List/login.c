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

int inputLogin(const char* message)
{
    printf("%s", message);
    printf("ID: ");
    scanf("%s", id);

    if (!strcmp(id, "0"))
    {
        exit(0);
    }
    else if (!strcmp(id, "1"))
    {
        return 1;
    }

    printf("PW: ");
    scanf("%s", pw);
    return 0;
}

void login(int sign)
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        printf("회원 목록을 확인할 수 없습니다.\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    if (size == 0)
    {
        sign = 0;
    }

    while (1)
    {
        system("cls");

        if (sign == 0)
        {
            if (signup())
            {
                sign = 1;
                continue;
            }
            else
            {
                printf("회원가입 실패\n");
                Sleep(1000);
                continue;
            }
        }

        if (signin())
        {
            printf("로그인 성공!\n");
            Sleep(800);
            settingPath();
            break;
        }
        else
        {
            printf("로그인 실패. 회원가입 하시겠습니까? (y/n)\n");
            char select = getch();
            if (select == 'y')
            {
                sign = 0;
            }
        }
    }
}

int signup()
{
    int select = inputLogin("회원가입을 종료하려면 0, 로그인 하려면 1.\n");

    if (select == 1)
    {
        return 1;
    }

    if (!sameID())
    {
        printf("이미 존재하는 아이디입니다.\n");
        Sleep(1000);
        return 0;
    }

    printf("회원가입 성공!\n");
    Sleep(800);
    settingPath();
    appendMember();
    return 1;
}

int signin()
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        printf("회원 정보를 확인할 수 없습니다.\n");
        return 0;
    }

    char line[LINE];
    char fileId[MAXLOGIN];
    char filePw[MAXLOGIN];

    inputLogin("로그인 (0 입력시 종료)\n");

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "ID:%[^,],PW:%s", fileId, filePw) == 2)
        {
            if (!strcmp(id, fileId) && !strcmp(pw, filePw))
            {
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}

int sameID()
{
    FILE* fp = fopen("c:\\TodoList\\member.txt", "r");
    if (!fp)
    {
        return 1;
    }

    char line[LINE];
    char fileId[MAXLOGIN];

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "ID:%[^,]", fileId) == 1)
        {
            if (!strcmp(id, fileId))
            {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}