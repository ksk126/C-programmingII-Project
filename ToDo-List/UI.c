#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#include "struct.h"

//기능: tui 출력
//입력 매개변수: 구조체배열 받아야돼
//반환값: 사용자가 선택한 정수값 번호(0~3)
int Ui(Todo **todo)
{
	int select = 0;
	printf("--------메뉴--------\n");
	printf("0. 일정 목록\n");
	printf("1. 일정 추가\n");
	printf("2. 일정 수정 및 삭제\n");
	printf("3. 종료\n");
	printf("--------------------\n");
	printf("\n입력: ");
	scanf("%d", &select);

	return select;
}