#include "main.h"

/**
 * cd_help_info - provides help information on the 'cd' command
 * Return: void
 */
void cd_help_info(void)
{
	char *help = "cd: cd [-L |[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * help_info - provides information on the 'help' command
 * Return: void
 */
void help_info(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDisplay information about builtin commands.\n";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Displays brief summaries of the builtin commands.\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * gen_help_info - provides general user assitance on using the help command
 * Return: void
 */
void gen_help_info(void)
{
	char *help = "(: TAA, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = " alias: alias [name=['string']]\n";
	write(STDOUT_FILENO, help, str_len(help));
	help = " cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
	write(STDOUT_FILENO, help, str_len(help));
	help = " exit: exit [n]\n";
	write(STDOUT_FILENO, help, str_len(help));
	help = " env: env [option] [name=value] [command [args]]\n";
	write(STDOUT_FILENO, help, str_len(help));
	help = " setenv: setenv [variable] [value]\n unsetenv: ";
	write(STDOUT_FILENO, help, str_len(help));
	help = " unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, help, str_len(help));
}
