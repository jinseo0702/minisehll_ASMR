
int handle_single_quotes(char *str, char *result, int *i, int *res_idx);
int handle_double_quotes(char *str, char *result, int *i, int *res_idx);
int handle_env_variable(char *str, char *result, int *i, int *res_idx);
char *expand_env_var_with_quotes(char *str);

void signal_handler(int signo);
void signal_init(void);
//---------------------------------------------
//heredoc
int    play_heredoc(char *val);
void	signal_ctlc_heredoc(int sig);
