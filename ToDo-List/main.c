#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//main.c에 남아야되는거. int main()이랑 run()함수.
//connect.c파일 하나 만들고 UI.c하나 만들고 list.c 만들고
//append.c, retouch.c 이렇게?하면 ? 될듯?
/*
0.목록
1.일정 추가
2.수정 및 삭제
3.종료
*/

int main()
{
	run();
	return 0;
}

void run()
{
	func fp = NULL;
	int select = 0;
	while (1)
	{
		system("cls");
		select = Ui();
		switch (select)
		{
		case 0:
			fp = list;
			connect(fp);
			break;
		case 1:
			fp = addTodo;
			connect(fp);
			break;
		case 2:
			fp = retouchTodo;
			connect(fp);
			break;
		case 3:
			printf("종료합니다.");
			break;
		default:
			printf("유효하지 않은 번호입니다.\n");
			Sleep(1000);
			system("cls");
		}

		if (select == 3)
		{
			break;
		}
	}
	return;
}