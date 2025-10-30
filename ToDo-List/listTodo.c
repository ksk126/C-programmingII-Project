#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//기능: 파일입출력 사용해서 목록 출력, 전체 보기 기능과 미완료만 보기 기능, 체크기능 만들어야되.
//입력 매개변수: view랑 구조체 배열도 받아야겟지요?
//반환값: 사용자가 선택한 정수값 번호(1~2) 0은 전체 보기 or 미완료 보기, back은 뒤로 가기
int list(char* view)
{
	int select = 0;

	printf("%s 출력\n", view);
	if (strcmp("all", view) != 0)
	{
		printf("0. 전체 목록 보기\n");
	}
	else
	{
		printf("0. 미완료 목록 보기\n");
	}
	printf("q. 뒤로 가기\n");
	printf("\n입력: ");
	scanf("%d", &select);

	return select;
}