#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#define IP_SIZE 0
#define SH_KILLER "exit\n"
#define DELIMITER "=: \n\t"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **environ;
/**
 * struct garbage - recieves address to free
 * @trash: pointer to malloc
 * @next: points to the next node
 */
typedef struct garbage
{
        void *trash;
        struct garbage *next;
} garbage;
garbage *add_nodeint_end(garbage **head, void *trash);
void print_listint(garbage *h);
void free_list(garbage *head);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int check_malloc(void *alloc);
void free_garbage(char *path, char **cmd, int n);
char **tokenizer(char *line, garbage **head);
int _strlen(char *s);
char *path_finder(char *env[], garbage **head);
int str_cmp_first_chars(char *envs, char *namenv);
char *cat_cmd(char *cmd0, char **dirs, garbage **head);
char *_strcpy(char *dest, char *src);
int is_address(char *cmd0);
int _putchar(char c);
void not_found(char *argv0, char *cmd0, int cmd_counter, garbage **head);
void print_number(int n);
char *return_integer(int n);
void null_env(void);
/* String Handlers */
int _strlen(char *str);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
/* Path & Search Handlers */
char *path_append(char *path, char *command);
char *_getenv(char *name);
int getpathfile(char **args);
/* Built-ins Functions */
void shb_env(void);
int shb_exit(char **args, char *buffer, int loops);
void shb_cd(char **args);

void free_function(int n, ...);
int _isdigit(char *number);



int execute(char **args);

void print_prompt(void);
int main(char *argv[]);
unsigned int factorial(unsigned int n);
/* from _getline.c */
int _getline(char **lineptr, int fd);
/* from _realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif

