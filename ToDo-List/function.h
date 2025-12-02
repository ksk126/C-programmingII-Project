#pragma once

// 실행 및 초기화
void run();
void openfile();
void makefile();

// 파일 관리
void appendMember();
void appendListFile();
void appendCategoryFile();
void appendFriendsFile();
void appendTeamsFile();

// UI
void mainUi();
void uiConnect(int select);

// 로그인
void login(int sign);
int inputLogin(const char* message);
int signup();
int signin();
int sameID();

// 경로 설정
void settingPath();
void settingCategoryPath();

// 카테고리
void category();
void categoryConnect(int select);
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

// 친구
void friends();
void friendsConnect(int select);
void appendfriend();
void removefriend();
void printFriendSummary();

// 팀
void teams();
void teamsConnect(int select);
void inputTeamName();
void retouchTeam();
void removeTeam();
void loadTeamTasks(const char* userId);
void selectTeamForTask(int mode);
void appendTeamTask(const char* teamName);
void removeTeamTask(const char* teamName);
void printTeamSummary();

// 일정 관리
int loadTodos();
void saveTodos(int count);
void appendTodo();
void qsortTodos(int count);
void retouchTodo();
int printTodoNum(int month, int day, int fcount, int count, int* found);