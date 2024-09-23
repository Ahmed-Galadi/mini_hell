#include <editline/readline.h>
#include <libc.h>
#include "minishell.h"

int main(void) {
    // Directly pass the prompt to readline()
    char *cmd_line_args = readline(BLUE_FG"❯ "RESET);
    
    if (cmd_line_args) {
        add_history(cmd_line_args);
        free(cmd_line_args);
    }
    return 0;
}

