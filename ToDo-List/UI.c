#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "function.h"
#include "struct.h"

//���: tui ���
//�Է� �Ű�����: void
//��ȯ��: ����ڰ� ������ ������ ��ȣ(0~3)
int Ui()
{
	int select = 0;
	printf("--------�޴�--------\n");
	printf("0. ���� ���\n");
	printf("1. ���� �߰�\n");
	printf("2. ���� ���� �� ����\n");
	printf("3. ����\n");
	printf("--------------------\n");
	printf("\n�Է�: ");
	scanf("%d", &select);

	return select;
}