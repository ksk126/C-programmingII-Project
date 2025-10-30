#pragma once
typedef struct login {
	char id[20];
	char pw[20];
}Login;

typedef struct todo {
	int cheak;
	int date;
	char contents[128];
	char memo[64];
}Todo;