#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int PROG_BAR_LENGTH = 30;

void
update_bar (int percent_done)
{
    int i;
    int num_char = percent_done * PROG_BAR_LENGTH / 100;

    printf("\r[");
    for (i=0; i < num_char; i++) {
        printf ("#");
    }
    for (i = 0; i < PROG_BAR_LENGTH - num_char; i++) {
        printf (" ");
    }
    printf("] %d%% Done", percent_done);
    fflush(stdout);
}

int main(void)
{
    int i;
    for(i=0; i <= 100; i++) {
        update_bar(i);
        usleep(20000);
    }
    printf ("\n");
    return 0;
}