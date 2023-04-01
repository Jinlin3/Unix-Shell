# CS214 - myshell (Jack Lin - jjl327)
### Implementation
The basic cycle of this shell is as follows: read, parse, and execute.

### readLine()
This function takes in a line from standard input, stores the string, and returns it.

### splitLine()
This functions takes in the string given by readLine() as a parameter and stores separate tokens into an array of string pointers. This way, we are able to distinguish commands from inputs.

### execute()
This function is a bit tricky. After reading and parsing the line, we run it through this function which checks whether the first token is a built-in command, a path to an executable, or a file. It first checks if it's a command. If not, it searches the current directory for an executable program of the same name. If neither of those work, if searches these paths in order for a file:

1. /usr/local/sbin
2. /usr/local/bin
3. /usr/sbin
4. /usr/bin
5. /sbin
6. /bin

### Testing
To test how the shell launches programs, I have created the following 2 programs within this directory to run:

1. helloworld - helloworld is a program which prints "hello world" 
2. printstrings - printstrings is a program which takes and n amount of strings and prints them all out separated by new lines

Using these programs I was able to test how the shell handles standard input and output. It was also a good indication of whether fork(), execv(), and wait() worked properly.

Another issue I was able to test for was how the shell handles the current working directory. To search for files in the previously mentioned 6 paths above, I had to use the getcwd() to change the current working directory. The problem with this is that it changes the working directory for the user as well, not just the program. To test this, I inputed random strings and actual files into the shell to see if the current working directory remained stable.