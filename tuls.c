#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

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

    //Read items one by one
    struct dirent *entry;
    while ((entry = readdir(folder)) != NULL) {
        
        // skipping hidden files
        if (entry->d_name[0] == '.') {
            continue;
        }

        //path constructor for stat
        struct stat st;
        char path_to_check[600];
        strcpy(path_to_check, target_dir);
        strcat(path_to_check, "/");
        strcat(path_to_check, entry->d_name);

        //determining wheter it is a directory or file to print.
        if (stat(path_to_check, &st) == 0 && S_ISDIR(st.st_mode)) {
            printf("\033[38;5;208m%s\033[0m\n", entry->d_name); // entry -> d_name retrieves directory or file name
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    //Clean up
    closedir(folder);

    return 0;
}

//Test Cases
    // gcc tuls.c -o tuls -Wall -Werror

// Case 1: No arguments (Lists current directory)
    // ./tuls

// Case 2: Specific directory path
    // ./tuls test_dir_1

// Case 3: Too many arguments (Should print an error)
    // ./tuls test test2

// Case 4: Hidden directory check (Should NOT show .git or other dots)
    // ls -a    # This shows everything, including hidden ones
    // ./tuls   # Run this to prove your code filters the dots out

// Case 5: Nonexistent directory (Should print "tuls: cannot open directory")
    // ./tuls folder_made_up