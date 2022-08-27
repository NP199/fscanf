/**
 *	Projekt geforked von https://github.com/np199/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.2";

int const DB_SIZE = 20;

struct person
{
    char name[30];
    char birthday[11];
    char deathday[11];
    char gender[2];
    char birthplace[30];
    char partner[30];
    char siblingName[30];
    char childName[30];
    struct person sibling;
    struct person child;
};
typedef struct person person_t;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t database[DB_SIZE];
    while(fscanf(filepointer,
                 "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                 &database[zaehler].name,
                 database[zaehler].birthday,
                 database[zaehler].deathday,
                 &database[zaehler].gender,
		 &database[zaehler].birthplace,
		 &database[zaehler].partner,
		 &database[zaehler].siblingName,
		 &database[zaehler].childName)
          != EOF)    
    {
        printf("%s, %s, %s, %s, %s, %s, %s, %s\n",
               database[zaehler].name,
               database[zaehler].birthday,
               database[zaehler].deathday,
               database[zaehler].gender,
	       database[zaehler].birthplace,
	       database[zaehler].partner,
	       database[zaehler].siblingName,
	       database[zaehler].childName);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
