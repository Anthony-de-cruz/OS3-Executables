#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Iterate over the directories,
// printing all of the executable files found inside
//
// returns true if all directories are valid
// return false if there is an invalid directory
bool print_executables(char *directories[]) { return true; }

// Parse argv into args
void parse_args(int argc, char *argv[], char *args[]) {}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Err: Missing argument\n");
        return EXIT_FAILURE;
    }

    char *args[ARG_MAX];

    parse_args(argc, argv, args);

    if (print_executables(args)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
