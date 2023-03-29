// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("Error with Buffer.\n");
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
                printf("Error: realloc of line.\n");
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
        printf("Error initializing tokens.");
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
                printf("Error with realloc.");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, delim);
    }
    tokens[pos] = NULL;
    return tokens;
}

void command(char** tokens) {

    char* firstToken = tokens[0];

    if (strcmp(firstToken, "cd") == 0) { // cd

        printf("cd command\n");

    } else if (strcmp(firstToken, "pwd") == 0) { // pwd

        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Current Working Directory: %s\n", cwd);

    } else {

        printf("will search for file in directories\n");

    }
    return;

}

int execute(char** tokens) {

    char* firstToken = tokens[0];
    
    if (firstToken[0] == '/') {

        printf("%s is a path to an executable program!\n", firstToken);

    } else {

        command(tokens);
        // Handle cd and pwd commands

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

        printf("mysh>"); // prompt
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

        printf("Welcome to my shell!\n");
        interactiveMode();

    }

    return 0;
}