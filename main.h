#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>

#define BUFFSIZE 1024
#define TOKEN_SIZE 128
#define TOKEN_DELIMITERS " \t\r\n\a"

extern char **environ;

/**
 * struct data - struct containing runtime data for the shell program
 * @argv: the argument vector
 * @cmdline: command line input written by the user
 * @tokenargs: array of tokens from the command line
 * @state: the exit status of the most recent shell command
 * @linenum: line number counter
 * @env_vars: environment variables
 * @pid: process identifier of the shell
 */
typedef struct data
{
	char **argv;
	char *cmdline;
	char **tokenargs;
	int state;
	int linenum;
	char **env_vars;
	char *pid;
} sh_data;

/**
 * struct sep_list_node - struct contains linked list to store separators
 * @separator: the separator characters (;, |, &)
 * @nxt: pointer to the next node in the list
 */
typedef struct sep_list_node
{
	char separator;
	struct sep_list_node *nxt;
} sep_t;

/**
 * struct cmdln_list_node - struct contains linked list to store command lines
 * @line: the command line
 * @nxt: pointer to the next node in the list
 */
typedef struct cmdln_list_node
{
	char *line;
	struct cmdln_list_node *nxt;
} cmdln_t;

/**
 * struct var_list_node - struct contains linked list to store variables
 * @var_len: varibale length
 * @value: varibale value
 * @val_len: value length
 * @nxt: pointer to the next node in the list
 */
typedef struct var_list_node
{
	int var_len;
	char *value;
	int val_len;
	struct var_list_node *nxt;
} var_t;

/**
 * struct builtin_cmd - struct containing built-in commands
 * @name: the name of the builtin commands (cd, ls, env)
 * @f: pointer to the associated function
 */
typedef struct builtin_cmd
{
	char *name;
	int (*f)(sh_data *dsh);
} builtin_t;

void cpy_mem(void *dst, const void *src, unsigned int size);
void *re_alloc(void *p, unsigned int prev_sz, unsigned int new_sz);
char **realloc_dp(char **p, unsigned int prev_sz, unsigned int new_sz);

int str_len(const char *str);
char *str_cat(char *dst, const char *src);
int str_cmp(char *str1, char *str2);
char *str_cpy(char *dst, char *src);
char *str_chr(char *str, char chr);
char *str_dup(const char *str);
void str_rev(char *str);
int str_spn(char *str, char *chr);
char *str_tok(char str[], const char *delim);
int is_digit(const char *str);
int char_cmp(char str[], const char *delim);
int cnt_rep_char(char *str, int idx);
int fst_char_index(char *str, int *idx);

sep_t *add_sep(sep_t **head, char sep);
void free_sep(sep_t **head);
cmdln_t *add_cmdln(cmdln_t **head, char *ln);
void free_cmdln(cmdln_t **head);
var_t *add_var(var_t **head, int vlen, char *val, int valen);
void free_var(var_t **head);
void add_lst_nodes(sep_t **sep_head, cmdln_t **cmdln_head, char *str);

int _intdigits(int num);
char *_sprintf(int num);
int ch_atoi(char *str);

int find_syn_err(char *str, int idx, char lschar);
void print_syn_err(sh_data *dsh, char *str, int idx, int ctrlerr);
int chck_syn_err(sh_data *dsh, char *str);
char *concatcd_err(sh_data *dsh, char *errmsg, char *error, char *cmd_ctr);
char *cd_cmd_err(sh_data *dsh);
char *cmd_not_found(sh_data *dsh);
char *sh_exit_err(sh_data *dsh);
char *env_err_msg(sh_data *dsh);
char *path126_err_msg(sh_data *dsh);

int get_error(sh_data *dsh, int err_val);
int (*get_builtin(char *cmd))(sh_data *);
void get_sigint(int sigh);
int get_help(sh_data *dsh);

char *read_input(int *is_eof);
char *char_swp(char *str, int swap);
int div_cmdln(sh_data *dsh, char *str);
char **tok_input(char *str);
char *strip_comms(char *str);

void exec_shell(sh_data *dsh);
void nxt_list(sep_t **sep_list, cmdln_t **cmdln_list, sh_data *dsh);
int check_cdir(char *path, int *idx);
int check_exec(sh_data *dsh);
int check_perms(char *dir, sh_data *dsh);

void check_env_vars(var_t **head, char *str, sh_data *dsh);
int proc_sp_vars(var_t **head, char *str, char *lst, sh_data *dsh);
char *sub_strvars(var_t **head, char *str, char *nstr, int nlent);
char *repvars_Instr(char *str, sh_data *dsh);
char *_execvp(char *cmd, char **env_vars);

void ret_line(char **lnptr, size_t *lnsize, char *buf, size_t bsize);
ssize_t get_line(char **lnptr, size_t *lnsize, FILE *stream);

int print_env(sh_data *dsh);
int cmp_env_var(const char *envname, const char *name);
char *_getenv(const char *name, char **env_vars);
char *cpy_env_info(char *name, char *val);
void set_env(char *name, char *val, sh_data *dsh);
int _setenv(sh_data *dsh);
int _unsetenv(sh_data *dsh);

void cd_dot(sh_data *dsh);
void cd_dash(sh_data *dsh);
void cd_tilde(sh_data *dsh);
void cd_path(sh_data *dsh);
int cd_sh(sh_data *dsh);

int sh_exit(sh_data *dsh);
int proc_cmdln(sh_data *dsh);
int exec_cmd(sh_data *dsh);

void env_help_info(void);
void setenv_help_info(void);
void unsetenv_help_info(void);
void gen_help_info(void);
void exit_help_info(void);
void help_info(void);
void alias_help_info(void);
void cd_help_info(void);

#endif
