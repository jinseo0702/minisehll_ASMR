#include "../../include/minishell.h"
/*
void prompt(t_mi *mi)
{
    while (1)
    {
        if ((mi->input = readline("~$ ")) != NULL)
        {
			add_history(mi->input);
			rl_redisplay();
            control_cmd(mi);
        }
        else
        {
            ft_freenull(mi->input);
            exit (1);//에러처리는 고민해야 하는 부분입니다.
        }
        ft_freenull(mi->input);
        ft_free_pcon(mi->head);
		mi->pcnt = 0;
		mi->file = 0;
    }
}
*/
/*
void signal_handler(int signo, siginfo_t *siginfo, void *context)
{
    (void)context;
    (void)siginfo;

    if (signo == SIGINT) // ctrl-C
    {
        rl_replace_line("", 0); // 현재 입력 라인 초기화
        rl_on_new_line();       // 새로운 라인으로 상태 업데이트
        rl_redisplay();         // 새로운 프롬프트 표시
    }
    else if (signo == SIGQUIT) // ctrl-\ 무시
    {
        // 아무 동작도 하지 않음
    }
}
void setup_signals(void)
{
    struct sigaction sig;

    sig.sa_flags = SA_RESTART | SA_SIGINFO;
    sig.sa_sigaction = signal_handler;
    sigemptyset(&sig.sa_mask);
    if (sigaction(SIGINT, &sig, NULL) == -1)
        perror("sigaction error for SIGINT");
    sig.sa_handler = SIG_IGN; // SIGQUIT 무시
    if (sigaction(SIGQUIT, &sig, NULL) == -1)
        perror("sigaction error for SIGQUIT");
}
void prompt(t_mi *mi)
{
    setup_signals(); // 시그널 처리 설정
    while (1)
    {
        if ((mi->input = readline("~$ ")) != NULL)
        {
            add_history(mi->input);
            control_cmd(mi);
        }
        else
        {
            ft_freenull(mi->input);
            write(1, "exit\n", 5); // 종료 메시지
            exit(0); // 정상 종료
        }
        ft_freenull(mi->input);
        ft_free_pcon(mi->head);
    }
}
*/
/*
void signal_handler(int signo)
{
    if (signo == SIGINT) // ctrl-C
    {
        write(1, "\n", 1); // 프롬프트 출력
        rl_replace_line("", 0); // 현재 입력 라인 초기화
        rl_on_new_line();       // 새로운 라인으로 상태 업데이트
        rl_redisplay();         // 프롬프트 다시 표시
    }
}
void setup_signals(void)
{
    // SIGINT(ctrl-C) 처리
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("signal error for SIGINT");
    // SIGQUIT(ctrl-\) 무시
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal error for SIGQUIT");
}
*/
void display_ascii(void)
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    {
        perror("ioctl");
        return;
    }
    // ANSI escape sequences for bold and color
    const char *siuuu_ascii =
        "\033[1;32m" // Bold blue
        "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠋⠉⠉⠉⠙⠛⢿⠿⠛⠛⠛⠛⠛⠿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⢀⡀⠤⠤⢄⣀⠐⡄⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣿⣿⠟⠀⠀⠀⠐⠁⠀⠀⢀⣀⣀⣉⣒⣄⠉⠉⠉⢉⣀⣂⠈⠙⠻⣿⣿\n"
        "⣿⣿⣿⠟⠉⡄⠀⠀⠀⠠⠤⣐⠭⠒⠉⠉⠉⠉⣒⣳⠈⠛⠂⠀⠀⣒⣛⡢⠈⢿\n"
        "⣿⣿⠁⠀⠀⠃⠀⠀⠈⠛⠛⠠⣤⣶⠖⠙⠀⡉⢻⡿⣶⣿⣿⠁⡂⠠⠈⢿⠗⢸\n"
        "⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠂⠭⠤⠤⠤⣤⠄⠊⠀⠀⠈⠀⠀⠀⠀⢀⣶⣿\n"
        "⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠒⠉⠀⠀⠀⠈⠁⠒⠂⠈⠁⠘⢿⣿⣿\n"
        "⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿\n"
        "⡇⠀⠀⠀⠀⠀⠀⠀⠀⣾⣟⣛⣛⣻⡶⠶⠶⣶⣤⣤⣤⣤⣤⣤⣤⡶⠾⢃⣼⣿\n"
        "⣷⡀⠀⠀⠀⠀⠀⠘⢄⡀⠀⠀⠉⠉⠙⠛⠛⠛⠓⠛⠻⠿⠿⠷⠿⠟⢃⣼⣿⣿\n"
        "⣿⣿⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⣿⣿⣿\n"
        "⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⡿⠁⠀⠀⢠⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡶⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⠃⠀⠀⢀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⢠⢶⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⡄⠀⢠⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠋⢸⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⡏⠀⠀⠀⠀⢰⣶⣤⣤⣤⣤⣤⣴⣦⡀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
        "⣿⣿⣿⣷⣄⣀⣀⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣄⣀⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
"   ###     #####   ##   ##  ## ###\n"
"  ## ##   ##   ##  ### ###  ###  ##\n" 
" ##   ##  ##       #######  ##   ##\n" 
" #######   #####   ## # ##  ######\n"  
" ##   ##       ##  ##   ##  ## ##\n"   
" ##   ##  ##   ##  ##   ##  ##  ###\n" 
" ##   ##   #####   ##   ##  ##   ##\n" 
        "\033[0m"; // Reset color
    // 중앙 정렬을 위해 빈 줄 계산
    int padding = (ws.ws_row - 50) / 6; // 5 lines of "SIUUU" ASCII art
    for (int i = 0; i < padding; i++)
        write(1, "\n", 1);
    // "SIUUU" 출력
    write(1, siuuu_ascii, strlen(siuuu_ascii));
    // 한 줄 띄우기
    write(1, "\n", 1);
}

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
    // const char *prompt_str = "\033[32m~$ \033[0m"; // 초록색 프롬프트 설정하기
   // display_ascii();
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