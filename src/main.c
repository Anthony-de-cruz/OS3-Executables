#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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

// Checks whether or not the user has execution permissions for the file
// at path.
//
// - Returns bool
bool has_exe_perms(char *path) {

    // Get file stat
    struct stat stat_buf;
    if (stat(path, &stat_buf) != 0) {
        printf("%s\n", path);
        perror("Stat error");
        return false;
    }

    // The 7th bit of file_stat.st_mode signifies the execution permissions
    // of the file. S_IXUSR acts as a bit mask for the 7th bit, allowing us
    // to check it. S_ISREG() is a macro to check if it is regular file
    if (stat_buf.st_mode & S_IXUSR && S_ISREG(stat_buf.st_mode)) {
        return true;
    }
    return false;
}

// Iterate over the directories,
// printing all of the executable files found inside.
//
// - Returns true if all directories are valid and
//   false if there is an invalid directory
bool print_executables(int dirc, char *dirs[]) {

    for (int x = 0; x + 1 <= dirc; x++) {
        printf("DIRECTORY: %s\n", dirs[x]);

        // Open the directory
        DIR *dir = opendir(dirs[x]);
        if (dir == NULL) {
            perror("Error opening directory");
            return false;
        }
        struct dirent *entry;

        // Iterate over all the files
        while ((entry = readdir(dir)) != NULL) {
            
            // Put together a path for the file
            char *file_path = strdup(dirs[x]);
            file_path = realloc(file_path, PATH_MAX);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            // Check if the file is executable
            if (has_exe_perms(file_path)) {
                printf("    %8ld - %20s\n", entry->d_ino, entry->d_name);
            }

            free(file_path);
        }

        closedir(dir);
    }

    /*
    // DEBUG
    printf("\nArgs check\n");
    for (int x = 0; x < 15; x++) {
        printf("    args[%d] = %s\n", x, dirs[x]);
    }*/

    return true;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Err: Missing argument\n");
        return EXIT_FAILURE;
    }

    char **dirs = malloc(_POSIX_ARG_MAX * PATH_MAX);

    int dirc = parse_args(argc, argv, dirs);

    if (print_executables(dirc, dirs)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
