#pragma once

// -----------------------------
// 일정(Todo) 구조체 정의
// -----------------------------
typedef struct {
    int check;          // 완료 여부 (0 = 미완료, 1 = 완료)
    int month;          // 월
    int day;            // 일
    char tasks[64];     // 할일 내용
    char memo[128];     // 메모
} Todo;