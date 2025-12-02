#include "struct.h"

#define MAX_ID_LEN       20
#define MAX_PATH_LEN     256
#define MAX_TODO_COUNT   200

// 사용자 정보
char id[MAX_ID_LEN];
char pw[MAX_ID_LEN];

// 경로 관리
char path[MAX_PATH_LEN];
char pathlist[MAX_PATH_LEN];
char pathfriends[MAX_PATH_LEN];
char pathteams[MAX_PATH_LEN];
char pathcategory[MAX_PATH_LEN];
char pathcategoryList[MAX_PATH_LEN];
char pathcategoryfile[MAX_PATH_LEN];
char categoryName[MAX_PATH_LEN];
char pathteamsFile[MAX_PATH_LEN];
char pathteamsDir[MAX_PATH_LEN];

// 일정 관리
Todo list = { 0 };
Todo todos[MAX_TODO_COUNT] = { 0 };
Todo todo = { 0 };