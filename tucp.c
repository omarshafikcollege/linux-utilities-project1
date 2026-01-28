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

    //For loop t oprocess files
    for (int i = 1; i < argc - 1; i++) {
        char final_dest[100];

        //Path Constructor
        if (is_dir == 1) {
            strcpy(final_dest, argv[argc-1]);
            strcat(final_dest, "/");
            strcat(final_dest, argv[i]);
        } else {
            //if not a directory then just use name directly
            strcpy(final_dest, argv[argc-1]);
        }

        // reads current file with guard
        FILE *src = fopen(argv[i], "rb");
        if (src == NULL) {
            printf("Error: Cannot open source file %s\n", argv[i]);
            continue; //skips current loop iteration
        }

        // writes to dest with guard 
        FILE *dst = fopen(final_dest, "wb");
        if (dst == NULL) {
            printf("Error: Cannot create destination\n");
            fclose(src); // closes source file in case of error
            continue;
        }

        // copies byte by byte
        int ch;
        while ((ch = fgetc(src)) != EOF) {
            fputc(ch, dst);
        }

        //ensuring files close before end of program
        fclose(src);
        fclose(dst);
    }

    return 0;
}

//Test cases
    // gcc tucp.c -o tucp -Wall -Werror

//Case 1: File to File (test.txt to test2.txt)
    // ./tucp test.txt test2.txt
    // cat test2.txt

//Case 2: Image Copy (ImageToCopy.png to ImageToCopy2.png)
    // ./tucp ImageToCopy.png ImageToCopy2.png


//Case 3: Overwrite test2.txt with second_test.txt
    // ./tucp test_second.txt test2.txt
    // cat test2.txt

//Case 4: Nonexistent file (Should print an error)
    // ./tucp non_existent_file.txt nowhere.txt

//Case 5: File to Directory
    // mkdir test
    // ./tucp test.txt test
    // ls test

//Case 6: Multiple files to Directory
    // ./tucp test.txt ImageToCopy.png test
    // ls test

//Case 7: Copy to nonexistent directory (Should print an error)
    // ./tucp test.txt folder_that_doesnt_exist/

//Case 8: One argument error (Should print an error)
    // ./tucp test.txt

//Case 9: Two directories error (Should print an error)
    // mkdir test_dir1 test_dir2
    // ./tucp test_dir1 test_dir2