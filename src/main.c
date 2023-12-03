#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Iterate over the directories,
// printing all of the executable files found inside.
//
// - returns true if all directories are valid
// - return false if there is an invalid directory
bool print_executables(char *directories[]) { return true; }

// Parse argv into args.
//
// - Accepts formats ['/usr/bin', 'usr/sbin'] and ['/usr/bin:/usr/sbin'].
void parse_args(int argc, char *argv[], char *args[]) {

    int dir = 0;
    int arg = 0;

    for (; arg + 1 < argc; arg++) {

        char *temp = strdup(argv[arg + 1]);
        char *token = strtok(temp, ":");
        
        // Tokenise each string, delimiting by :
        // and appending to args[]
        while (token != NULL) {
            args[dir] = token;
            dir++;
            token = strtok(NULL, ":");
        }

        free(token);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Err: Missing argument\n");
        return EXIT_FAILURE;
    }

    char *args[ARG_MAX];

    parse_args(argc, argv, args);
    
    /*
    printf("\nArgs check\n");
    for (int x = 0; x < 15; x++) {
        printf("    args[%d] = %s\n", x, args[x]);
    }*/

    if (print_executables(args)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
