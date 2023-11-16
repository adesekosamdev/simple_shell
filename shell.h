#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/************* MACROS **************/

/* Prompt to be printed */
#define PROMPT_WORD "Bazzy's Shell $ "

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILTIN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argumenthelp is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Displays information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @exec_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @first_cmd: pointer to the first command typed by the user
 * @exec_count: number of excecuted comands
 * @file_desc_cmd: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environment
 * @alias_list: array of pointers with aliases.
 */

typedef struct info
{
	char *exec_name;
	char *input_line;
	char *first_cmd;
	int exec_count;
	int file_desc_cmd;
	char **tokens;
	char **env;
	char **alias_list;
} program_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */

typedef struct builtins
{
	char *builtin;
	int (*function)(program_data *data);
} builtins;


/************** PRINT FUNCTIONS **************/

int bazzy_print(char *string);
int _print_err(char *string);
int _print_error(int errorcode, program_data *data);


/************* MAIN FUNCTIONS *************/

void init_data(program_data *data, int arc, char *argv[], char **env);
void prompt_loop(char *prompt, program_data *data);
void ctrl_c_handler(int opr UNUSED);


/************** STRING FUNCTIONS **************/

int _strlen(char *string);
char *_strdup(char *string);
int _strcmp(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_rev(char *string);


/*======== num_aux.c ========*/

void num_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_chars(char *string, char *character);


/*======== str_tok.c ========*/

void tokenize(program_data *data);
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

int execute_cmd(program_data *data);


/*========  _getline.c  ========*/

int _getline(program_data *data);
int check_log_opers(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

void expand_vars(program_data *data);
void expand_alias(program_data *data);
int add_buffer(char *buffer, char *str_to_add);


/*======== builtins_list.c ========*/

int builtins_list(program_data *data);


/*======== find_in_path.c ========*/

char **tokenize_path(program_data *data);
int find_program(program_data *data);
int check_for_file(char *full_path);


/************** MEMORY MANAGEMENT **************/

void free_pointer_array(char **directories);
void free_req_data(program_data *data);
void free_all_data(program_data *data);


/************** BUILTINS **************/

int builtin_exit(program_data *data);
int builtin_cd(program_data *data);
int set_working_directory(program_data *data, char *new_dir);
int builtin_help(program_data *data);
int builtin_alias(program_data *data);


/*======== builtins_env.c ========*/

int builtin_env(program_data *data);
int set_builtin_env(program_data *data);
int unset_builtin_env(program_data *data);


/************** ENVIRONMENT VARIABLES **************/

char *get_env_key(char *name, program_data *data);
int set_env_key(char *key, char *value, program_data *data);
int rm_env_key(char *key, program_data *data);
void print_environ(program_data *data);


/*======== alias_management.c ========*/

int print_alias(program_data *data, char *alias);
char *get_alias(program_data *data, char *alias);
int set_alias(char *alias_string, program_data *data);


#endif
