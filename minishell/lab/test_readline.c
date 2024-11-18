#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// 함수 원형(프로토타입)
// char *readline(const char *prompt);
void rl_clear_history(void);
int rl_on_new_line(void);
void rl_replace_line(const char *text, int clear_undo);
void rl_redisplay(void);

int main() {
    // readline: 사용자로부터 입력을 받음
    char *input = readline("Enter a command: ");
    if (input) {
        printf("You entered: %s\n", input);
        add_history(input);  // 입력을 히스토리에 추가
    }

    // rl_clear_history: 모든 히스토리를 지움
    rl_clear_history();
    printf("History cleared.\n");

    // rl_on_new_line: 새 줄로 이동했음을 readline에 알림
    rl_on_new_line();

    // rl_replace_line: 현재 줄의 내용을 새 텍스트로 교체
    rl_replace_line("This is a new line", 0);

    // rl_redisplay: 프롬프트와 편집 중인 줄을 다시 표시
    rl_redisplay();

    free(input);
    return 0;
}
