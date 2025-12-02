#pragma once
#include <windows.h>

// 화면 초기화 (system("cls") 대체)
void clearScreen();

// 파일에서 문자열 목록 읽기
int loadListFromFile(const char* filepath, char list[][64], int maxCount);

// 목록 출력
void printList(const char list[][64], int count, const char* title);

// 선택 입력
int selectFromList(int count, const char* message);

// 문자열에서 괄호 앞 이름 추출 (예: "팀이름(멤버1,멤버2)" → "팀이름")
void extractNameBeforeParen(const char* src, char* dest);

// 문자열에서 개행 제거
void trimNewline(char* str);