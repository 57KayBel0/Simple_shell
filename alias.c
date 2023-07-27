#include <stdio.h>
#include <stdlib.h>
#include <string.h

/**
 *Structure to store an alias
 *Array to store aliases
 *Function to find an alias by name
 *Function to print all aliases
 *Function to print specific aliases
 *Function to define or update aliases
 *Update existing alias
 *Create new alias
 *
 */
struct Alias
{
	char name[MAX_ALIAS_NAME_LENGTH];
	char value[MAX_ALIAS_VALUE_LENGTH];
};

struct Alias aliases[MAX_ALIAS_COUNT];
	int alias_count = 0;

/*Function to find an alias by name*/
int find_alias(char* name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/*Function to print all aliases*/
void print_all_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

/*Function to print specific aliases*/
void print_specific_aliases(char** names, int count) {
    for (int i = 0; i < count; i++) {
        int index = find_alias(names[i]);
        if (index != -1) {
            printf("%s='%s'\n", aliases[index].name, aliases[index].value);
        }
    }
}

/* Function to define or update aliases*/
void define_aliases(char** names, char** values, int count) {
    for (int i = 0; i < count; i++) {
        int index = find_alias(names[i]);

        if (index != -1) {
            /* Update existing alias*/
            strcpy(aliases[index].value, values[i]);
        } else {
            /* Create new alias*/
            if (alias_count >= MAX_ALIAS_COUNT) {
                printf("Error: Maximum alias count reached\n");
                return;
            }

            strcpy(aliases[alias_count].name, names[i]);
            strcpy(aliases[alias_count].value, values[i]);
            alias_count++;
        }
    }
}

int main() {
    char input[256];
    char* command;

    while (1) {
        printf("Shell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        /* Tokenize the input command*/
        command = strtok(input, " ");

        if (command == NULL) {
            continue;
        }

        if (strcmp(command, "alias") == 0) {
            char* arguments[MAX_ALIAS_COUNT];
            int count = 0;

            /* Parse the rest of the command and extract aliases and values*/
            while ((arguments[count] = strtok(NULL, " ")) != NULL) {
                count++;
            }

            if (count == 0) {
                /*Print all aliases if no arguments are provided*/
                print_all_aliases();
            } else if (count == 1) {
                /* Print specific aliases*/
                print_specific_aliases(arguments, count);
            } else {
                /*Define or update aliases*/
                int equal_sign_index;
                char* names[MAX_ALIAS_COUNT];
                char* values[MAX_ALIAS_COUNT];
                int alias_count = 0;

                for (int i = 0; i < count; i++) {
                    equal_sign_index = strcspn(arguments[i], "=");

                    if (equal_sign_index != strlen(arguments[i])) {
                        /* Define or update aliases with given value*/
                        names[alias_count] = malloc(equal_sign_index + 1);
                        strncpy(names[alias_count], arguments[i], equal_sign_index);
                        names[alias_count][equal_sign_index] = '\0';

                        values[alias_count] = malloc(strlen(arguments[i]) - equal_sign_index);
                        strcpy(values[alias_count], arguments[i] + equal_sign_index + 1);

                        alias_count++;
                    } else {
                        /* Print specific aliases*/
                        print_specific_aliases(&arguments[i], 1);
                    }
                }

                define_aliases(names, values, alias_count);

                /* Free dynamically allocated memory*/
                for (int i = 0; i < alias_count; i++) {
                    free(names[i]);
                    free(values[i]);
                }
            }
        } else {
            /* Implement other shell commands here*/
            /* ...*/
        }
    }

    return 0;
}

