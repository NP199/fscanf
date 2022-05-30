/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct ListNode
{
    ListElement_t    data;
    struct ListNode* next;
};
typedef struct ListNode ListNode_t;

struct List
{
    ListNode_t* head;
};
typedef struct List List_t;
typedef void (*ListElement_callback_t)(ListElement_t const* const);

//Funtionsdeklaration
ListElement_t* list_insert(List_t* list, ListElement_t* const position);
ListElement_t* list_push_back(List_t* list);
ListElement_t* list_push(List_t* list);

void list_erase(List_t* list, ListElement_t* const position);
void list_pop_back(List_t* list);
void list_pop(List_t* list);

ListElement_t* list_front(List_t* list);
ListElement_t* list_back(List_t* list);

void list_foreach(List_t const* const list, ListElement_callback_t operation);

void list_init(List_t* const list);
void list_free(List_t* const list);

bool         list_empty(List_t const* const list);
unsigned int list_size(List_t const* const list);

//Funktionsdefinition
//Liste leer, Liste != leer Position == NULL, Position außerhalb von Liste
//Position irgendwo in Liste
ListElement_t* list_insert(List_t* list, ListElement_t* const positionElement)
{
    ListNode_t* current_node  = list->head;
    ListNode_t* position      = (ListNode_t*)positionElement;
    ListNode_t* previous_node = current_node;
    ListNode_t* new_node      = NULL;

    if(current_node == NULL && position != NULL)
    {
        fprintf(stderr, "Liste leer, Position nicht. Was ist da passiert?, list_insert grueßt");
        exit(1);
    }
    if(position == list->head)
    {
        new_node       = malloc(sizeof(ListNode_t));
        new_node->next = list->head;
        list->head     = new_node;
        return &new_node->data;
    }
    while(current_node != NULL && current_node != position)
    {
        previous_node = current_node;
        current_node  = current_node->next;
    }
    new_node            = malloc(sizeof(ListNode_t));
    previous_node->next = new_node;
    new_node->next      = current_node;

    return &new_node->data;
}

ListElement_t* list_push_back(List_t* list) { return list_insert(list, NULL); }

ListElement_t* list_push(List_t* list) { return list_insert(list, list_front(list)); }
//leere Liste Position == NULL, Liste != leer Postition irgendwo in Liste,
//Position außerhalb von Liste, Liste leer Position != NULL
void list_erase(List_t* list, ListElement_t* const positionElement)
{
    ListNode_t* current_node  = list->head;
    ListNode_t* position      = (ListNode_t*)positionElement;
    ListNode_t* previous_node = current_node;

    if(current_node == NULL && position != NULL)
    {
        fprintf(stderr, "Liste leer, Position nicht. Was ist da passiert?, list_erase grueßt");
        exit(1);
    }
    if(current_node != NULL && position != NULL)
    {
        while(current_node != NULL && current_node != position)
        {
            previous_node = current_node;
            current_node  = current_node->next;
        }
        if(current_node == NULL)
        {
            fprintf(stderr, "Das war gar nicht gut!, ihr list_erase");
            exit(1);
        }
        if(position == list->head)
        {
            list->head = position->next;
        }
        else
        {
            previous_node->next = position->next;
        }
        free(position);
    }
}

void list_pop_back(List_t* list) { list_erase(list, list_back(list)); }

void list_pop(List_t* list) { list_erase(list, list_front(list)); }

ListElement_t* list_front(List_t* list)
{
    if(list->head == NULL)
    {
        return NULL;
    }
    return &list->head->data;
}

ListElement_t* list_back(List_t* list)
{
    ListNode_t* latest_node = list->head;
    if(latest_node == NULL)
    {
        return NULL;
    }
    while(latest_node->next != NULL)
    {
        latest_node = latest_node->next;
    }
    return &latest_node->data;
}

void list_foreach(List_t const* const list, ListElement_callback_t operation)
{
    ListNode_t const* current_node = list->head;
    while(current_node != NULL)
    {
        operation(&current_node->data);
        current_node = current_node->next;
    }
}

void list_init(List_t* const list) { list->head = NULL; }

void list_free(List_t* const list)
{
    ListNode_t* current_node  = list->head;
    ListNode_t* previous_node = NULL;

    while(current_node != NULL)
    {
        previous_node = current_node;
        current_node  = current_node->next;
        free(previous_node);
    }
    list_init(list);
}

bool list_empty(List_t const* const list)
{
    if(list->head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
unsigned int list_size(List_t const* const list)
{
    unsigned int      size         = 0;
    ListNode_t const* current_node = list->head;

    while(current_node != NULL)
    {
        current_node = current_node->next;
        size++;
    }
    return size;
}
