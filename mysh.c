// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char* curToken; // pointer for current token
    const char delim[2] = " ";
    int pos = 0;

    if (!tokens) {
        printf("Error initializing tokens.");
        exit(EXIT_FAILURE);
    }

    curToken = strtok(line, delim);
    while (curToken != NULL) {
        tokens[pos] = curToken;
        pos++;

        if (pos >= curBufferSize) {
            curBufferSize += STD_TOKEN_BUFFER;
            realloc(tokens, sizeof(char*) * curBufferSize);
            if (!tokens) {
                printf("Error: realloc of tokens.");
            }
        }
        curToken = strtok(NULL, delim);
    }
    tokens[pos] = NULL; // ends the array with a null pointer
    return tokens;
}

int execute(char** tokens) {

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