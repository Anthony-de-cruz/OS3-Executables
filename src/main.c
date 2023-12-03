#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Parse argv into dirs.
//
// - Accepts formats ['/usr/bin', 'usr/sbin'] and ['/usr/bin:/usr/sbin'].
//
// - Returns number of directories in dirs
int parse_args(int argc, char *argv[], char **dirs) {

    int dirc = 0;

    for (int arg = 0; arg + 1 < argc; arg++) {

        char *temp = strdup(argv[arg + 1]);
        char *token = strtok(temp, ":");

        // Tokenise each string, delimiting by :
        // and appending to args[]
        while (token != NULL) {
            dirs[dirc] = token;
            dirc++;
            token = strtok(NULL, ":");
        }

        free(token);
    }

    dirs = realloc(dirs, dirc * sizeof(char *));
    return dirc;
}

// Iterate over the directories,
// printing all of the executable files found inside.
//
// - Returns true if all directories are valid
// - Returns false if there is an invalid directory
bool print_executables(int dirc, char *dirs[]) {

    for (int x = 0; x + 1 < dirc; x++) {
        printf("%s\n", dirs[x]);
    }

    return true;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Err: Missing argument\n");
        return EXIT_FAILURE;
    }

    char **dirs = malloc(ARG_MAX * PATH_MAX);

    int dirc = parse_args(argc, argv, dirs);

    /*
    printf("\nArgs check\n");
    for (int x = 0; x < 15; x++) {
        printf("    args[%d] = %s\n", x, args[x]);
    }*/

    if (print_executables(dirc, dirs)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
