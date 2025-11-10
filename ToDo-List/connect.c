#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#include "struct.h"

void connect(func fp)
{
	int select = 0;
	char view[8] = "none";

	while (1)
	{
		system("cls");
		if (fp == list)
		{
			select = list(view);
			switch (select)
			{
			case 0:
				(strcmp(view, "all") == 0)
					? strcpy(view, "none") : strcpy(view, "all");
				break;
			case 2:
				return;
			}
		}
		else
		{
			return;
		}
	}
	return;
}