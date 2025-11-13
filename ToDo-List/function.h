#pragma once
void run();
void openfile();
void makefile();

void appendMember();
void appendList();
void appendFriends();
void appendTeams();

void mainUi();
void uiConnect(int select);

void print0check();

void login(int sign);
int inputLogin(const char* message);
int signup();
int signin();
int sameID();

void settingPath();

void category();
void friends();
void teams();

void categoryConnect(int select);
void friendsConnect(int select);
void teamsConnect(int select);

int loadTodos();
void saveTodos(int count);
void appendTodo();
void qsortTodos(int count);

void retouchTodo();
int printTodoNum(int month, int day, int fcount, int count, int* found);