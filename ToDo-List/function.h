#pragma once
void run();
void openfile();
void makefile();

void appendMember();
void appendListFile();
void appendCategoryFile();
void appendFriendsFile();
void appendTeamsFile();

void mainUi();
void uiConnect(int select);

void print0check();

void login(int sign);
int inputLogin(const char* message);
int signup();
int signin();
int sameID();

void settingPath();
void settingCategoryPath();

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

void inputCategoryName();
void appendCategory();
void appendCategoryListFile();
void appendTodoInCategory();
int printTodoNumInCategory(int month, int day, int fcount, int count, int* found);
void retouchTodoInCategory();
void saveTodosToCategory(int count);
int loadTodosToCategory();
void printCategorySummary();

void retouchCategory();
void removeCategory();

void appendfriend();
void removefriend();

void inputTeamName();
void retouchTeam();
void removeTeam();
void loadTeamTasks(const char* userId);
void selectTeamForTask(int mode);
void appendTeamTask(const char* teamName);
void removeTeamTask(const char* teamName);
void printTeamSummary();

void printFriendSummary();