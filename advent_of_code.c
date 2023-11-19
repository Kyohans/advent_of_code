#include <stdio.h>
#include <advent_of_code.h>

#define PROJECT_NAME "advent-of-code"

int main(int argc, char **argv) {
    if(argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }
    printf("This is project %s.\n", PROJECT_NAME);
    // FILE * file = fetch_input("2022", "1");
    // if(file != NULL) {
    //     printf("File opened!");
    //     fclose(file);
    // }
    printf("%s\n", get_session());
}
