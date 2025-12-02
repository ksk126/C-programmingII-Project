#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

// -----------------------------
// 화면 초기화 (system("cls") 대체)
// -----------------------------
void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// -----------------------------
// 파일에서 문자열 목록 읽기
// -----------------------------
int loadListFromFile(const char* filepath, char list[][64], int maxCount) {
    FILE* fp = fopen(filepath, "r");
    if (!fp) return 0;

    int count = 0;
    while (fscanf(fp, "%63s", list[count]) != EOF) {
        count++;
        if (count >= maxCount) break;
    }
    fclose(fp);
    return count;
}

// -----------------------------
// 목록 출력
// -----------------------------
void printList(const char list[][64], int count, const char* title) {
    printf("------ %s ------\n", title);
    if (count == 0) {
        printf("(없음)\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("[%d] %s\n", i + 1, list[i]);
    }
    printf("-----------------------\n");
}

// -----------------------------
// 선택 입력
// -----------------------------
int selectFromList(int count, const char* message) {
    int select;
    printf("%s", message);
    if (scanf("%d", &select) != 1) {
        fflush(stdin);
        return -1;
    }
    if (select < 1 || select > count) {
        printf("잘못된 선택입니다.\n");
        Sleep(1000);
        return -1;
    }
    return select;
}

// -----------------------------
// 문자열에서 팀 이름 추출 (예: "팀이름(멤버1,멤버2)")
// -----------------------------
void extractNameBeforeParen(const char* src, char* dest) {
    char* openParen = strchr(src, '(');
    if (openParen) {
        strncpy(dest, src, openParen - src);
        dest[openParen - src] = '\0';
    }
    else {
        strcpy(dest, src);
    }
}

// -----------------------------
// 문자열에서 개행 제거
// -----------------------------
void trimNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}