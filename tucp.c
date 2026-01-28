#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //Making sure we have the minimum amount of arguments
    if (argc < 3) {
        printf("Error: Not enough arguments\n");
        return 1;
    }

    //using stat to find if last argument is a directory or not
    struct stat st;
    int is_dir = 0;
    if (stat(argv[argc-1], &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            is_dir = 1;
        }
    }

    return 0;
}