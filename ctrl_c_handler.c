#include "shell.h"

/**
 * ctrl_c_handler - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */

void ctrl_c_handler(int opr UNUSED)
{
	bazzy_print("\n");
	bazzy_print(PROMPT_WORD);
}
