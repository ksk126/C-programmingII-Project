#pragma once
typedef void (*func)(void);

void run();
void connect(func fp);
int Ui();
int list(char* view);
void addTodo();
void retouchTodo();