#include <stdio.h>
#include <stdlib.h>
#include "tinyscript.h"

int inchar() {
    return getchar();
}
void outchar(int c) {
    putchar(c);
}

#define MAX_SCRIPT_SIZE 100000
char script[MAX_SCRIPT_SIZE];

void
runscript(const char *filename)
{
    FILE *f = fopen(filename, "r");
    int r;
    if (!f) {
        perror(filename);
        return;
    }
    r=fread(script, 1, MAX_SCRIPT_SIZE, f);
    fclose(f);
    if (r <= 0) {
        fprintf(stderr, "File read error on %s\n", filename);
        return;
    }
    script[r] = 0;
    r = TinyScript_Run(script);
    if (r != 0) {
        printf("script error %d\n", r);
    }
    exit(r);
}

void
REPL()
{
    char buf[128];
    char *s;
    int r;
    
    for(;;) {
        printf("> "); fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        r = TinyScript_Run(buf);
        if (r != 0) {
            printf("error %d\n", r);
        }
    }
}

int
main(int argc, char **argv)
{
    if (argc > 2) {
        fprintf(stderr, "Usage: tinyscript [file]\n");
    }
    TinyScript_Init();
    if (argv[1]) {
        runscript(argv[1]);
    } else {
        REPL();
    }
    return 0;
}

