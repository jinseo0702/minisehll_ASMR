#include "../../include/minishell.h"

static void init_terminal(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;  // Ctrl 문자 에코 비활성화
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 프로그램 종료 시
static void restore_terminal(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;   // 원래 상태로 복구
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// SIGINT 핸들러 (Ctrl-C)에 대해서 적었습니다
void signal_handler(int signo)
{
    if (signo == SIGINT) // Ctrl-C
    {
        init_terminal();
        if (isatty(STDIN_FILENO)) // 프롬프트 상태
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_replace_line("", 0);    // 입력된 라인 초기화
            rl_on_new_line();          // 새로운 줄 상태로 업데이트
            // rl_redisplay();            // 프롬프트 다시 표시
        }
    }
}
// SIGQUIT 핸들러 (Ctrl-\)에 대해서 적었습니다
void sigquit_handler(int signo)
{
    if (signo == SIGQUIT)
    {
        restore_terminal();
        printf("Quit (core dumped)\n");
        rl_redisplay();
    }
}
// 시그널 설정 하기 입니다
void signal_init(void)
{
    init_terminal();
    // SIGINT 처리 (Ctrl-C)
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("signal error for SIGINT");
    // SIGQUIT 처리 (Ctrl-\)
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal error for SIGQUIT");
}

void signal_turn_play(void)
{
    restore_terminal();
    // SIGINT 처리 (Ctrl-C) 해주기
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("signal error for SIGINT");
    // SIGQUIT 처리 (Ctrl-\) 해주기
    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
        perror("signal error for SIGQUIT");
}

void	signal_ctlc_heredoc(int sig)//히어독 시그널 아직까지 안했어서, 히어독 하면 시그널 같이 넣어줘야합니다. sigint만 새로 지정해주면 됩니다. 
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}


void prompt(t_mi *mi)
{
    while (1)
    {
        signal_init(); // 시그널 처리 설정
        // readline으로 사용자 입력 받기
        if ((mi->input = readline("~$ ")) != NULL)
        {
            signal_turn_play();
            // 입력값이 존재하면 히스토리에 추가
            // if (*mi->input)
                add_history(mi->input);
            rl_redisplay();
            control_cmd(mi); // 입력 명령 처리
        }
        else // readline이 NULL 반환 (ctrl-D 입력 시)
        {
            ft_freenull((&mi->input));
            ft_free_env(mi->env);
            ft_free_env(mi->export);
            exit(0);              // 정상 종료
        }
        // 입력 처리 후 메모리 해제
        ft_freenull(&(mi->input));
        ft_free_pcon(mi->head);
        mi->pcnt = 0;
		mi->file = 0;
    }
}

//히어독 만들기