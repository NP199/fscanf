/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
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
    int  personalnummer;
    char nachname[20];
    char vorname[20];
    int  geburtsjahr;
};
typedef struct person person_t;

person_t *next = NULL;	
person_t *begin = NULL;

void init_list()
{
	person_t *zeiger;
	printf("zeiger:%p begin:%p, next:%p\n",(void *)zeiger,(void *)begin, (void *)zeiger->next );

	if(begin == NULL)
	{
		if((begin = malloc(sizeof(struct person_t))) == NULL)
		{
			fprintf(stderr, "Kein Speicherplatz vorhanden für den Anfang!\n");
			exit(2);
		}
		
		printf("zeiger:%p begin:%p, next:%p\n",(void *)zeiger,(void *)begin, (void *)zeiger->next );

		zeiger = begin;
	
		printf("zeiger:%p begin:%p, next:%p\n",(void *)zeiger,(void *)begin, (void *)zeiger->next );
		while(zeiger->next != NULL)
		{
			zeiger =zeiger->next;
		}
		if((zeiger->next = malloc(sizeof(struct person_t))) == NULL)
		{
			fprintf(stderr, "Kein Speicherplatz vorhanden für den naechsten Zeiger!\n");
			exit(2);
		}

		printf("zeiger:%p begin:%p, next:%p\n",(void *)zeiger,(void *)begin, (void *)zeiger->next );
		zeiger = zeiger->next;		
		printf("zeiger:%p begin:%p, next:%p\n",(void *)zeiger,(void *)begin, (void *)zeiger->next );
	}
	else
	{
		fprintf(stderr ,"erster Zeiger bereits vorhanden!");
		exit(2);
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
    person_t database[DB_SIZE];
    while(fscanf(filepointer,
                 "%d,%[^,],%[^,],%d",
                 &database[zaehler].personalnummer,
                 database[zaehler].nachname,
                 database[zaehler].vorname,
                 &database[zaehler].geburtsjahr)
          != EOF)
    {
        printf("%d, %s, %s, %d \n",
               database[zaehler].personalnummer,
               database[zaehler].nachname,
               database[zaehler].vorname,
               database[zaehler].geburtsjahr);
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
	init_list();
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
