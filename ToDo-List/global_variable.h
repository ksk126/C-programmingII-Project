#pragma once
#include "struct.h"

// -----------------------------
// 상수 정의
// -----------------------------
#define MAX_ID_LEN       20
#define MAX_PATH_LEN     256
#define MAX_TODO_COUNT   200

// -----------------------------
// 사용자 정보
// -----------------------------
extern char id[MAX_ID_LEN];
extern char pw[MAX_ID_LEN];

// -----------------------------
// 경로 관리
// -----------------------------
extern char path[MAX_PATH_LEN];
extern char pathlist[MAX_PATH_LEN];
extern char pathfriends[MAX_PATH_LEN];
extern char pathteams[MAX_PATH_LEN];
extern char pathcategory[MAX_PATH_LEN];
extern char pathcategoryList[MAX_PATH_LEN];
extern char pathcategoryfile[MAX_PATH_LEN];
extern char categoryName[MAX_PATH_LEN];
extern char pathteamsFile[MAX_PATH_LEN];
extern char pathteamsDir[MAX_PATH_LEN];

// -----------------------------
// 일정 관리
// -----------------------------
extern Todo list;
extern Todo todos[MAX_TODO_COUNT];
extern Todo todo;