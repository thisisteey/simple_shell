#include "main.h"

/**
 * env_help_info - provides help information for the 'env' command
 * Return: void
 */
void env_help_info(void)
{
	char *help = "env: env [option] [name=value] [command] [args]\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Print the shell environment.\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * setenv_help_info - provides help information for the 'setenv' command
 * Return: void
 */
void setenv_help_info(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, str_len(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Add a new environment variable, or modify an existing one\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * unsetenv_help_info - provides help information for the 'unsetenv' command
 * Return: void
 */
void unsetenv_help_info(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Deletes a variable completely from the environment\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * exit_help_info - provides help information for the 'exit' command
 * Return: void
 */
void exit_help_info(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, str_len(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * alias_help_info - provides help information for the 'alias' command
 * Return: void
 */
void alias_help_info(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDefine or display aliases.\n";
	write(STDOUT_FILENO, help, str_len(help));
}
