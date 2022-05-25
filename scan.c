/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.2.2";
int const DB_SIZE = 20;

struct person
{
    int  personalnummer;
    char nachname[20];
    char vorname[20];
    int  geburtsjahr;
	struct person *next;
};
typedef struct person person_t;

person_t *next = NULL;
person_t *anfang = NULL;	

void init_list()
{
	//printf("database:%p next:%p, anfang:%p\n", (void *)database, (void*)next, (void*)anfang );

	if(anfang == NULL)
	{
		anfang = malloc(sizeof(person_t));
		if(anfang == NULL)
		{
			fprintf(stderr, "Kein Speicherplatz vorhanden für den Anfang!\n");
			exit(2);
		}
	}
}

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
	
	next = anfang;
    while(fscanf(filepointer,
                 "%d,%[^,],%[^,],%d",
                 &next->personalnummer,
                 next->nachname,
                 next->vorname,
                 &next->geburtsjahr)
          != EOF)
    {		
     
	   printf("%d, %s, %s, %d \n",
               next->personalnummer,
               next->nachname,
               next->vorname,
               next->geburtsjahr);
        
		if(next->next == NULL)
		{
			next->next = malloc(sizeof(person_t));
			if(next->next == NULL)
			{
				fprintf(stderr,"Kein Speicherplatz für einen weiteren Eintrag!");
			}
			next = next->next;
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

	init_list();
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
