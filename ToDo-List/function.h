#pragma once
#include "struct.h"

// -----------------------------
// main.c
// -----------------------------
void run();
void settingPath();
void settingCategoryPath();

// -----------------------------
// login.c
// -----------------------------
int inputLogin(const char* message);
void login(int sign);
int signup();
int signin();
int sameID();

// -----------------------------
// ui.c
// -----------------------------
void mainUi();
void uiConnect(int select);
void categoryConnect(int select);
void friendsConnect(int select);
void teamsConnect(int select);
void TitleOnBar(int width);
void printMiddleLine(const char* text, int width);
void TitleUnderBar(int width);
void gotoxy(int x, int y);

// -----------------------------
// file_manager.c
// -----------------------------
void openfile();
void makefile();
void appendMember();
void appendListFile();
void appendCategoryFile();
void appendFriendsFile();
void appendTeamsFile();
void appendCategory();
void appendCategoryListFile();

// -----------------------------
// todo.c (개인 일정)
// -----------------------------
int loadTodos();
void saveTodos(int count);
void appendTodo();
void qsortTodos(int count);
int printTodoNum(int month, int day, int fcount, int count, int* found);
void retouchTodo();
void completeTodo();

// -----------------------------
// category.c (카테고리 일정)
// -----------------------------
void inputCategoryName();
void retouchCategory();
void removeCategory();
void appendTodoInCategory();
void retouchTodoInCategory();
int loadTodosToCategory();
void saveTodosToCategory(int count);
int printTodoNumInCategory(int month, int day, int fcount, int count, int* found);
void completeTodoInCategory();
void printCategorySummary();

// -----------------------------
// friends.c
// -----------------------------
void appendfriend();
void removefriend();
void printFriendSummary();

// -----------------------------
// teams.c (팀 일정)
// -----------------------------
void inputTeamName();
void retouchTeam();
void removeTeam();
void selectTeamForTask(int mode);
void completeTeamTask(const char* teamName);
void appendTeamTask(const char* teamName);
void removeTeamTask(const char* teamName);
void printTeamSummary(const char* teamName);
