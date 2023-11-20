#include <util.h>
#include <runner.h>
#include <stdio.h>

char * get_session(void) {
    FILE * file = fopen(SESSION_KEY, "r");
    if(file == NULL) return NULL;

    char * session_key = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    fgets(session_key, BUFFER_SIZE, file);

    fclose(file);
    return session_key;
}

int fetch_input(const char * year, const char * day) {
    char * session_key = get_session();
    char command[BUFFER_SIZE];
    sprintf(command, 
            "curl --silent 'https://adventofcode.com/%s/day/%s/input' -H 'Cookie: session=%s' > /tmp/year%s_%s.input", 
            year, day, session_key, year, day
    );
    
    return system(command);
}

int cleanup_file(const char * filename) {
    return remove(filename);
}


