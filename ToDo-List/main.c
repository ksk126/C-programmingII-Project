#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#define MAXLOGIN 20
#define LINE 128
#define MAX 200
//main.c에 남아야되는거. int main()이랑 run()함수.
//connect.c파일 하나 만들고 UI.c하나 만들고 list.c 만들고
//append.c, retouch.c 이렇게?하면 ? 될듯?
/*
0.목록
1.일정 추가
2.수정 및 삭제
3.종료
*/

void run();
void openfile();
char* login(int sign, FILE * fp);
void ui(FILE* fp, Todo list, const char* path);
void uiConnect(int select, const char* path, Todo list);
void appendTodo(const char* path, Todo list);
int inputLogin(char* id, char* pw, const char* message);
int signup(char *id, char *pw, FILE *fp);
int signin(char *id, char *pw, FILE *fp);
int sameID(char* id, char* pw, FILE *fp);
void appendMember(char* id, char* pw, FILE *fp);
char* settingPath(char* id, FILE* fp, char* path);

typedef struct todo {
	int month;
	int day;
	char tasks[MAX];
	char memo[MAX];
}Todo;

int main()
{
	openfile();
	run();

	return 0;
}

void openfile()
{
	if (_mkdir("c:\\TodoList") == 0)
	{
		printf("");
	}
	
	FILE* fp = NULL;
	
	fp = fopen("c:\\TodoList\\member.txt", "a");
	if (fp == NULL)
	{
		printf("파일 열기 실패");
		exit(0);
	}

	fclose(fp);

	return;
}

void run()
{
	char id[MAXLOGIN];
	char pw[MAXLOGIN];
	char path[LINE];
	FILE* fp = NULL;
	int sign = 1;
	Todo list = { 0 };
	strcpy(id, login(id, pw, sign, fp));
	strcpy(path, settingPath(id, fp));
	ui(fp, list, path);

	return;
}

int inputLogin(char* id, char* pw, const char* message)
{
	printf("%s", message);
	printf("ID: ");
	scanf("%s", id);
	if (!strcmp(id, "0"))
	{
		exit(0);
	}
	else if (!strcmp(id, "1"))
	{
		return 1;
	}
	printf("PW: ");
	scanf("%s", pw);

	return 0;
}

