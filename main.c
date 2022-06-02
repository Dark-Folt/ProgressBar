#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <curl/curl.h>

#define SIZE_ARR(arr) (sizeof(arr) / sizeof(arr[0]))

const int PROG_BAR_LENGTH = 30;

typedef struct {
    long total_bytes;
} statusinfo;


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

size_t
got_data (char *buffer, size_t itemsize, size_t numitems, void *stinfo) {
    return NULL;
}

bool
download_url (char *url, statusinfo *sinfo)
{
    // init du curl
    CURL *curl = curl_easy_init();
    if (NULL == curl) return false;

    // set options
    curl_easy_setopt (curl, CURLOPT_URL, url);
    curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, got_data);
    curl_easy_setopt (curl, CURLOPT_WRITEDATA, sinfo);
    curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1);

    // do the download
    CURLcode result = curl_easy_perform (curl);

    // liveration de la memoire alloué
    curl_easy_cleanup (curl);

    return  (CURLE_OK == result);
}

int main(void)
{
    char *urls[] = {
        "https://docs.phpdoc.org/3.0/packages/phpDocumentor-AST.html",
        "https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-11.3.0-amd64-netinst.iso"
    };

    int i;
    for(i=0; i <= 100; i++) {
        update_bar(i);
        usleep(20000);
    }
    printf ("\n");
    return 0;
}