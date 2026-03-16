#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <crypt.h>

/*
 * simple login screen
 * with minimal persis.
 * database (<crypt>)
 *
 */

// data
typedef struct {
    char *name;
    char *pass;
    //char *hash;
} User;

// fwd decl (funcs)
void PrintMenu(User *user);
void MenuHandler();
//char Register(User *user);
//int Login(User *user);
//int Logout(const char *user);
//int WriteUser(User *user); // writes User.* to disk
//User ReadUser(User *user); // reades User.* from disk, returns User*

// crypt
const char *salt = "$6$0x0d4743453$";
//char *hashed = crypt(plainPass, salt);


int main(void)
{
//    while (true) {
        // main loop
        PrintMenu(NULL);
//    }

    return 0;
}

void PrintMenu(User *user)
{
    // print user specific stuff
    if (user != NULL) {
        char welcomeMessage[8192];
        sprintf(welcomeMessage, "welcome back, %s", user->name);

        // open
        printf("╭");
        // top border
        for (unsigned int i = 0; i < strlen(welcomeMessage)+2; i++) // +2 forpadding
            printf("─");
        // close and message
        printf("╮\n│ %s │\n╰", welcomeMessage);
        // bottom
        for (unsigned int i = 0; i < strlen(welcomeMessage)+2; i++)
            printf("─");
        printf("╯\n");
    }
    printf(
        "╭──────────main menu──────────╮\n"
        "│ available options           │ \n"
        "│ - login                     │ \n"
        "│ - logout                    │ \n"
    );
    if (user == NULL)
        printf("│ - register                  │ \n");
    printf("╰─────────────────────────────╯\n");

    MenuHandler();
}

void MenuHandler()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);
    // strip \n
    if (read > 0 && line[read-1] == '\n') {
        line[read-1] = '\0';
    }
    if (read != -1) {
        if (strcmp(line, "login") == 0)
            printf("//TODO call Login() and pass over inputs.\n");

        if (strcmp(line, "logout") == 0)
            printf("//TODO call Logout() and pass over inputs.\n");

        if (strcmp(line, "register") == 0)
            printf("//TODO call Register() and pass over inputs.\n");
    }

    free(line);
}
