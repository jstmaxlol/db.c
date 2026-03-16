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
 * i am sleepy and idk i just
 * wanted to write some C and
 * draw boxes. haha.
 *
 * von    czjstmax
 *   <jstmaxlol at
 *     disroot dot
 *             org>
 */

// data
typedef struct {
    char *name;
    char *pass;
} User;

User *loggedUser = NULL;
FILE *f = NULL;             // 'database'-ish file
const char *filename = "users.txt";

// fwd decl (funcs)
void PrintMenu(User *u);
void MenuHandler(User *u);
//char Register(User *u);
void Login(User *u);
void Logout();
void WriteUser(); // writes user to disk
//User ReadUser(); // reades user from disk, returns User*
int BoxTitle(const char *str);
void TODO();


// crypt
const char *salt = "$6$0x0d4743453$";
//char *hash = crypt(plainPass, salt);
//if (strcmp(crypt(pass, stored_hash), stored_hash) == 0) //success


int main(void)
{
    while (true) {
        PrintMenu(NULL);
        if (loggedUser != NULL)
            WriteUser();
    }

    return 0;
}

void PrintMenu(User *u)
{
    // print user specific stuff
    if (loggedUser != NULL) {
        char *welcomeMessage = malloc(strlen("welcome back, ")+strlen(loggedUser->name)+2);
        int msgLen = sprintf(welcomeMessage, "welcome back, %s!", loggedUser->name);

        // open
        printf("╭");
        // top border
        for (int i = 0; i < msgLen+2; i++) // +2 forpadding
            printf("─");
        // close and message
        printf("╮\n│ %s │\n╰", welcomeMessage);
        // bottom
        for (int i = 0; i < msgLen+2; i++)
            printf("─");
        printf("╯\n");

        free(welcomeMessage);
    }
    printf(
        "╭──────────main menu──────────╮\n"
        "│   >> available options <<   │ \n"
        "│ - login      (1)            │ \n"
        "│ - logout     (2)            │ \n"
    );
    if (loggedUser == NULL)
        printf("│ - register   (3)            │ \n");
    printf("╰─────────────────────────────╯\n");

    MenuHandler(u);
}

void MenuHandler(User *u)
{
    char *line = NULL;
    size_t len = 0;

    printf("? ");
    ssize_t read = getline(&line, &len, stdin);
    // strip \n
    line[strcspn(line, "\n")] = '\0';

    if (read) {
        if (strcmp(line, "login") == 0 || strcmp(line, "1") == 0) {
            // allocate u if NULL
            if (u == NULL) {
                u = malloc(sizeof(User));
                if (!u) {
                    free(line);
                    return;
                }
            }
            free(line);
            Login(u);
        }
        else if (strcmp(line, "logout") == 0 || strcmp(line, "2") == 0) {
            free(line);
            Logout();
        }
        else if (strcmp(line, "register") == 0 || strcmp(line, "3") == 0) {
            //Register(u);
            free(line);
        }
        else {
            printf("(!) unknown option :(\n");
        }
    }
}

void Login(User *u)
{
    printf(">> login <<\n");

    char *line = NULL;
    size_t len = 0;

    printf("username? ");
    ssize_t read = getline(&line, &len, stdin);
    // strip \n
    line[strcspn(line, "\n")] = '\0';

    if (!read) 
        printf("(!!) err reading input\n");

    u->name = malloc(strlen(line)+1);
    strcpy(u->name, line);
    read = 0;

    printf("password? ");
    read = getline(&line, &len, stdin);
    // strip \n
    line[strcspn(line, "\n")] = '\0';

    u->pass = malloc(strlen(line)+1);
    strcpy(u->pass, line);

    char *hash = crypt(u->pass, salt);

    printf("%s:%s -> %s\n", u->name, u->pass, hash);

    if (loggedUser == NULL)
        loggedUser = malloc(sizeof(User));
    loggedUser->name = strdup(u->name);
    loggedUser->pass = strdup(u->pass);
    // free u->*
    free(u->name);
    free(u->pass);
}

void Logout()
{
    if (!loggedUser)
        return;
    // clear the loggedUser
    free(loggedUser->name);
    free(loggedUser->pass);
    free(loggedUser);
    loggedUser = NULL;
}

void WriteUser()
{
    f = fopen(filename, "a");
    if (f) {
        char *hash = crypt(loggedUser->pass, salt);
        fprintf(f, "%s:%s", loggedUser->name, hash);
    }
    fclose(f);

    printf("(!) wrote %s to %s\n", loggedUser->name, filename);
}

int BoxTitle(const char *str)
{
    printf("╭");
    for (unsigned int i = 0; i < strlen(str)/2; i++)
        printf("─");
    printf("%s", str);
    for (unsigned int i = 0; i < strlen(str)/2; i++)
        printf("─");
    printf("╮\n");

    return (int)strlen(str);
}

void TODO()
{
    printf("(!) TODO!\n");
}
