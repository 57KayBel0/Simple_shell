#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

// Function to expand variables in the command (same as previous implementation)
void expand_variables(char* command) {
    // ... (same as before)
}

// Function to execute a single command
void execute_command(char* command) {
    // ... (same as before)
}

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (true) {
        printf("Shell> ");
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Ignore comments in the command
        char* comment = strchr(input, '#');
        if (comment != NULL) {
            // Truncate the input at the position of the comment
            *comment = '\0';
        }

        // Expand variables in the command
        expand_variables(input);

        // Check if the command is empty (due to a comment)
        if (strlen(input) == 0) {
            continue;
        }

        // Execute the command
        execute_command(input);
    }

    return 0;
}

