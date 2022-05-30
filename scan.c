/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct Person
{
    int  personalnummer;
    char nachname[20];
    char vorname[20];
    int  geburtsjahr;
};
typedef struct Person Person_t;
typedef Person_t      ListElement_t;
#include "list.h"
typedef List_t PersonList_t;

char const* const VERSIONSNR = "0.2.2";

void readcsv(char const* const datei, PersonList_t* list)
{
    FILE* filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }

    Person_t* newdata = NULL;

    do
    {
        newdata = list_push_back(list);
    } while(fscanf(filepointer,
                   "%d,%[^,],%[^,],%d",
                   &newdata->personalnummer,
                   newdata->nachname,
                   newdata->vorname,
                   &newdata->geburtsjahr)
            == 4);

    list_pop_back(list);
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

void print_person(Person_t const* const person)
{
    printf("%d, %s, %s, %d \n",
           person->personalnummer,
           person->nachname,
           person->vorname,
           person->geburtsjahr);
}

void test_list()
{
    PersonList_t list;
    list_init(&list);
    // Testaufrufe
    Person_t* person = list_push(&list);
    strcpy(person->vorname, "Hans");
    strcpy(person->nachname, "wurst");
    person->personalnummer = 1;
    person->geburtsjahr    = 1999;
    printf("1\n");
    person = list_push_back(&list);
    strcpy(person->vorname, "Hans2");
    strcpy(person->nachname, "wurst2");
    person->personalnummer = 2;
    person->geburtsjahr    = 2000;
    printf("4\n");
    person = list_push_back(&list);
    strcpy(person->vorname, "Hans4");
    strcpy(person->nachname, "wurst4");
    person->personalnummer = 4;
    person->geburtsjahr    = 2004;

    printf("2\n");
    person = list_insert(&list, person);
    strcpy(person->vorname, "Hans3");
    strcpy(person->nachname, "wurst3");
    person->personalnummer = 3;
    person->geburtsjahr    = 2003;

    printf("Ganze Liste\n");
    list_foreach(&list, print_person);
    printf("list_back\n");
    print_person(list_back(&list));

    printf("list_front\n");
    print_person(list_front(&list));
    printf("List groeße:%d\n", list_size(&list));
    list_pop_back(&list);
    list_pop(&list);
    printf("empty:%i\n", list_empty(&list));
    printf("List groeße:%d\n", list_size(&list));
    printf("ganze Liste\n");
    list_foreach(&list, print_person);
    list_free(&list);
    list_foreach(&list, print_person);
    printf("List groeße:%d\n", list_size(&list));
    printf("empty:%i\n", list_empty(&list));
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
        {
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);
        }
        case 'v':
        {
            printf("Version %s\n", VERSIONSNR);
            exit(0);
        }
        case 'f':
        {
            PersonList_t list;
            list_init(&list);
            readcsv(optarg, &list);
            list_foreach(&list, print_person);
            list_free(&list);
            break;
        }
        case '?':
        {
            fprintf(stderr, "Please try -h\n");
            exit(1);
        }
        case -1:
        {
            exit(0);
        }
        }
    }

    return 0;
}
