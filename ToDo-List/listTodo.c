#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//���: ��������� ����ؼ� ��� ���, ��ü ���� ��ɰ� �̿ϷḸ ���� ���, üũ��� �����ߵ�.
//�Է� �Ű�����: view�� ����ü �迭�� �޾ƾ߰�����?
//��ȯ��: ����ڰ� ������ ������ ��ȣ(1~2) 0�� ��ü ���� or �̿Ϸ� ����, back�� �ڷ� ����
int list(char* view)
{
	int select = 0;

	printf("%s ���\n", view);
	if (strcmp("all", view) != 0)
	{
		printf("0. ��ü ��� ����\n");
	}
	else
	{
		printf("0. �̿Ϸ� ��� ����\n");
	}
	printf("q. �ڷ� ����\n");
	printf("\n�Է�: ");
	scanf("%d", &select);

	return select;
}