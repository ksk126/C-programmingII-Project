#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//main.c�� ���ƾߵǴ°�. int main()�̶� run()�Լ�.
//connect.c���� �ϳ� ����� UI.c�ϳ� ����� list.c �����
//append.c, retouch.c �̷���?�ϸ� ? �ɵ�?
/*
0.���
1.���� �߰�
2.���� �� ����
3.����
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
			printf("�����մϴ�.");
			break;
		default:
			printf("��ȿ���� ���� ��ȣ�Դϴ�.\n");
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