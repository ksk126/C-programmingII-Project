#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//���: ��������� ����ؼ� ��� ���, ��ü ���� ��ɰ� �̿ϷḸ ���� ���
//�Է� �Ű�����: void
//��ȯ��: ����ڰ� ������ ������ ��ȣ(1~2) 1�� ��ü ���� or �̿Ϸ� ����, 2�� �ڷ� ���� ����?
int list(char* view)
{
	int select = 0;

	printf("%s ���\n", view);
	if (strcmp("all", view) != 0)
	{
		printf("1. ��ü ��� ����\n");
	}
	else
	{
		printf("1. �̿Ϸ� ��� ����\n");
	}
	printf("2. �ڷ� ����\n");
	printf("\n�Է�: ");
	scanf("%d", &select);

	return select;
}