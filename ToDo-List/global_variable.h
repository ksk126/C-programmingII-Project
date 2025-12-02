#pragma once
#include "struct.h"
#define MAXLOGIN 20
#define LINE 128
#define MAX 200

extern char id[MAXLOGIN];
extern char pw[MAXLOGIN];
extern char path[LINE];
extern char pathlist[LINE];
extern char pathfriends[LINE];
extern char pathteams[LINE];
extern char pathcategory[LINE];
extern char pathcategoryList[LINE];
extern char pathcategoryfile[LINE];
extern char categoryName[LINE];
extern char pathteamsFile[LINE];
extern char pathteamsDir[LINE];

extern Todo list;
extern Todo todos[200];
extern Todo todo;