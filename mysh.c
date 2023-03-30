// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
// macros
#define STD_LINE_BUFFER 1024
#define STD_TOKEN_BUFFER 64

// function for reading the current line
char* readLine() {

    int curBufferSize = STD_LINE_BUFFER;
    char* line = malloc(sizeof(char) * curBufferSize);
    int pos = 0; // ptr for traversing through the line
    char cur;

    if (!line) { // checks for error
        printf("malloc(line) has failed.\n");
        exit(EXIT_FAILURE);
    }

    while (1) { // infinite loop until return statement (when EOC or \n character)

        cur = getchar(); // looks at current character

        if (cur == EOF || cur == '\n') { // base case
            line[pos] = '\0';
            return line;
        } else { // continuation
            line[pos] = cur;
        }
        pos++;

        if (pos >= curBufferSize) {
            curBufferSize += STD_LINE_BUFFER;
            line = realloc(line, sizeof(char) * curBufferSize);

            if (!line) { // checks for error
                printf("realloc(line) has failed.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// function for splitting line into tokens
char** splitLine(char* line) {

    int curBufferSize = STD_TOKEN_BUFFER;
    char** tokens = malloc(sizeof(char*) * curBufferSize); // array of tokens
    char* token; // current character
    int pos = 0;
    char delim[] = " ";

    if (!tokens) {
        printf("initializing(tokens) has failed.\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, delim);
    while (token != NULL) {
        tokens[pos] = token;
        pos++;

        if (pos >= curBufferSize) {
            curBufferSize += STD_TOKEN_BUFFER;
            tokens = realloc(tokens, curBufferSize * sizeof(char*));
            if (!tokens) {
                printf("realloc has failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, delim);
    }
    tokens[pos] = NULL;
    return tokens;
}

// change cd to linux style once testing is over

void command(char** tokens) {

    int pos = 0;
    char* firstToken = tokens[pos];

    if (strcmp(firstToken, "cd") == 0) { // cd

        if (tokens[pos+1] == NULL) { // "cd" | home directory
            chdir("/home");
            if (chdir("/home") == -1) {
                printf("chdir has failed.\n");
            }
        } else if (tokens[pos+1][0] == '/' || tokens[pos+1][0] == '\\') { // "cd /..." | indicates the path
            printf("newDir: %s\n", tokens[pos+1]);
            chdir(tokens[pos+1]);
            if (chdir(tokens[pos+1]) == -1) {
                printf("chdir has failed.\n");
                if (errno == ENOENT) {
                printf("path not found.\n");
                }
            }
        } else {
            printf("cd : Cannot change directory to '%s' because it does not exist.\n", tokens[pos+1]);
        }

    } else if (strcmp(firstToken, "pwd") == 0) { // pwd

        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            printf("pwd has failed.\n");
            exit(EXIT_FAILURE);
        }

        printf("Current Working Directory: %s\n", cwd);

    } else if (strcmp(firstToken, "exit") == 0) { // exit
    
        printf("mysh: exiting\n");
        exit(EXIT_SUCCESS);

    } else if (strcmp(firstToken, "ls") == 0) { // ls
    
        // code for ls

    } else if (strcmp(firstToken, "echo") == 0) { // echo
        
        // code for echo

    } else { // typos for commands (usually)

        printf("%s : The term '%s' is not recognized as a built-in command.\n", firstToken, firstToken);

    }
    return;
}

void launch(char** tokens) { // launches applications

    char firstArg[STD_LINE_BUFFER] = ".";
    strcat(firstArg, tokens[0]);
    char* args[] = {firstArg, NULL};
    execv(args[0], args);
    return;

}

int execute(char** tokens) {

    char* firstToken = tokens[0];
    
    if (firstToken[0] != '/') { // commands

        command(tokens);

    } else { // executables (start with a slash)

        launch(tokens);

    }

    return 1;

}

// batch mode
void batchMode(char file[]) {

}

// loop for interactive mode
void interactiveMode() {

    char *line;
    char **tokens;
    int status;

    do {

        printf("mysh> "); // prompt
        line = readLine(); // reads the current line

        tokens = splitLine(line); // splits the line into separate tokens

        status = execute(tokens);

        free(line);
        free(tokens);

    } while (status);

}

int main(int argc, char** argv) {

    if (argc == 2) { // batch mode

        char fileName[strlen(argv[1])];
        strcpy(fileName, argv[1]);
        printf("%s\n", fileName);
        batchMode(fileName);

    } else { // interactive mode

        printf("WELCOME TO MY SHELL\n");
        interactiveMode();

    }

    return 0;
}