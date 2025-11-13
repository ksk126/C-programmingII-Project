#pragma once
#define MAXLOGIN 20
#define LINE 128
#define MAX 200

typedef struct todo
{
    int check;
    int month;
    int day;
    char tasks[MAX];
    char memo[MAX];
} Todo;