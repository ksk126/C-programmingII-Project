#pragma once
typedef void (*func)(void);

void run();
void connect(func fp);
int Ui(Todo **todo);
int list(char* view, Todo** todo);
void addTodo();
void retouchTodo();