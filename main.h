#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command from user
 * @args: arguments of the command line
 * @status: status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID 
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct separator_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separator_list_s
{
	char separator;
	struct separator_list_s *next;
} separator_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_variable_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_variable_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_variable_list *next;
} r_variable;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


separator_list *add_separator_end(separator_list **head, char sep);
void free_separator_list(separator_list **head);
line_list *add_line_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_variable *add_rvariable_end(r_variable **head, int lengthvar, char *val, int lvalue);
void free_rvariable_list(r_variable **head);
char *_stradd(char *dest, const char *source);
char *_strcopy(char *dest, char *source);
int _strcompare(char *str1, char *str2);
char *_strchar(char *str, char c);
int _strlps(char *str, char *acpt);
void _memcopy(void *destptr, const void *srcptr, unsigned int size);
void *_rlocate(void *ptr, unsigned int size1, unsigned int size2);
char **_rlocatedp(char **ptr, unsigned int size1, unsigned int size2);   
char *_strdp(const char *str);
int _strlength(const char *str);
int compare_schar(char str[], const char *delim);
char *_strsplt(char str[], const char *delim);
int _isnum(const char *str); 
void str_rev(char *str);
int rep_char(char *input, int i);
int synerr_find(char *input, int i, char lchar);
int fchar_index(char *input, int *i);
void synerr_print(data_shell *datastruc, char *input, int i, int bool);
int synerr_check(data_shell *datastruc, char *input);
char *rem_comment(char *input);
void loop(data_shell *datastruc);  
char *input_read(int *i_eof);
char *char_swap(char *input, int bool);
void add_nodes(sep_list **head_sep, line_list **head_com, char *input);
void next_com(list_sept **list_sep, line_list **list_com, data_shell *datastruc);
int split_com(data_shell *datastruc, char *input);
char **split_input(char *input);
void env_check(r_variable **h, char *in, data_shell *data);
int var_check(r_variable **h, char *in, char *st, data_shell *data);
char *input_replace(r_variable **head, char *input, char *new_input, int nlen);
char *var_replace(char *input, data_shell *datastruc);   
void accept_input(char **inputptr, size_t *i, char *buffer, size_t b);
ssize_t stream_read(char **inputptr, size_t *i, FILE *stream);      
int exect_line(data_shell *datastruc);       
int currdir(char *path, int *i);
char *_loccmd(char *cmd, char **_envn);
int execut(data_shell *datastruc);
int check_cmd(char *dir, data_shell *datastruc);
int exect_cmd(data_shell *datastruc);             
char *_getenvn(const char *name, char **_envn);
int _envn(data_shell *datastruc);         
char *cpy_info(char *name, char *val);
void set_envn(char *name, char *val, data_shell *datastruc);
int _setenvn(data_shell *datastruc);
int del_setenvn(data_shell *datastruc);           
void cd_dotdot(data_shell *datastruc);
void user_cd(data_shell *datastruc);
void pre_cd(data_shell *datastruc);
void cd_homedir(data_shell *datastruc);     
int shell_cd(data_shell *datastruc);    
int (*get_btin(char *cmd))(data_shell *datastruc);        
int ext_shell(data_shell *datastruc);
int get_length(int n);
char *aux_intstr(int n);
int _strint(char *s);
char *stradd_cd(data_shell *, char *, char *, char *);
char *cd_error(data_shell *datastruc);
char *no_error(data_shell *datastruc);
char *err_exit_shell(data_shell *datastruc);
char *error_get_alias(char **args);
char *err_envn(data_shell *datastruc);
char *error_syntax(char **args);
char *error_permission(char **args);
char *err_path_126(data_shell *datastruc);
int get_err(data_shell *datastruc, int errval);
void sigint(int sig);
void aux_hlp_envn(void);
void aux_hlp_setenvn(void);
void aux_hlp_delsetenvn(void);
void aux_hlp_general(void);
void aux_hlp_exit(void);
void aux_hlp(void);
void aux_hlp_alias(void);
void aux_hlp_cd(void);
int get_hlp(data_shell *datastruc);

#endif