char* login(char *id, char *pw, int sign, FILE* fp)
{
	fp = fopen("c:\\TodoList\\member.txt", "r");
	if (fp == NULL)
	{
		printf("회원 목록을 확인할 수 없습니다.");
		exit(0);
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fclose(fp);
	if (size == 0) {
		sign = 0;
	}

	while (1)
	{
		system("cls");
		//파일이 비어있을 경우 회원가입 먼저
		if (sign == 0)
		{
			if (signup(id, pw, fp))
			{
				sign = 1;
			}
			else
			{
				printf("회원가입 실패\n");
				Sleep(1000);
				continue;
			}
		}

		//로그인
		if (signin(id, pw, fp))
		{
			printf("로그인 성공\n");
			Sleep(1000);
			break;
		}
		else
		{
			printf("로그인 실패. 회원가입 하시겠습니까? (y/n)\n");

			char select = getch();

			if (select == 'y')
			{
				sign = 0;
				continue;
			}
			else if (select == 'n')
			{
				continue;
			}
			else
			{
				printf("잘못 입력하였습니다.\n");
				Sleep(1000);
			}
		}
	}
	return id;
}

//member,txt파일에 회원정보 추가, memberTodo 파일 생성
void appendMember(char* id, char* pw, FILE* fp)
{
	fp = fopen("c:\\TodoList\\member.txt", "a");
	if (fp == NULL)
	{
		printf("파일 정보 추가 실패");
		exit(0);
	}

	fprintf(fp, "ID:%s,PW:%s\n", id, pw);

	fclose(fp);

	return;
}

char* settingPath(char *id, FILE* fp, char *path)
{
	sprintf(path, "c:\\TodoList\\%s.txt", id);

	fp = fopen(path, "a");
	if (fp == NULL)
	{
		printf("파일 추가 실패");
		exit(0);
	}

	fclose(fp);

	return path;
}

//회원가입
int signup(char* id, char *pw, FILE * fp)
{
	int select = 0;
	system("cls");
	select = inputLogin(id, pw, "회원가입을 종료하려면 0(프로그램 종료), 로그인 하려면 1.\n");

	if (select == 1)
	{
		return 1;
	}

	if (!sameID(id, pw, fp))
	{
		return 0;
	}
	else
	{
		//회원 정보 추가
		appendMember(id, pw, fp);
		printf("회원가입 성공\n");
		Sleep(1000);
	}

	return 1;
}

//로그인
int signin(char *id, char *pw, FILE *fp)
{
	system("cls");
	fp = fopen("c:\\TodoList\\member.txt", "r");
	if (fp == NULL)
	{
		printf("회원 정보를 확인할 수 없습니다.");
		Sleep(1000);
		return 0;
	}
	char line[LINE];
	char fileId[MAXLOGIN], filePw[MAXLOGIN];

	inputLogin(id, pw, "로그인을 종료하려면 0(프로그램 종료).\n");

	while (fgets(line, sizeof(line), fp))
	{
		if (sscanf(line, "ID:%[^,],PW:%s", fileId, filePw) == 2)
		{
			if (!strcmp(id, fileId) && !strcmp(pw, filePw))
			{
				fclose(fp);
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

//같은 id인지 확인
int sameID(char* id, char* pw, FILE *fp)
{
	char fileId[MAXLOGIN];
	fp = fopen("c:\\TodoList\\member.txt", "r");

	if (fp == NULL)
	{
		printf("회원 정보를 불러올 수 없습니다.");
		exit(0);
	}

	char line[LINE];
	while (fgets(line, sizeof(line), fp))
	{
		line[strcspn(line, "\n")] = 0;

		if (strlen(line) == 0 || line[0] == '\n')
		{
			break;
		}

		if (sscanf(line, "ID:%[^,]", fileId) == 1)
		{
			if (!strcmp(id, fileId))
			{
				printf("이미 있는 아이디입니다.\n");
				return 0;
			}
		}
	}
	fclose(fp);

	return 1;
}

void ui(FILE * fp, Todo list, const char* path)
{
	char line[LINE];
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("파일을 불러올 수 없습니다.");
		exit(0);
	}
	while (fgets(line, sizeof(line), fp))
	{
		printf("%s\n", line);
	}

	fclose(fp);

	system("cls");
	int select = 0;
	printf("----------메뉴---------\n");
	printf("0. 목록\n");
	printf("1. 일정 추가\n");
	printf("2. 수정 및 삭제\n");
	printf("3. 로그아웃\n");
	printf("----------------------=\n");
	printf("입력: ");
	scanf("%d", &select);

	uiConnect(select, path, list);

	return 0;
}

void uiConnect(int select, const char* path, Todo list)
{
	switch (select)
	{
	case 0:
		break;
	case 1:
		appendTodo(path, list);
		break;
	case 2:
		break;
	case 3:
		login(0, 0, 1, NULL);
	}
	return;
}

void appendTodo(const char *path, Todo list)
{
	char todo[64];
	printf("날짜 입력->mm/dd\n");
	printf("날짜|할일|비고: ");
	getchar();  // 버퍼 비우기
	fgets(todo, sizeof(todo), stdin);
	todo[strcspn(todo, "\n")] = 0;

	char* token = strtok(todo, "/");
	list.month = atoi(token);

	char* ptr = strtok(todo, "/");
	
	if (ptr == NULL)
	{
		list.month = ptr;
		ptr = strtok(NULL, "|");
	}
	if (ptr == NULL)
	{
		list.day = ptr;
		ptr = strtok(NULL, "|");
	}
	if (ptr == NULL)
	{
		strcpy(list.tasks, ptr);
		ptr = strtok(NULL, "|");
	}
	if (ptr == NULL)
	{
		strcpy(list.memo, ptr);
		ptr = strtok(NULL, "|");
	}

	FILE* fp = NULL;
	fp = fopen(path, "a");
	if (fp == NULL)
	{
		printf("파일 열기 실패");
		return;
	}
	fprintf("%d %s/%s %s %s", 0, list.month, list.day, list.tasks, list.memo);

	fclose(fp);

	return;
}