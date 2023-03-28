#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STD_BUFFER 1024

char* readLine() { // function for reading the current line

    int curBufferSize = STD_BUFFER;
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
            curBufferSize += STD_BUFFER;
            line = realloc(line, sizeof(char) * curBufferSize);

            if (!line) { // checks for error
                printf("Error with Buffer.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

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

        interactiveMode();

    }

    return 0;
}