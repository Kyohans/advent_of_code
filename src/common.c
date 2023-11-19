#include <advent_of_code.h>

char * get_session(void) {
    FILE * file = fopen(SESSION_KEY, "r");
    char * session_key = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(session_key, BUFFER_SIZE, file);

    fclose(file);
    return session_key;
}

FILE * fetch_input(const char * day, const char * year) {
    char * session_key = get_session();
    char command[BUFFER_SIZE];
    sprintf(command, "curl 'https://adventofcode.com/%s/day/%s/input' -H 'Cookie: %s'", year, day, session_key);
    
    FILE * input = popen(command, "r");
    if(input == NULL) {
        return NULL;
    }
    return input;
}
