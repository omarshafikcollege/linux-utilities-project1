#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *target_dir;

    //Argument check & assigning target directory.
    if (argc == 1) {
        target_dir = "."; //loos for the folder the user is currently in
    } else if (argc == 2) {
        target_dir = argv[1]; //looks at the folder the user typed
    } else {
        printf("Error: Too many arguments\n");
        return 1;
    }

    //Opening the folder
    DIR *folder = opendir(target_dir);
    if (folder == NULL) {
        printf("can't open directory\n"); // Required error message 
        return 1;
    }

    return 0;
}