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

// 회원가입, 로그인 입력
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

// 회원가입, 로그인 입력
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